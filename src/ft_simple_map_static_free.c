/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_map_static_free.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:01:04 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/15 02:28:41 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_simple_map_internal.h"

#include <stdlib.h>

static void	ft_simple_map_static_free_internal(
	t_ft_simple_map_static_value *current,
	void (*free_value)(void *value),
	size_t remain_depth
)
{
	size_t	i;

	if (!current)
		return ;
	i = 0;
	if (!remain_depth)
	{
		while (i < (1 << CHAR_BIT))
		{
			if (current->value[i])
				free_value(current->value[i]);
			i++;
		}
	}
	else
		while (i < (1 << CHAR_BIT))
			ft_simple_map_static_free_internal(
				current->array[i++],
				free_value,
				remain_depth - 1
				);
	free(current);
}

void	ft_simple_map_static_free(
	t_ft_simple_map_static *self,
	void (*free_value)(void *value)
)
{
	ft_simple_map_static_free_internal(
		self->values,
		free_value,
		self->key_length - 1
		);
	free(self);
}
