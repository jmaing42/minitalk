/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringbuilder_to_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:59:01 by jmaing            #+#    #+#             */
/*   Updated: 2022/06/01 12:43:45 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stringbuilder.h"

#include <stdlib.h>

static void	ft_memcpy(void *dest, const void *source, size_t size)
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

char	*stringbuilder_to_string(t_stringbuilder *self, size_t offset)
{
	char *const				result = (char *)malloc(self->length - offset + 1);
	t_stringbuilder_node	*node;
	size_t					position;

	if (!result)
		return (NULL);
	result[self->length - offset] = '\0';
	if (!self->length)
		return (result);
	node = self->head;
	position = 0;
	ft_memcpy(
		(void *)&result[position],
		&node->str[offset],
		node->length - offset);
	position += node->length - offset;
	node = node->next;
	while (node)
	{
		ft_memcpy((void *)&result[position], node->str, node->length);
		position += node->length;
		node = node->next;
	}
	return (result);
}
