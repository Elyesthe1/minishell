/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:25 by erahal            #+#    #+#             */
/*   Updated: 2024/11/16 15:36:59 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(int pipefd[2], t_parser **parser)
{
	pipe(pipefd);
	if ((*parser)->outfile.fd == NULL)
	{
		(*parser)->outfile.fd = malloc(sizeof(int));
		*(*parser)->outfile.fd = pipefd[1];
	}
	else
	{
		close(pipefd[1]);
	}
	(*parser)->next->infile.fd = malloc(sizeof(int));
	*(*parser)->next->infile.fd = pipefd[0];
}

void	close_free_fd(t_parser **parser)
{
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
}

void	close_next_fd(t_parser **parser)
{
	if ((*parser)->next)
	{
		if ((*parser)->next->infile.fd)
			close(*(*parser)->next->infile.fd);
		if ((*parser)->next->outfile.fd)
			close(*(*parser)->next->outfile.fd);
	}
}

void	malloc_infile(t_infile *infile)
{
	if (infile->fd)
	{
		close(*infile->fd);
		free(infile->fd);
		infile->fd = NULL;
	}
	infile->fd = malloc(sizeof(int));
}

void	execve_cmd(t_parser **parser, t_env **env)
{
	char	**envp;

	envp = NULL;
	replace_command_name_by_path(&(*parser)->str[0], *env);
	envp = convert_env_to_envp(*env);
	execve((*parser)->str[0], (*parser)->str, envp);
}
