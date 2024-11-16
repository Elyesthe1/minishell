/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:27 by erahal            #+#    #+#             */
/*   Updated: 2024/11/16 15:38:12 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	access_all_infile(t_infile *infile, t_env **env, t_parser **parser)
{
	int	i;
	int	tmp_fd;

	if (!infile->infile[0])
		return (0);
	i = 0;
	while (infile->infile[i])
	{
		if (infile->flag[i] == 4)
			tmp_fd = here_doc(infile->infile[i], env, NULL, parser);
		else if (infile->flag[i] == 1)
			tmp_fd = open(infile->infile[i], O_RDONLY);
		if (tmp_fd == -1)
			return (perror(infile->infile[i]), g_status_code = 1, -1);
		else if (tmp_fd == -2)
			return (-2);
		if (infile->infile[i + 1])
			close(tmp_fd);
		++i;
	}
	malloc_infile(infile);
	if (!infile->fd)
		return (close(tmp_fd), -1);
	*infile->fd = tmp_fd;
	return (0);
}

int	create_outfile(t_outfile *outfile)
{
	int	i;
	int	tmp_fd;

	if (!outfile->outfile[0])
		return (0);
	i = 0;
	while (outfile->outfile[i])
	{
		if (outfile->flag[i] == 2)
			tmp_fd = open(outfile->outfile[i],
					O_TRUNC | O_APPEND | O_WRONLY | O_CREAT, 0644);
		else if (outfile->flag[i] == 3)
			tmp_fd = open(outfile->outfile[i], O_APPEND | O_WRONLY | O_CREAT,
					0644);
		if (tmp_fd == -1)
			return (perror(outfile->outfile[i]), g_status_code = 1, -1);
		if (outfile->outfile[i + 1])
			close(tmp_fd);
		++i;
	}
	outfile->fd = malloc(sizeof(int));
	if (!outfile->fd)
		return (close(tmp_fd), -1);
	*outfile->fd = tmp_fd;
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

int	execute_command(t_env **env, t_parser **parser, t_pids **pids, int n_pipes)
{
	pid_t	pid;

	if (!(*parser)->str[0])
	{
		close_free_fd(parser);
		return (-1);
	}
	if (execute_outside_fork((*parser)->str[0], (*parser)->str, n_pipes))
		return (close_free_fd(parser), exec_outside_built((*parser)->str, env));
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signal_default();
		dup2_fd((*parser)->infile.fd, (*parser)->outfile.fd);
		close_next_fd(parser);
		if (!is_builtin((*parser)->str[0]))
			execve_cmd(parser, env);
		else
			exit(exec_built((*parser)->str, env));
		exit(0);
	}
	return (close_free_fd(parser), add_pid(pids, pid), 0);
}

int	executor(t_env **env, t_parser *parser, int n_pipes)
{
	int		pipefd[2];
	t_pids	*pids;

	if (!parser)
		return (0);
	pids = NULL;
	while (parser)
	{
		if (access_all_infile(&parser->infile, env, &parser) == 0
			&& create_outfile(&parser->outfile) == 0)
		{
			if (parser->next)
				create_pipe(pipefd, &parser);
			execute_command(env, &parser, &pids, n_pipes);
		}
		if (parser && parser->infile.fd)
		{
			free(parser->infile.fd);
			parser->infile.fd = NULL;
		}
		if (parser)
			parser = parser->next;
	}
	wait_all_pids(&pids);
	return (0);
}
