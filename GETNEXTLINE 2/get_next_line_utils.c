/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruiz-p <maruiz-p@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:32:02 by maruiz-p          #+#    #+#             */
/*   Updated: 2023/08/18 12:15:42 by maruiz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *str)
{
	int	c;

	c = 0;
	while (str[c])
		c++;
	return (c);
}

void	ft_bzero_gnl(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero_gnl(ptr, count * size);
	return (ptr);
}

int	ft_strchr_gnl(const char *s, int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	while (*s)
	{
		if (*s == ch)
			return (1);
		s++;
	}
	if (ch == '\0')
		return (0);
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	s1_len;
	char	*result;
	int		i;

	if (!s1)
	{
		s1 = ft_calloc_gnl(1, sizeof(char));
		if (!s1)
			return (free(s1), s1 = NULL, NULL);
	}
	if (!s2)
		return (free(s1), s1 = NULL, NULL);
	s1_len = ft_strlen_gnl(s1);
	result = (char *)ft_calloc_gnl((s1_len + ft_strlen_gnl(s2) + 1),
			sizeof(char));
	if (!result)
		return (free(s1), s1 = NULL, NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	i = -1;
	while (s2[++i])
		result[s1_len + i] = s2[i];
	result[s1_len + i] = '\0';
	return (free(s1), result);
}
