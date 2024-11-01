/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:09:07 by erahal            #+#    #+#             */
/*   Updated: 2024/11/01 16:12:40 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char	*ft_strdup(char *s)
// {
// 	char	*dup;
// 	int		i;

// 	i = 0;
// 	dup = malloc(sizeof(char) * ft_strlen(s) + 1);
// 	if (!dup)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }


void lst_printf(t_lexer *lexer)
{
    while (lexer)
    {
        printf("mot = %s token = %d index == %d\n", lexer->str, lexer->token.tocken, lexer->i);
        lexer = lexer->next;
    }
}
// int	ft_strchr_tokens(char *str)
// {
// 	int		i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i])
// 	{
// 		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
// 			return (1);
// 		i++;
// 	}
// 	if (str[i] == '<' || str[i] == '>' || str[i] == '|')
// 		return (1);
// 	else
// 		return (0);
// }

int    ft_split_len(char const *s, char c)
{
    size_t    i;
    int        count;
    int        is_delimiter;

    i = 0;
    count = 0;
    is_delimiter = 1;
    while (s[i])
    {
        if (is_delimiter && s[i] != c)
        {
            ++count;
            is_delimiter = !is_delimiter;
        }
        else if (!is_delimiter && s[i] == c)
        {
            is_delimiter = !is_delimiter;
        }
        ++i;
    }
    return (count);
}

// static size_t    ft_strlen_delim(char const *s, char c)
// {
//     size_t    i;

//     i = 0;
//     while (s[i] && s[i] != c)
//         ++i;
//     return (i);
// }

// void    ft_free_split(char **split)
// {
//     int    i;

//     i = 0;
//     while (split[i])
//     {
//         free(split[i]);
//         ++i;
//     }
//     free(split);
// }

// char    **ft_split(char *s, char c, t_lexer **lexer)
// {
//     size_t    i;
//     size_t    pos;

//     i = 0;
//     pos = 0;
//     while (s[i])
//     {
//         if (ft_strlen_delim(&s[i], c) > 0)
//         {
//             strs[pos] = ft_calloc(ft_strlen_delim(&s[i], c) + 1, sizeof(char));
//             if (!strs[pos])
//                 return (strs[pos] = NULL, ft_free_split(strs), NULL);
//             ft_memcpy(strs[pos], &s[i], ft_strlen_delim(&s[i], c));
//             i += ft_strlen_delim(&s[i], c);
//             ++pos;
//         }
//         else
//             ++i;
//     }
//     strs[pos] = NULL;
//     return (strs);
// }
