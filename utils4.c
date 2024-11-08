#include "minishell.h"

void	*ft_calloc(size_t nb, size_t size)
{
	void	*tab;

	if ((nb >= 65535 && size >= 65535) || nb * size >= 65535)
		return (NULL);
	tab = malloc(nb * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, size * nb);
	return (tab);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (dest);
	i = 0;
	while (i < n)
	{
		((char *) dest)[i] = ((char *) src)[i];
		i++;
	}
	return (dest);
}

void	ft_bzero(void *s1, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s1)[i] = '\0';
		i++;
	}
}




