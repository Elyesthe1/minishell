#include "../minishell.h"

int	here_doc(char *limiter)
{
	char	*line;
	int		hd_pipes[2];

	line = NULL;
	pipe(hd_pipes);
	while (true)
	{
		free(line);
		line = readline("> ");
		if (ft_strcmp(line, limiter) == 0)
			break ;
		line = ft_strjoin_free(line, "\n");
		write(hd_pipes[1], line, ft_strlen(line));
	}
	free(line);
	close(hd_pipes[1]);
	return (hd_pipes[0]);
}
