/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 08:52:59 by asolano-          #+#    #+#             */
/*   Updated: 2022/05/02 11:20:41 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	s = malloc(sizeof (char) * (i + 2));
	if (!s)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_save(char *str)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	s = malloc(sizeof (char) * (ft_strlen(str) - i + 1));
	if (!s)
		return (0);
	i++;
	c = 0;
	while (str[i])
		s[c++] = str[i++];
	s[c] = '\0';
	free(str);
	return (s);
}

char	*ft_read_and_save(int fd, char *str)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof (char));
	if (!buff)
		return (0);
	read_bytes = 1;
	while (!ft_strchr(str, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (0);
		}
		buff[read_bytes] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[257];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (0);
	str[fd] = ft_read_and_save(fd, str[fd]);
	if (!str[fd])
		return (0);
	line = ft_get_line(str[fd]);
	str[fd] = ft_save(str[fd]);
	return (line);
}
