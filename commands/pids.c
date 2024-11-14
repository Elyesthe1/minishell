/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:54:41 by erahal            #+#    #+#             */
/*   Updated: 2024/11/14 18:03:16 by tovetouc         ###   ########.fr       */
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
		write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
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

int		get_global_code(int status_code)
{
	if (WIFSIGNALED(status_code))
	{
		if (WTERMSIG(status_code) == SIGINT)
			return (130);
		else if (WTERMSIG(status_code) == SIGQUIT)
			return (131);
	}
	return ((WEXITSTATUS(status_code)) % 256);
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
			g_status_code = get_global_code(status_code);
		}
		pid_node = pid_node->next;
	}
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
	free_all_pids(pids);
}
