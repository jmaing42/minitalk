/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringbuilder_new.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:33:58 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/23 01:53:04 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stringbuilder.h"

#include <stdlib.h>

#define MINIMUM_BUFFER_SIZE 1024

t_stringbuilder	*new_stringbuilder(size_t buffer_size)
{
	t_stringbuilder *const	result
		= (t_stringbuilder *)malloc(sizeof(t_stringbuilder));

	if (!result)
		return (NULL);
	result->length = 0;
	result->head = NULL;
	result->tail = NULL;
	result->buffer_size = buffer_size;
	if (MINIMUM_BUFFER_SIZE > buffer_size)
		result->buffer_size = MINIMUM_BUFFER_SIZE;
	return (result);
}
