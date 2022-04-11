/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:33:10 by jibot             #+#    #+#             */
/*   Updated: 2022/04/11 16:36:36 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*tab;
	size_t	i;

	tab = malloc(size * count);
	i = 0;
	while (i < size * count)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
}

static char	*strseg(const char *str, char c)
{
	int		i;
	char	*tab;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	tab = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (str[i] && str[i] != c)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

static unsigned int	size_count(const char *str, char c)
{
	unsigned int	i;
	unsigned int	size;

	i = 0;
	size = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c)
		{
			size++;
			while (str[i] == c)
				i++;
			if (str[i] == '\0')
				return (size);
		}
		i++;
	}
	if (str[i] == '\0' && str[i - 1] != c)
		size++;
	return (size);
}

char	**ft_split(char const *s, char c)
{
	int				i;
	unsigned int	n;
	char			**ftab;

	if (!s)
		return (NULL);
	else if (s[0] == '\0' || (s[0] == '\0' && c == '\0'))
	{
		ftab = malloc(sizeof(char *));
		ftab[0] = NULL;
		return (ftab);
	}
	i = 0;
	n = 0;
	ftab = ft_calloc(size_count(s, c) + 1, sizeof(char *));
	while (n < size_count(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		ftab[n++] = strseg(s + i, c);
		while (s[i] && s[i] != c)
			i++;
	}
	ftab[n] = NULL;
	return (ftab);
}
