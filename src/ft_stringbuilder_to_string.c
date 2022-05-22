/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringbuilder_to_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:59:01 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/23 02:04:08 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stringbuilder.h"

#include <stdlib.h>

#include "ft_memory.h"

t_string	*stringbuilder_to_string(t_stringbuilder *self, size_t offset)
{
	t_string *const			result
		= (t_string *)malloc(sizeof(t_string) + self->length - offset);
	t_stringbuilder_node	*node;
	size_t					position;

	if (!result)
		return (NULL);
	result->len = self->length - offset;
	if (!self->length)
		return (result);
	node = self->head;
	position = 0;
	ft_memcpy(
		(void *)&result->str[position],
		&node->str[offset],
		node->length - offset);
	position += node->length - offset;
	node = node->next;
	while (node)
	{
		ft_memcpy((void *)&result->str[position], node->str, node->length);
		position += node->length;
		node = node->next;
	}
	return (result);
}
