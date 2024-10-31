/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tovetouc <tovetouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:41:40 by tovetouc          #+#    #+#             */
/*   Updated: 2024/10/31 15:19:29 by tovetouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
	{
		++i;
	}
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
	{
		((unsigned char *) b)[i] = (unsigned char) c;
		++i;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count != 0 && (count * size) / count != size)
		return (NULL);
	mem = malloc(size * count);
	if (!mem)
		return (NULL);
	ft_memset(mem, 0, size * count);
	return (mem);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return ((char *) ft_calloc(1, sizeof(char)));
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	str[i++] = '\n';
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		++j;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*built_env(char **envp)
{
	int		i;
	char	*str;
	
	i = 0;
	str = NULL;
	while (envp[i])
	{
		str = ft_strjoin(str, envp[i]);
		++i;
	}
	printf(str);
	free(str);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*str;

// 	str = env(envp);
// 	printf("%s\n", str);
// 	free(str);
// }
