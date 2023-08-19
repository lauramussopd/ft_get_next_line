/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laurmuss <laurmuss@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:31:02 by laurmuss          #+#    #+#             */
/*   Updated: 2023/08/17 18:10:10 by laurmuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

char	*fill_buf(int fd, char *buf)
{
	char	*tmp;
	int		read_char;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (true_free(&buf));
	tmp[0] = '\0';
	read_char = 1;
	while (read_char > 0 && !ft_strchr(buf, '\n'))
	{
		read_char = read (fd, tmp, BUFFER_SIZE);
		if (read_char == -1)
		{
			free(tmp);
			return (true_free(&buf));
		}
		if (read_char > 0)
		{
			tmp[read_char] = '\0';
			buf = ft_strjoin(buf, tmp, read_char); 
		}
	}
	free(tmp);
	return (buf);
}

char	*copy_line(char *buf)
{
	char	*line;
	int		i;
	int		x;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	x = -1;
	while (++x < i)
		line[x] = buf[x];
	line[x] = '\0';
	return (line);
}

char	*update_buf(char *buf)
{
	int		i;
	char	*newbuf;
	int		j;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i] || !buf[i + 1])
		return (true_free(&buf));
	newbuf = malloc((ft_strlen(buf) - i + 1) * sizeof(char));
	if (!newbuf)
		return (true_free(&buf));
	j = 0;
	while (buf[++i])
		newbuf[j++] = buf[i];
	newbuf[j] = '\0';
	true_free(&buf);
	return (newbuf);
}

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (true_free(&buf));
	if (!buf || (buf && !ft_strchr(buf, '\n')))
		buf = fill_buf(fd, buf); 
	if (!buf)
		return (NULL);
	line = copy_line(buf);
	if (!line)
		return (true_free(&buf));
	buf = update_buf(buf);
	return (line); 
}
/*
int main(int args, char **argv)
{
	int fd1;
	char *line; 
	int i;		
	if (args != 2)
		return (1);
	fd1 =  open(argv[1], O_RDONLY, 0);
	if (fd1 < 0)
		return (1);
	i = 0;
	line = get_next_line(fd1); 

	while (line != NULL)
	{
		printf("%s", line); 
		free(line);
		line = get_next_line(fd1); 
	}
	close(fd1);
	return (0);
}
*/
