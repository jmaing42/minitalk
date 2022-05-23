/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_byte_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:54:01 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/23 08:29:14 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_byte_map.h"

#include <stddef.h>
#include <limits.h>

#include "ft_types.h"

void	ft_byte_map(t_byte *out, bool include_null, const t_byte *set)
{
	size_t			i;
	const t_byte	*tmp;

	i = 0;
	while (i < 1 << CHAR_BIT)
		out[i++] = 0;
	if (include_null)
		out[0] = 1;
	if (!set)
		return ;
	tmp = (const unsigned char *) set;
	while (*tmp)
		out[*tmp++] = 1;
}
