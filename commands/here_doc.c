#include "../minishell.h"

int print_error()
{
	write(2, "error: warning: here-document stoped\n", 38);
	return (1);
}

int here_doc1(char *line, int pipe[2])
{
	free(line);
	close(pipe[1]);
	return (pipe[0]);
}

int	here_doc(char *limiter, t_env **env)
{
	char	*line;
	int		hd_pipes[2];

	line = NULL;
	pipe(hd_pipes);
	while (true)
	{
		free(line);
		line = readline("> ");
		if (line == NULL && print_error())
			break;
		if (ft_strcmp(line, limiter) == 0)
			break ;
		line = ft_strjoin_free(line, "\n");
		line = expander(&line, env);
		write(hd_pipes[1], line, ft_strlen(line));
	}
	return (here_doc1(line, hd_pipes));
}
