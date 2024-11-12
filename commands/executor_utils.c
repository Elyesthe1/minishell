/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:25 by erahal            #+#    #+#             */
/*   Updated: 2024/11/12 18:54:26 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(int pipefd[2], t_parser **parser)
{
	pipe(pipefd);
	(*parser)->outfile.fd = malloc(sizeof(int));
	*(*parser)->outfile.fd = pipefd[1];
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
