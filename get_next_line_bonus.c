/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 08:48:25 by asolano-          #+#    #+#             */
/*   Updated: 2022/05/12 08:48:30 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

void	ft_clean_memory(char **memory)
{
	char	*new_memo;
	int		len;
	int		new_size;

	if (*memory == NULL)
	{
		*memory = (char *) malloc (sizeof(char));
		**memory = '\0';
		return ;
	}
	len = ft_line_len(*memory);
	new_size = ft_strlen(&(*memory)[len]) + 1;
	new_memo = (char *) malloc(sizeof(char) * new_size);
	ft_memcpy(new_memo, &(*memory)[len], new_size);
	free(*memory);
	*memory = new_memo;
}

int	ft_fill_memory(char **memory, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		ret;
	char	*tmp;

	ft_clean_memory(memory);
	ret = 1;
	while (!ft_strchr(*memory, '\n') && ret)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 1)
			return (ret);
		buffer[ret] = '\0';
		tmp = *memory;
		*memory = ft_strjoin(*memory, buffer);
		free(tmp);
	}
	return (ret);
}

char	*ft_get_line(char **memory)
{
	char	*line;
	int		len;
	int		i;

	len = ft_line_len(*memory);
	if (len == 0)
		return (NULL);
	line = (char *) malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		line[i] = (*memory)[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*memory[256] = {0};
	char		*line;

	if (fd < 0 || fd > 255)
		return (NULL);
	if (ft_fill_memory(&memory[fd], fd) == -1)
	{
		free(memory[fd]);
		memory[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(&memory[fd]);
	if (!line)
	{
		free(memory[fd]);
		memory[fd] = NULL;
	}
	return (line);
}
