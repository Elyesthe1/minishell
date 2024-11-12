/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:27 by erahal            #+#    #+#             */
/*   Updated: 2024/11/12 18:54:33 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			tmp_fd = here_doc(infile->infile[i], env, NULL);
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
			return (perror(outfile->outfile[i]), -1);
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

int	execute_command(t_env **env, t_parser **parser, t_pids **pids)
{
	pid_t	pid;
	char	**envp;

	if (!(*parser)->str[0])
		return (-1);
	if (execute_outside_fork((*parser)->str[0], (*parser)->str))
		return (close_free_fd(parser), exec_built((*parser)->str, env));
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		dup2_fd((*parser)->infile.fd, (*parser)->outfile.fd);
		close_next_fd(parser);
		if (!is_builtin((*parser)->str[0]))
		{
			replace_command_name_by_path(&(*parser)->str[0], *env);
			envp = convert_env_to_envp(*env);
			execve((*parser)->str[0], (*parser)->str, envp);
		}
		else
			exec_built((*parser)->str, env);
		exit(0);
	}
	return (close_free_fd(parser), add_pid(pids, pid), 0);
}

int	executor(t_env **env, t_parser *parser)
{
	int		pipefd[2];
	t_pids	*pids;

	if (!parser)
		return (0);
	pids = NULL;
	while (parser)
	{
		if (access_all_infile(&parser->infile, env) == 0
			&& create_outfile(&parser->outfile) == 0)
		{
			if (parser->next && parser->outfile.fd == NULL)
				create_pipe(pipefd, &parser);
			execute_command(env, &parser, &pids);
		}
		if (parser->infile.fd)
		{
			free(parser->infile.fd);
			parser->infile.fd = NULL;
		}
		parser = parser->next;
	}
	wait_all_pids(pids);
	free_all_pids(&pids);
	return (0);
}
