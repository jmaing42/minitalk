/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_map_static_set.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:01:04 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/17 18:24:10 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_simple_map_internal.h"

#include <stdlib.h>

static void	*ft_calloc(size_t count, size_t size)
{
	const size_t	total_size = count * size;
	char *const		result = (char *)malloc(total_size);
	size_t			i;

	if (!result)
		return (NULL);
	i = 0;
	while (i < total_size)
		result[i++] = 0;
	return (result);
}

static bool	ft_simple_map_static_set_internal(
	const t_ft_simple_map_static_context_set *context,
	t_ft_simple_map_static_value **current,
	size_t depth
)
{
	const size_t	index = ((unsigned char *) context->key)[depth];
	const bool		fresh = !*current;
	bool			error;

	if (fresh)
		*current = (t_ft_simple_map_static_value *)
			ft_calloc(1, sizeof(t_ft_simple_map_static_value));
	if (!*current)
		return (true);
	if (depth + 1 == context->self->key_length)
	{
		if ((*current)->value[index])
			return (true);
		(*current)->value[index] = context->value;
		return (false);
	}
	error = ft_simple_map_static_set_internal(
			context,
			&(*current)->array[index],
			depth + 1);
	if (!(error && fresh))
		return (error);
	free(*current);
	*current = NULL;
	return (error);
}

bool	ft_simple_map_static_set(
	t_ft_simple_map_static *self,
	void *key,
	void *value
)
{
	const t_ft_simple_map_static_context_set	context = {self, key, value};

	return (
		ft_simple_map_static_set_internal(
			&context,
			&self->values,
			0
		)
	);
}
