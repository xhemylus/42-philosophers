/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollen <abollen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:08:00 by abollen           #+#    #+#             */
/*   Updated: 2022/01/20 16:51:58 by abollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnlstrjoin(char *s1, char const *s2)
{
	char	*dst;
	int		i;
	int		len;

	i = -1;
	if (!s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	if (s1 != NULL)
		while (s1[++i])
			dst[i] = s1[i];
	i = -1;
	while (s2[++i])
		dst[i + ft_strlen(s1)] = s2[i];
	dst[i + ft_strlen(s1)] = '\0';
	if (s1)
		free(s1);
	return (dst);
}

static int	ft_endline(char *src)
{
	int	i;

	i = -1;
	if (!src)
		return (-1);
	while (src[++i])
	{
		if (src[i] == '\n')
			return (i);
	}
	return (-1);
}

static char	*out(char *line, char **rest)
{
	int		i;
	char	*dst;
	int		j;

	i = 1;
	while (line[i - 1] != '\n' && line[i])
		i++;
	j = i;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (ft_multifree(1, line));
	dst[i] = '\0';
	while (--i >= 0)
		dst[i] = line[i];
	if ((int)ft_strlen(line) > j)
	{
		rest[0] = ft_strdup(line + j);
		if (!rest[0])
			return (ft_multifree(2, line, dst));
	}
	free(line);
	return (dst);
}

static int	ft_rest_manager(char **line, char **rest, int fd)
{
	*line = ft_strdup(rest[fd]);
	free(rest[fd]);
	rest[fd] = NULL;
	if (!(*line))
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*rest[4096];
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int			ret;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, buffer, 0))
		return (NULL);
	line = NULL;
	ret = BUFFER_SIZE;
	while (ft_endline(line) == -1 && ret == BUFFER_SIZE)
	{
		if (rest[fd])
			if (ft_rest_manager(&line, rest, fd) == 0)
				return (NULL);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		if (ft_endline(line) == -1)
			ret = read(fd, buffer, BUFFER_SIZE);
		if ((ret > 0))
			line = ft_gnlstrjoin(line, (char *)buffer);
		else if (ret == 0 && !line)
			return (NULL);
		if (!line)
			return (NULL);
	}
	return (out(line, &rest[fd]));
}
