

#include "minishell.h"

void free_free(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
void lst_free_parser(t_parser **parser)
{
	t_parser *temp;
	int i;

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
void alloc1(t_lexer *lexer, t_parser **parser)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (lexer && lexer->token.token != 5)
	{
		while (lexer && lexer->token.token == 0)
			lexer = lexer->next;
		if (lexer && (lexer->token.token == 2 || lexer->token.token == 3))
		{
			(*parser)->outfile.outfile[i] = malloc(sizeof(char) * (ft_strlen(lexer->next->str) + 1));
			lexer = lexer->next->next;
			i++;
		}
		if (lexer && (lexer->token.token == 1 || lexer->token.token == 4))
		{
			(*parser)->infile.infile[j] = malloc(sizeof(char) * (ft_strlen(lexer->next->str) + 1));
			lexer = lexer->next->next;
			j++;
		}
	}
	(*parser)->outfile.outfile[i] = 0;
	(*parser)->infile.infile[j] = 0;
}

void fill2(t_lexer *lexer, t_parser **parser)
{
	int i;
	int a;
	int j;

	j =0;
	a = 0;
	alloc1(lexer, parser);
	while (lexer && lexer->token.token != 5)
	{
		i = 0;
		while (lexer && lexer->token.token == 0)
			lexer = lexer->next;
		if (lexer && (lexer->token.token == 2 || lexer->token.token == 3))
		{
			printf(" %s %s %d\n", lexer->str,lexer->next->str, lexer->token.token);
			while (lexer->next->str[i])
			{
				(*parser)->outfile.outfile[j][i] = lexer->next->str[i];
				i++;
			}
			(*parser)->outfile.outfile[j][i] = '\0';
			if (lexer->token.token == 2)
				(*parser)->outfile.flag[j] = 2;
			else
				(*parser)->outfile.flag[j] = 3;
			j++;
			lexer = lexer->next->next;
		}
		else if (lexer && (lexer->token.token == 1 || lexer->token.token == 4))
		{
			while (lexer->next->str[i])
			{
				(*parser)->infile.infile[a][i] = lexer->next->str[i];
				i++;
			}
			(*parser)->infile.infile[a][i] = '\0';
			if (lexer->token.token == 1)
				(*parser)->infile.flag[a] = 1;
			else
				(*parser)->infile.flag[a] = 4;
			a++;
			lexer = lexer->next->next;
		}
	}
}
void alloc(t_parser **parser, int infile, int outfile, t_lexer *lexer)
{
	(*parser)->infile.infile = malloc(sizeof(char *) * (infile + 1));
	(*parser)->outfile.outfile = malloc(sizeof(char *) * (outfile + 1));
	(*parser)->outfile.flag = malloc(sizeof(int) * outfile);
	(*parser)->infile.flag = malloc(sizeof(int) * infile);
	fill2(lexer,parser);
}
int	how_much_cmd(t_lexer *lexer, t_parser **parser)
{
	int i;
	int infile;
	int outfile;
	t_lexer *temp;

	i = 0;
	temp = lexer;
	outfile = 0;
	infile = 0;
	while (lexer && lexer->token.token != 5)
	{
		while (lexer && lexer->token.token == 0)
		{
			i++;
			lexer = lexer->next;
		}
		if (lexer && (lexer->token.token == 2 || lexer->token.token == 3))
		{
			lexer = lexer->next->next;
			outfile++;
		}
		else if (lexer && (lexer->token.token == 1 || lexer->token.token == 4))
		{
			lexer = lexer->next->next;
			infile++;
		}
	}
	alloc(parser, infile, outfile, temp);
	return (i);
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

void	fill(t_parser **new, t_lexer *lexer, int size)
{
	int i;
	int j;

	i = 0;
	if ( lexer && lexer->str == NULL)
		return;
	while (i < size -1)
	{
		j = 0;
		if ( i < size - 1&& lexer->token.token != 0 )
			lexer = lexer->next->next;
		while (lexer->str[j])
		{
			(*new)->str[i][j] = lexer->str[j];
			j++;
		}
		(*new)->str[i][j] = '\0';
		i++;
		lexer = lexer->next;
	}
}

t_parser	*ft_lstnewcmd(t_lexer *lexer)
{
	t_parser	*new;
	t_lexer *temp;
	int size;
	int i;

	i = 0;
	temp = lexer;
	new = (t_parser *)malloc(sizeof(t_parser));
	new->infile.infile = NULL;
	new->outfile.outfile = NULL;
	if (!new)
		return (NULL);
	size = how_much_cmd(lexer, &new) + 1;
	new->str = malloc(sizeof(char*) * size);
	while (i < size -1)
	{
		printf("%d %s\n", ft_strlen(lexer->str) + 1, lexer->str);
		new->str[i] = malloc(sizeof(char) * ft_strlen(lexer->str) + 1);
		i++;
		lexer = lexer->next;
		if ( i < size - 1 && lexer->token.token != 0 && lexer->token.token != 5)
			lexer = lexer->next->next;
	}
	new->str[i] = 0;
	fill(&new, temp, size);
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
	tmp = ft_lstlastcmd(*lst);
	tmp->next = new;
}


