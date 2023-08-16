/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laurmuss <laurmuss@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:31:02 by laurmuss          #+#    #+#             */
/*   Updated: 2023/08/16 18:58:37 by laurmuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

char *fill_buf(int fd, char *buf)
{
	char *storage;
	int read_char;				   // memorizzare il numero di caratteri letti in ogni iterazione del ciclo.
	//char storage[BUFFER_SIZE + 1]; // DICHIARIAMO UN ARRAY Di CARATTERI
	storage = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(!storage)
		return(true_free(&buf));

	storage[0] = '\0';
	read_char = 1;
	while (read_char > 0 && !ft_strchr(buf, '\n')) // continua finche ci sono caratteri e finche non si trova un a capo nel buf
	{
		read_char = read(fd, storage, BUFFER_SIZE); // read legge fino a buffer_size caratteri dall'fd e li immagazina dentr a storage.
													// read_char mi dice quanti caratteri sono stati letti
													// return (NULL);
		if (read_char == -1)
		{
			free(storage);
			return (true_free(&buf));
		}
		if (read_char > 0)
		{
			storage[read_char] = '\0';				   // alla fine di storage si aggiunge la fine
			buf = ft_strjoin(buf, storage, read_char); // per concatenare il contenuto di storage alla fine del buf il buff ricevera una nuova direzione di memoria quindi la liberiamo con il free;
		}
	}
	free(storage);
	return (buf);
}

char *copy_line(char *buf)
{
	char *line;
	int i;
	int x;

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

char *update_buf(char *buf)
{
	int i;
	char *newbuf;
	int j;

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

char *get_next_line(int fd)
{
	static char *buf = NULL;
	char *line;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (true_free(&buf));
	if (!buf || (buf && !ft_strchr(buf, '\n')))
		buf = fill_buf(fd, buf); // el fd e quello che era rimansto nella linea anteriore; si no hay buff retur
	if (!buf)
		return (NULL);
	line = copy_line(buf);
	if (!line)
		return (true_free(&buf));
	buf = update_buf(buf);
	return (line); // aqui tendriamo que devolver la linea
}
/*
int main(int args, char **argv)
{
	int fd1;
	char *line; // dichiarazione di un puntatore a char per memorizzare le linee lette
	int i;		// serve per contare le linee
	if (args != 2)
		return (1);
	fd1 = open(argv[1], O_RDONLY, 0);
	if (fd1 < 0)
		return (1);
	i = 0;
	line = get_next_line(fd1); // Legge una riga dal file utilizzando get_next_line finché non raggiunge la fine del file

	while (line != NULL)
	{
		printf("%s", line); // Stampa il numero della linæea e il contenuto della linea
		free(line);
		line = get_next_line(fd1); // legge la prossima linea
	}
	close(fd1);
	return (0);
}
*/