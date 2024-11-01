/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:40:18 by erahal            #+#    #+#             */
/*   Updated: 2024/11/01 16:47:31 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int ft_free(char *s)
{
	free(s);
	return (1);
}
int ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return(i);
}

char	*ft_strdup(char *s)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}


char	*ft_joinstrcpy(char *s1, char *s2, char *s3, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	if (n == 2)
		s1[i++] = '@';
	while (s3[j])
	{
		s1[i] = s3[j];
		j++;
		i++;
	}
	if (n == 2)
		s1[i++] = ':';
	if (n == 1 && ft_free(s2) && ft_free(s3))
		s1[i++] = '$';
	s1[i] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2, int n)
{
	char	*str;
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1 + n));
	if (!str)
		return (NULL);
	str = ft_joinstrcpy(str, s1, s2, n);
	if (n == 0)
		free(s1);
	return (str);
}
