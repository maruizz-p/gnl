/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruiz-p <maruiz-p@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:53:16 by maruiz-p          #+#    #+#             */
/*   Updated: 2023/08/18 12:09:07 by maruiz-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*readline(int fd, char *txt)
{
	char	*aux;
	int		counter;

	counter = 1;
	aux = ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	if (!aux)
		return (free(txt), NULL);
	while (counter > 0 && !ft_strchr_gnl(aux, '\n'))
	{
		counter = read(fd, aux, BUFFER_SIZE);
		/*archivo a leer,
			donde vamos a almacenar la lectura y el tamaño de la lectura k keremos hacer. La funcion read nos devuelve el numero de caracteres leidos.*/
		if (counter < 0)
			return (free(aux), NULL);
		aux[counter] = '\0';
		// Para asegurarnos de k la cadena no se ha alterado con la funcion read.
		txt = ft_strjoin_gnl(txt, aux);
		if (!txt)
			return (free(txt), free(aux), NULL);
		//en caso de que en el calloc de strjoin haya fallos tenemos que comprobarlo.
	}
	return (free(aux), txt);
	/*no keremos memory leaks y para depurar el funcionamiento liberamos lo k no necesitamos,
		pues aux ya ha sido concatenado con txt.*/
}

char	*nextline(char *txt)
{
	char	*aux;
	int		counter;

	counter = 0;
	if (txt[counter] == '\0')
		return (NULL);
	while (txt[counter] != '\0' && txt[counter] != '\n')
		counter++;
	aux = ft_calloc_gnl((counter + 1 + (txt[counter] == '\n')), sizeof(char));
	/*en caso de que la ultima posicion sea un salto de linea nos va a sumar 1*/
	if (!aux)
		return (NULL);
	counter = 0;
	while (txt[counter] != '\0' && txt[counter] != '\n')
	{
		aux[counter] = txt[counter];
		counter++;
	}
	if (txt[counter] == '\n' && txt[counter] != '\0')
		aux[counter++] = '\n';
	aux[counter] = '\0';
	return (free(txt), aux);
}

char	*cleanbuffer(char *txt)
{
	char	*result;
	int		c1;
	int		c2;

	c1 = 0;
	while (txt[c1] != '\0' && txt[c1] != '\n')
		c1++;
	if (txt[c1] == '\0')
		return (free(txt), NULL);
	c2 = 0;
	result = ft_calloc_gnl((ft_strlen_gnl(txt) - c1 + 1), sizeof(char));
	if (!result)
		return (free(txt), NULL);
	c2 = 0;
	while (txt[++c1] != '\0')
		result[c2++] = txt[c1];
	result[c2] = '\0';
	return (free(txt), result);
}

char	*get_next_line(int fd)
{
	static char	*txt;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (txt != NULL)
		{
			free(txt);
			txt = NULL;
		}
		return (NULL);
	}
	txt = readline(fd, txt);
	if (!txt)
		return (free(txt), txt = NULL, NULL);
	result = nextline(txt);
	if (!result)
		return (free(txt), txt = NULL, NULL);
	txt = cleanbuffer(txt);
	if (!txt)
		return (free(txt), txt = NULL, result);
	return (result);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		tester;
	char	*written_line;

	tester = open("test.txt", O_RDONLY);
	written_line = get_next_line(tester);
	while (written_line != NULL)
	{
		printf("%s", written_line);
		written_line = get_next_line(tester);
	}
	printf("\n");
	close(tester);
	free(written_line);
}
