

#include "minishell.h"

t_parser	*ft_lstnewcmd(t_lexer *lexer)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	// new->str = content;
	new->next = NULL;
	return (new);
}


void	ft_lstadd_backcmd(t_parser **lst, t_parser *new)
{
	t_parser	*tmp;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		(*lst) = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}


