#include "../minishell.h"

int	access_all_infile(t_infile *infile)
{
	int	i;

	if (!infile->infile[0])
		return (0);

	printf("infile present\n");
	i = 0;
	while (infile->infile[i])
	{
		printf("testing access for infile %s\n", infile->infile[0]);
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
	*infile->fd = open(infile->infile[i], O_RDONLY);
	printf("file fd should be: %d\n", *infile->fd);
	if (*infile->fd == -1)
	{
		perror(infile->infile[i]);
		free(infile->fd);
		return (-1);
	}
	printf("infile OK fd = %d\n", *infile->fd);
	return (0);
}

int create_outfile(t_outfile *outfile)
{
	if (!outfile->outfile[0])
		return (0);
	printf("outfile present\n");
	outfile->fd = malloc(sizeof(int));
	if (!outfile->fd)
		return (-1);
	*outfile->fd = open(outfile->outfile[0], O_TRUNC | O_APPEND | O_WRONLY | O_CREAT, 0644); 
	if (*outfile->fd == -1)
	{
		perror(outfile->outfile[0]);
		free(outfile->fd);
		return (-1);
	}
	printf("oufile OK fd = %d\n", *outfile->fd);
	return (0);
}
// pid == -1 = fail
// pid == 0 = child process
// else pid = parent process
int execute_command(t_env **env, t_parser **parser)
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
		replace_command_name_by_path(&(*parser)->str[0], *env);
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
		waitpid(pid, NULL, 0);
		return (0);
	}
}

// make it so create_outfile uses the good flag and same for access_all_infile
int	executor(t_env **env, t_parser *parser)
{
	int	pipefd[2];

	if (!parser)
		return (0);

	while (parser)
	{
		printf("starting execution of command: %s\n", parser->str[0]);
		if (create_outfile(&parser->outfile) == -1 || access_all_infile(&parser->infile))
		{
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
		execute_command(env, &parser);
		parser = parser->next;
	}
	printf("finished executor\n");
	return (0);
}
