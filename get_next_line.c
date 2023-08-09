/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laurmuss <laurmuss@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:31:02 by laurmuss          #+#    #+#             */
/*   Updated: 2023/08/09 16:31:07 by laurmuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	l;

	l = 0;
	while (s[l] != '\0')
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
	if (buffer && *buffer) //lo que t mando y el contenido de lo que te mando 
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
		buffer = malloc(sizeof(char));
	if (!buffer)
		return (NULL);
	tmp = malloc((ft_strlen(buffer) + size + 1) * sizeof(char)); //lo que tiene el buffer + algo
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



char *fill_first_line(int fd, char *buf)
{
    int read_char;
    char storage[BUFFER_SIZE + 1];
    
    storage[0] = '\0';
    read_char = 1;
    while (read_char > 0 && !ft_strchr(buf, '\n'))
    {  
    read_char = read(fd, storage, BUFFER_SIZE); //int + arreglo depoita en storage buffer_size elements leidos en el fd y devuelve a read char la cantiad de elelemnts leidos.
    if (read_char < 0)
      return (NULL);
    storage[read_char] = '\0';
    buf = ft_strjoin(buf, storage, read_char); // il buff ricevera una nuova direzione di memoria quindi la liberiamo con il free;
    }
    return(buf);
}



char *get_next_line(int fd)
{
    char *line; //lo que vamos a devolver
    static char *buf = NULL;

   // if check(si hay el file, si el fd sta bien)
   // return (NULL);
    buf = fill_first_line(fd, buf); //el fd e quello che era rimansto nella linea anteriore; si no hay buff retur
    if(!buf)
        return (NULL);
 /*  line = copy_first_line(buf);
    if(!line)
        return(NULL);
    buf = update_buf(buf);
    if(!buf)
    return(NULL);*/
    return(buf);
}
int main (int args, char **argv)
{
    int fd1;
    char    *line; //dichiarazione di un puntatore a char per memorizzare le linee lette
    int i; // serve per contare le linee
    if (args != 2)
        return (1);
    fd1 = open(argv[1], O_RDONLY, 0);
    if (fd1 < 0)
        return (1);
    i = 1;
    line = get_next_line(fd1); // Legge una riga dal file utilizzando get_next_line finché non raggiunge la fine del file

    //while (line)
   // {
        printf("line [%02d]: %s \n", i, line); // Stampa il numero della linea e il contenuto della linea
        free(line);
   //     line = get_next_line(fd1);    //legge la prossima linea
   // }
    close(fd1);
    return (0);
}
/*
    if(fd == -1)
    {
        printf("Error al abrir el archivo \n");
    }
    else
    {
        nr_bytes = read(fd, buf, 10);
        close(fd);

        if(nr_bytes == 0)
        {
            printf("archivo vacio \n");
        }
        else
        {
            printf("el numero de characteres es %d, el contenido %s \n", (int)nr_bytes, buf);
        }
    }
    return 0;
}
*/
