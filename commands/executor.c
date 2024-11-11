#include "../minishell.h"

// CHECK IF ALL INFILE EXISTS AND THEN USE HERE_DOC
// int	access_all_infile(t_infile *infile)
// {
// 	int	i;

// 	if (!infile->infile[0])
// 		return (0);

// 	printf("infile present\n");
// 	i = 0;
// 	while (infile->infile[i])
// 	{
// 		if (infile->flag[i] == 4)
// 		{
// 			++i;
// 			continue;
// 		}
// 		printf("testing access for infile %s\n", infile->infile[i]);
// 		if (access(infile->infile[i], R_OK) == -1)
// 		{
// 			perror(infile->infile[i]);
// 			return (-1);
// 		}
// 		++i;
// 	}
// 	--i;
// 	infile->fd = malloc(sizeof(int));
// 	if (!infile->fd)
// 		return (-1);
// 	printf("infile flag %d\n", *infile->flag);
// 	if (*infile->flag == 1)
// 		*infile->fd = open(infile->infile[i], O_RDONLY);
// 	else if (*infile->flag == 4)
// 		*infile->fd = here_doc(infile->infile[0]);
// 	printf("file fd should be: %d\n", *infile->fd);
// 	if (*infile->fd == -1)
// 	{
// 		perror(infile->infile[i]);
// 		free(infile->fd);
// 		infile->fd = NULL;
// 		return (-1);
// 	}
// 	printf("infile OK fd = %d\n", *infile->fd);
// 	return (0);
// }

int	access_all_infile(t_infile *infile, t_env **env)
{
	int	i;
	int	tmp_fd;

	if (!infile->infile[0])
		return (0);
	i = 0;
	while (infile->infile[i])
	{
		if (infile->flag[i] == 4)
			tmp_fd = here_doc(infile->infile[i], env);
		else if (infile->flag[i] == 1)
			tmp_fd = open(infile->infile[i], O_RDONLY);

		if (tmp_fd == -1)
			return (perror(infile->infile[i]), -1);
		if (infile->infile[i + 1])
			close(tmp_fd);
		++i;
	}
	infile->fd = malloc(sizeof(int));
	if (!infile->fd)
		return (close(tmp_fd), -1);
	*infile->fd = tmp_fd;
	return (0);
}

int create_outfile(t_outfile *outfile)
{
	int	i;
	int	tmp_fd;

	if (!outfile->outfile[0])
		return (0);
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
	return (0);
}

void	dup2_fd(int *in, int *out)
{
	if (in)
	{
		dup2(*in, STDIN_FILENO);
		close(*in);
	}
	if (out)
	{
		dup2(*out, STDOUT_FILENO);
		close(*out);
	}
}
// pid == -1 = fail
// pid == 0 = child process
// else pid = parent process
int execute_command(t_env **env, t_parser **parser, t_pids **pids)
{
	pid_t	pid;
	char	**envp;
	
	if (!(*parser)->str[0])
		return (-1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (!is_builtin((*parser)->str[0]))
			replace_command_name_by_path(&(*parser)->str[0], *env);
		dup2_fd((*parser)->infile.fd, (*parser)->outfile.fd);
		if ((*parser)->next)
		{
			if ((*parser)->next->infile.fd)
				close(*(*parser)->next->infile.fd);
			if ((*parser)->next->outfile.fd)
				close(*(*parser)->next->outfile.fd);
		}
		if (!is_builtin((*parser)->str[0]))
		{
			envp = convert_env_to_envp(*env);
			execve((*parser)->str[0], (*parser)->str, envp);
		}
		else
			execute_builtin((*parser)->str[0], (*parser)->str++, env);
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
		if (access_all_infile(&parser->infile, env) == -1 || create_outfile(&parser->outfile) == -1)
		{
			if (parser->infile.fd)
			{
				free(parser->infile.fd);
				parser->infile.fd = NULL;
			}
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
	return (0);
}
