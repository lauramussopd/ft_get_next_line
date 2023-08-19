/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laurmuss <laurmuss@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:35:35 by laurmuss          #+#    #+#             */
/*   Updated: 2023/08/17 17:26:10 by laurmuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

char	*ft_strchr(const char *str, int c)
{
	if (str && *str)
	{
		while (*str && *str != c)
			str++;
		if (!*str && c != '\0')
			return (0);
	}
	return ((char *) str);
}

void	*true_free(char **buffer)
{
	if (buffer && *buffer) 
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

char	*ft_strjoin(char *buffer, char *tail, ssize_t size)
{
	int		i;
	int		j;
	char	*tmp;

	if (!buffer)
	{
		buffer = malloc(sizeof(char));
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	tmp = malloc((ft_strlen(buffer) + size + 1) * sizeof(char)); 
	if (!tmp)
		return (true_free(&buffer));
	i = -1;
	while (buffer[++i])
		tmp[i] = buffer[i];
	j = -1;
	while (tail[++j])
		tmp[i++] = tail[j];
	true_free(&buffer);
	tmp[i] = '\0';
	return (tmp);
}
