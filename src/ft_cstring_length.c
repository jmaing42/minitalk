/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cstring_length.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:00:11 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/18 17:25:25 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cstring.h"

#include <limits.h>

static void	bake(const char *set, bool include_null, char *out)
{
	size_t				i;
	const unsigned char	*tmp;

	i = 0;
	while (i < (1 << CHAR_BIT))
		out[i++] = 0;
	if (include_null || !set)
		out[0] = 1;
	if (!set)
		return ;
	tmp = (const unsigned char *) set;
	while (*tmp)
		out[*tmp++] = 1;
}

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

size_t	ft_strlen_until(
	const char *str,
	const char *set,
	bool include_null
)
{
	size_t	result;
	char	baked[1 << CHAR_BIT];

	bake(set, include_null, baked);
	result = 0;
	while (!baked[*((const unsigned char *) str)])
	{
		str++;
		result++;
	}
	return (result);
}

size_t	ft_strnlen(const char *str, size_t max_len)
{
	size_t	result;

	result = 0;
	while (*str && max_len > result)
	{
		str++;
		result++;
	}
	return (result);
}

size_t	ft_strnlen_until(
	const char *str,
	const char *set,
	size_t max_len,
	bool include_null
)
{
	size_t	result;
	char	baked[1 << CHAR_BIT];

	bake(set, include_null, baked);
	result = 0;
	while (max_len > result && !baked[*((const unsigned char *) str)])
	{
		str++;
		result++;
	}
	return (result);
}
