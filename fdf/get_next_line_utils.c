/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddehili <ddehili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:51:49 by ddehili           #+#    #+#             */
/*   Updated: 2026/01/10 14:29:08 by ddehili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		l;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	l = 0;
	while (l < i)
	{
		str[l] = s[l];
		l++;
	}
	str[l] = '\0';
	return (str);
}

char	*strjoin(char *rest, char *buffer)
{
	char	*temp;
	int		l;
	int		lb;
	int		i;

	if (!rest || !buffer)
		return (NULL);
	i = 0;
	l = ft_strlen(rest);
	lb = ft_strlen(buffer);
	temp = malloc(sizeof(char) *(lb + l) + 1);
	if (!temp)
		return (free(rest), NULL);
	while (i < l)
	{
		temp[i] = rest[i];
		i++;
	}
	while (i < lb + l)
	{
		temp[i] = buffer[i - l];
		i++;
	}
	temp[i] = '\0';
	return (free(rest), temp);
}
