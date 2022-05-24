/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringbuilder_append_buffer.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:59:01 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/24 22:40:22 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stringbuilder.h"

#include <stdlib.h>

#include "ft_memory.h"

static t_stringbuilder_node	*alloc(
	t_stringbuilder *self,
	size_t length,
	const char *buffer
)
{
	t_stringbuilder_node	*node;
	size_t					size;

	size = length;
	if (length < self->buffer_size)
		size = self->buffer_size;
	node = (t_stringbuilder_node *)malloc(sizeof(t_stringbuilder_node) + size);
	if (!node)
		return (NULL);
	node->next = NULL;
	node->capacity = size;
	ft_memcpy(node->str, buffer, length);
	node->length = length;
	if (self->tail)
		self->tail->next = node;
	else
		self->head = node;
	self->tail = node;
	return (node);
}

t_err	stringbuilder_append_buffer(
	t_stringbuilder *self,
	size_t len,
	const char *buffer
)
{
	t_stringbuilder_node *const	tail = self->tail;
	size_t						offset;
	t_stringbuilder_node		*new_tail;

	offset = 0;
	if (self->tail)
		offset = self->tail->capacity - self->tail->length;
	if (offset >= len)
	{
		ft_memcpy(&self->tail->str[self->tail->length], buffer, len);
		self->tail->length += len;
		self->length += len;
		return (false);
	}
	new_tail = alloc(self, len - offset, &buffer[offset]);
	if (!new_tail)
		return (true);
	if (offset)
	{
		ft_memcpy(&tail->str[tail->length], buffer, offset);
		tail->length += offset;
	}
	self->length += len;
	return (false);
}
