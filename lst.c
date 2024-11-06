#include "minishell.h"

t_lexer	*ft_lstnewtoken(int content)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->token.tocken = content;
	new->next = NULL;
	return (new);
}

int lst_free(t_lexer **lexer)
{
	t_lexer *tmp;
	while ((*lexer) != NULL)
	{
		tmp = (*lexer)->next;
		free((*lexer)->str);
		free((*lexer));
		(*lexer) = tmp;
	}
	return (1);
}

t_lexer	*ft_lstlast(t_lexer *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}


int	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;
	static int index = 1;

	if (!new)
		return (-1);
	if (*lst == NULL)
	{
		(*lst) = new;
		(*lst)->i = index++;
		return ((*lst)->token.tocken);
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	new->i = index++;
	return ((*lst)->token.tocken);
}


t_lexer	*ft_lstnew(void *content, int i)
{
	t_lexer	*new;
	char	*s;
	int j;

	j = 0;
	s = (char*)content;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	new->str = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	while (s[j])
	{
		new->str[j] = s[j];
		j++;
	}
	new->str[j] = '\0';
	new->token.tocken = 0;
	new->next = NULL;
	return (new);
}

