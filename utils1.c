/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahal <erahal@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:09:07 by erahal            #+#    #+#             */
/*   Updated: 2024/11/04 11:48:15 by erahal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_promt(char *line, char *promt, t_lexer **lexer)
{
    free(promt);
    free(line);
    lst_free(lexer);
}


void lst_printf(t_lexer *lexer)
{
    while (lexer)
    {
        printf("mot = %s token = %d index == %d\n", lexer->str, lexer->token.tocken, lexer->i);
        lexer = lexer->next;
    }
}
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

