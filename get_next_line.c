/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 08:47:18 by asolano-          #+#    #+#             */
/*   Updated: 2022/05/12 08:47:24 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

/* 
 * This function will "clean" the memory, so it only contains the remaining
 * characters after the first line found (delimited by '\n')
 */
void	ft_clean_memory(char **memory)
{
	char	*new_memo; //this will be the new memory
	int		len; //this is the len of the first line on the current memory
	int		new_size; // this is the size of the remaining content on the memory after the line

	//if memory is empty we fill it with an end of string '\0'
	if (*memory == NULL)
	{
		*memory = (char *) malloc (sizeof(char));
		**memory = '\0';
		return ;
	}
	//else
	len = ft_line_len(*memory); //we asign the length of the first line on memory to 'len'
	new_size = ft_strlen(&(*memory)[len]) + 1; //we asign the length of the rest of the memory (+1 for the '\0' final character) to 'new_size'
	new_memo = (char *) malloc(sizeof(char) * new_size); //we allocate memory for the new memory in 'new_memo'
	ft_memcpy(new_memo, &(*memory)[len], new_size); //we copy the rest of the memory (after the first line) to 'new_memo'
	free(*memory); //we free the old memory
	*memory = new_memo; //we reasign the pointer to the new memory
}

/*
 * This function will fill the memory using the buffer size, reading from the file descriptor
 */
int	ft_fill_memory(char **memory, int fd)
{
	char	buffer[BUFFER_SIZE + 1]; //this will be the buffer so we asign it buffer size (+1 for '\0')
	int		ret; //this will be the return value
	char	*tmp; //this will be a holder for freeing the old memory during the iteration

	ft_clean_memory(memory); //we clean the memory so we start from the next line (first line if it's the first use of the function)
	ret = 1; //we asign ret value 1
	while (!ft_strchr(*memory, '\n') && ret) //while we don't find '\n' character in memory and ret value is not 0
	{
		ret = read(fd, buffer, BUFFER_SIZE); //we asign ret the number of bytes read by 'read' function (BUFFER_SIZE or end of file), and copy these bytes into buffer
		if (ret < 1) //if ret is 0 or -1, meaning the file is empty (0) or read returned an error (-1)
			return (ret); //we return that value to finish the iteration
		buffer[ret] = '\0'; //we add '\0' at the end of buffer, so it's a line with a proper end
		tmp = *memory; //we asign 'tmp' to 'memory' direction so we can free it later
		*memory = ft_strjoin(*memory, buffer); //we join the buffer (new characters taken from read) to memory (everything we've read until now)
		free(tmp); //we free the old 'memory' so we don't have any leaks
	}
	return (ret); //once we finish the iteration we return 'ret' value
}

/*
 * This function finds a line and return it
 */
char	*ft_get_line(char **memory)
{
	char	*line; //this will be the line
	int		len; //this will be the length of the line
	int		i; //this will be an iterator

	len = ft_line_len(*memory); //we asign the size of the first line found in 'memory' to 'len
	if (len == 0) //if 'len is 0 it means the first line is empty so we return 'NULL'
		return (NULL);
	line = (char *) malloc(sizeof(char) * (len + 1)); // if 'len' is > 0 we allocate memory for the new line (+1 for '\0')
	i = 0; //we start the iterator to 0
	while (i < len) //while iterator is less than 'len'
	{
		line[i] = (*memory)[i]; //we copy each character from memory into line
		i++; //increase the iterator
	}
	line[i] = '\0'; //for the last value we asign a '\0' so the line is ended
	return (line); //we return the line
}

/*
 * This fuction is the main function which returns next line
 */
char	*get_next_line(int fd)
{
	static char	*memory = NULL; //this will be the memory where we'll hold the file content after the file descriptor given, 
	//it is static so it will not be deleted during the whole program execution
	char		*line; //this will be the line to return

	if (ft_fill_memory(&memory, fd) == -1) //if fill memory function returns -1 means an error
	{
		free(memory); //we free memory
		memory = NULL; //we set memory pointer to NULL
		return (NULL); //we return NULL
	}
	line = ft_get_line(&memory); //once the memory is filled properly we find the line and asign it to line
	if (!line) //if line is empty
	{
		free(memory); //we free memory
		memory = NULL; //we set memory pointer to  NULL
	}
	return (line); //we return the line
}
