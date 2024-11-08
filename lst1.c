#include "minishell.h"

void	lst_free_parser(t_parser **parser)
{
	t_parser	*temp;
	int			i;

	i = 0;
	while ((*parser) != NULL)
	{
		temp = (*parser)->next;
		free((*parser)->outfile.flag);
		free((*parser)->infile.flag);
		free_free((*parser)->infile.infile);
		free_free((*parser)->outfile.outfile);
		free_free((*parser)->str);
		free((*parser));
		(*parser) = temp;
	}
}

t_parser	*ft_lstlastcmd(t_parser *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
