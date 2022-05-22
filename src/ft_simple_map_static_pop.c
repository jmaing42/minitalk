/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_map_static_pop.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:01:04 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/12 03:32:35 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_simple_map_internal.h"

#include <stdlib.h>

static void	ft_simple_map_static_pop_internal_cleanup(
	t_ft_simple_map_static_value **current
)
{
	size_t	i;

	i = 0;
	while (i < (1 << CHAR_BIT))
		if ((*current)->value[i++])
			return ;
	free(*current);
	*current = NULL;
}

static bool	ft_simple_map_static_pop_internal(
	const t_ft_simple_map_static_context_get *context,
	t_ft_simple_map_static_value **current,
	size_t depth
)
{
	const size_t	index = ((unsigned char *) context->key)[depth];
	bool			error;

	if (!*current)
		return (true);
	if (depth + 1 == context->self->key_length)
	{
		if (context->out)
			*context->out = (*current)->value[index];
		(*current)->value[index] = NULL;
		error = false;
	}
	else
		error = ft_simple_map_static_pop_internal(
				context,
				&(*current)->array[index],
				depth + 1);
	ft_simple_map_static_pop_internal_cleanup(current);
	return (error);
}

bool	ft_simple_map_static_pop(
	t_ft_simple_map_static *self,
	void *key,
	void **out
)
{
	const t_ft_simple_map_static_context_get	context = {self, key, out};

	return (
		ft_simple_map_static_pop_internal(
			&context,
			&self->values,
			0
		)
	);
}
