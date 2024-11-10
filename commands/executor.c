#include "../minishell.h"

// CHECK IF ALL INFILE EXISTS AND THEN USE HERE_DOC
int	access_all_infile(t_infile *infile)
{
	int	i;

	if (!infile->infile[0])
		return (0);

	printf("infile present\n");
	i = 0;
	while (infile->infile[i])
	{
		if (infile->flag[i] == 4)
		{
			++i;
			continue;
		}
		printf("testing access for infile %s\n", infile->infile[i]);
		if (access(infile->infile[i], R_OK) == -1)
		{
			perror(infile->infile[i]);
			return (-1);
		}
		++i;
	}
	--i;
	infile->fd = malloc(sizeof(int));
	if (!infile->fd)
		return (-1);
	printf("infile flag %d\n", *infile->flag);
	if (*infile->flag == 1)
		*infile->fd = open(infile->infile[i], O_RDONLY);
	else if (*infile->flag == 4)
		*infile->fd = here_doc(infile->infile[0]);
	printf("file fd should be: %d\n", *infile->fd);
	if (*infile->fd == -1)
	{
		perror(infile->infile[i]);
		free(infile->fd);
		infile->fd = NULL;
		return (-1);
	}
	printf("infile OK fd = %d\n", *infile->fd);
	return (0);
}

int create_outfile(t_outfile *outfile)
{
	int	i;
	int	tmp_fd;

	if (!outfile->outfile[0])
		return (0);
	printf("outfile present\n");
	outfile->fd = malloc(sizeof(int));
	if (!outfile->fd)
		return (-1);
	
	i = 0;
	while (outfile->outfile[i])
	{
		if (outfile->flag[i] == 2)
			tmp_fd = open(outfile->outfile[i], O_TRUNC | O_APPEND | O_WRONLY | O_CREAT, 0644); 
		else if (outfile->flag[i] == 3)
			tmp_fd = open(outfile->outfile[i], O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (tmp_fd == -1)
		{
			perror(outfile->outfile[i]);
			free(outfile->fd);
			return (-1);
		}
		if (outfile->outfile[i + 1])
			close(tmp_fd);
		else
			*outfile->fd = tmp_fd;
		++i;
	}
	printf("oufile OK name = %s - fd = %d\n", outfile->outfile[i - 1], *outfile->fd);
	return (0);
}
// pid == -1 = fail
// pid == 0 = child process
// else pid = parent process
int execute_command(t_env **env, t_parser **parser, t_pids **pids)
{
	pid_t	pid;
	char	**envp;

	printf("executing command %s\n", (*parser)->str[0]);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}

	if (pid == 0)
	{
		envp = convert_env_to_envp(*env);
		if (replace_command_name_by_path(&(*parser)->str[0], *env) == -1)
		{
			ft_free_split(envp);
			exit(0);
		}
		if ((*parser)->infile.fd)
		{
			dup2(*(*parser)->infile.fd, STDIN_FILENO);
			close(*(*parser)->infile.fd);
		}
		if ((*parser)->outfile.fd)
		{
			dup2(*(*parser)->outfile.fd, STDOUT_FILENO);
			close(*(*parser)->outfile.fd);
		}
		if ((*parser)->next)
		{
			if ((*parser)->next->infile.fd)
				close(*(*parser)->next->infile.fd);
			if ((*parser)->next->outfile.fd)
				close(*(*parser)->next->outfile.fd);
		}
		execve((*parser)->str[0], (*parser)->str, envp);
		exit(0);
	} else {
		if ((*parser)->infile.fd)
		{
			close(*(*parser)->infile.fd);
			free((*parser)->infile.fd);
			(*parser)->infile.fd = NULL;
		}
		if ((*parser)->outfile.fd)
		{
			close(*(*parser)->outfile.fd);
			free((*parser)->outfile.fd);
			(*parser)->outfile.fd = NULL;
		}
		printf("pid: %d\n", pid);
		add_pid(pids, pid);
		return (0);
	}
}

// make it so create_outfile uses the good flag and same for access_all_infile
// MAKE IT SO STATUS_CODE WORKS WITH FILE OPENING
int	executor(t_env **env, t_parser *parser)
{
	int		pipefd[2];
	t_pids	*pids;

	if (!parser)
		return (0);
	pids = NULL;
	while (parser)
	{
		printf("starting execution of command: %s\n", parser->str[0]);
		if (access_all_infile(&parser->infile) == -1 || create_outfile(&parser->outfile) == -1)
		{
			if (parser->infile.fd)
			{
				free(parser->infile.fd);
				parser->infile.fd = NULL;
			}
			printf("skipping parser cmd\n");
			parser = parser->next;
			continue;
		}
		if (parser->next && parser->outfile.fd == NULL)
		{
			pipe(pipefd);
			parser->outfile.fd = malloc(sizeof(int));
			*parser->outfile.fd = pipefd[1];
			parser->next->infile.fd = malloc(sizeof(int));
			*parser->next->infile.fd = pipefd[0];
		}
		execute_command(env, &parser, &pids);
		parser = parser->next;
	}
	wait_all_pids(pids);
	free_all_pids(&pids);
	printf("finished executor\n");
	return (0);
}
