#include "../minishell.h"

extern int	g_status_code;

int print_error()
{
	write(2, "error: warning: here-document stoped\n", 38);
	return (1);
}

int here_doc1(char *line, int pipe[2])
{
	signal(SIGINT, &signal_handler);
	free(line);
	close(pipe[1]);
	return (pipe[0]);
}

void signal_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		close(0);
		g_status_code = -99;
	}
}

int	here_doc(char *limiter, t_env **env, char *line)
{
	int fd;
	int		hd_pipes[2];

	fd = dup(0);
	pipe(hd_pipes);
	signal(SIGINT, &signal_handler_heredoc);
	while (true)
	{
		free(line);
		line = readline("> ");
		if (line == NULL && g_status_code == -99)
		{
			dup2(fd, STDIN_FILENO);
			g_status_code = 0;
			break;
		}
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
