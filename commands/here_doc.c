#include "../minishell.h"

int	here_doc(char *limiter, t_env **env)
{
	char	*line;
	int		hd_pipes[2];
	char *history;
	char *temp;

	line = NULL;
	history = NULL;
	pipe(hd_pipes);
	while (true)
	{
		free(line);
		line = readline("> ");
		temp = ft_strdup(line);
		if (ft_strcmp(line, limiter) == 0)
			break ;
		temp = ft_strjoin_free(temp, "\n");
		line = ft_strjoin_free(line, "\n");
		line = expander(&line, env);
		history = ft_strjoin(history, temp);
		write(hd_pipes[1], line, ft_strlen(line));
	}
	add_history(history);
	free(line);
	close(hd_pipes[1]);
	return (hd_pipes[0]);
}
