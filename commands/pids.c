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

void	wait_all_pids(t_pids *pids)
{
	while (pids)
	{
		if (pids->next)
			waitpid(pids->pid, NULL, 0);
		else
			waitpid(pids->pid, &g_status_code, 0);
		pids = pids->next;
	}
}

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
