/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:41 by erahal            #+#    #+#             */
/*   Updated: 2024/11/13 19:06:38 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_pid(t_pids **pids, pid_t pid)
{
	t_pids	*pid_node;
	t_pids	*tmp;

	pid_node = malloc(sizeof(t_pids));
	tmp = *pids;
	if (!pid_node)
		return ;
	pid_node->pid = pid;
	pid_node->next = NULL;
	if (!tmp)
	{
		*pids = pid_node;
		return ;
	}
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = pid_node;
}



void	signal_hxDDD(int signal)
{
	// (void)signal;
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	}
}
// CHECK IF A CHILD WAS KILLED BY A SIGNAL AND IF SO PRINT (COREDUMP)

void	free_all_pids(t_pids **pids)
{
	t_pids	*pid_node;
	t_pids	*next;

	pid_node = *pids;
	while (pid_node)
	{
		next = pid_node->next;
		free(pid_node);
		pid_node = next;
	}
	*pids = NULL;
}

void	wait_all_pids(t_pids **pids)
{
	int	status_code;
	t_pids	*pid_node;

	pid_node = *pids;
	signal(SIGINT, &signal_hxDDD);
	signal(SIGQUIT, &signal_hxDDD);
	while (pid_node)
	{
		if (pid_node->next)
			waitpid(pid_node->pid, NULL, 0);
		else
		{
			waitpid(pid_node->pid, &status_code, 0);
			
			g_status_code = (WEXITSTATUS(status_code)) % 256;
		}
		pid_node = pid_node->next;
	}
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	free_all_pids(pids);
}
