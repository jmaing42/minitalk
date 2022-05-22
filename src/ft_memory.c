/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 08:09:51 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/22 20:39:51 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	const size_t	total_size = count * size;
	void *const		result = malloc(total_size);

	if (!result)
		return (NULL);
	ft_bzero(result, total_size);
	return (result);
}

void	ft_bzero(void *mem, size_t len)
{
	ft_memset(mem, 0, len);
}

void	*ft_memset(void *mem, int value, size_t len)
{
	char	*ptr;

	ptr = (char *) mem;
	while (len--)
		*ptr++ = (signed char) value;
	return (mem);
}

void	ft_memcpy(void *dest, const void *source, size_t size)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = (char *) dest;
	s = (const char *) source;
	i = 0;
	while (i < size)
	{
		i++;
		*d++ = *s++;
	}
}

void	*ft_memdup(const void *mem, size_t len)
{
	void *const	result = malloc(len);

	if (result)
		ft_memcpy(result, mem, len);
	return (result);
}
