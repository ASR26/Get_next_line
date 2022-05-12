/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 08:49:07 by asolano-          #+#    #+#             */
/*   Updated: 2022/05/12 08:49:11 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

unsigned int	ft_strlen(const char *s)
{
	unsigned int	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	*ft_memcpy(void *dst, const void *src, unsigned int n)
{
	unsigned char	*tmp;
	unsigned char	*src_tmp;

	if (dst == 0 && src == 0)
		return (0);
	tmp = (unsigned char *) dst;
	src_tmp = (unsigned char *) src;
	while (n > 0)
	{
		*tmp++ = *src_tmp++;
		n--;
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == c)
			return (ptr);
		ptr++;
	}
	if (*ptr == c)
		return (ptr);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	size;
	char			*ptr;
	int				i;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = (char *) malloc(sizeof(char) * size);
	if (ptr == 0)
		return (ptr);
	i = 0;
	while (*s1)
		ptr[i++] = *s1++;
	while (*s2)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}

int	ft_line_len(char *ptr)
{
	int	len;

	len = 0;
	while (ptr[len] && ptr[len] != '\n')
		len++;
	if (ptr[len] == '\n')
		len++;
	return (len);
}
