/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddehili <ddehili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:51:53 by ddehili           #+#    #+#             */
/*   Updated: 2026/01/10 14:29:10 by ddehili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ret_rest(char *rest)
{
	if (!rest)
		return (NULL);
	while (*rest)
	{
		if (*rest == '\n')
			return (rest + 1);
		rest++;
	}	
	return (NULL);
}

void	ft_strncpy(char *dst, const char *src, int siz)
{
	int	i;

	i = 0;
	if (!dst || !src || siz <= 0)
		return ;
	if (!src || siz <= 0)
	{
		dst[0] = '\0';
		return ;
	}
	while (i < siz && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*avant_apre(char **rest, char *ptr)
{
	char	*line;
	char	*new_rest;
	size_t	len_line;

	if (!rest || !*rest || !ptr || ptr < *rest)
		return (NULL);
	if ((ptr - *rest) > ft_strlen(*rest))
		return (NULL);
	len_line = (size_t)(ptr - *rest);
	line = malloc(len_line + 1);
	if (!line)
		return (NULL);
	ft_strncpy(line, *rest, len_line);
	new_rest = ft_strdup(ptr);
	if (!new_rest)
		return (free(line), free(*rest), *rest = NULL, NULL);
	return (free(*rest), *rest = new_rest, line);
}

static char	*read_loop(int fd, char **rest)
{
	char	*buff;
	int		byte;
	char	*ptr;

	if (!rest || !*rest)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	byte = read(fd, buff, BUFFER_SIZE);
	while (byte > 0)
	{
		buff[byte] = '\0';
		*rest = strjoin(*rest, buff);
		if (!*rest)
			return (free(buff), NULL);
		ptr = ret_rest(*rest);
		if (ptr)
			return (free(buff), avant_apre(rest, ptr));
		byte = read(fd, buff, BUFFER_SIZE);
	}
	if (byte < 0)
		return (free(*rest), free(buff), ptr = NULL, *rest = NULL, NULL);
	return (free(buff), NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*res;
	char		*ptr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest)
	{
		rest = ft_strdup("");
		if (!rest)
			return (NULL);
	}
	ptr = ret_rest(rest);
	if (ptr)
		return (avant_apre(&rest, ptr));
	res = read_loop(fd, &rest);
	if (res)
		return (res);
	if (rest && *rest != '\0')
		return (res = rest, rest = NULL, (res));
	return (free(rest), ptr = NULL, rest = NULL, NULL);
}
// #include <stdio.h>
// int main()
// {
// 	char *c;
// 	int	fd = open("text.txt", O_RDONLY);
// 	for( int i = 0; i < 50; i++)
// 	{
// 		c = get_next_line(fd);
// 		printf("nl:%s" , c);
// 		free(c);
// 	}
// }