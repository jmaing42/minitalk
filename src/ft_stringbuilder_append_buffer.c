/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringbuilder_append_buffer.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:59:01 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/22 22:21:45 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stringbuilder.h"

#include <stdlib.h>

t_string		*stringbuilder_to_string(t_stringbuilder *self, size_t offset);
const char		*stringbuilder_to_cstring(t_stringbuilder *self, size_t offset);

t_err	stringbuilder_append_buffer(
	t_stringbuilder *self,
	size_t length,
	const char *buffer
)
{
	size_t	remain;

	if (self->tail && self->tail->capacity - self->tail->length >= self->length)
	{
		// TODO:
	}
}
