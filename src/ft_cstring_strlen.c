/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cstring_strlen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:00:11 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/02 15:25:46 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cstring.h"

#include <limits.h>

#include "ft_byte_map.h"

size_t	ft_strlen(const char *str)
{
	size_t	result;

	result = 0;
	while (*str)
	{
		str++;
		result++;
	}
	return (result);
}

size_t	ft_strlen_until_set(
	const char *str,
	const char *set,
	bool include_null
)
{
	t_byte	map[1 << CHAR_BIT];

	ft_byte_map(map, include_null, (t_byte *) set);
	return (ft_strlen_until_map(str, map));
}

size_t	ft_strlen_until_map(
	const char *str,
	const t_byte *map
)
{
	size_t	result;

	result = 0;
	while (!map[*((t_byte *) str)])
	{
		str++;
		result++;
	}
	return (result);
}
