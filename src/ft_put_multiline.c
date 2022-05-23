/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_multiline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 08:16:22 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/23 08:32:36 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"

#include <stddef.h>
#include <stdbool.h>

#include "ft_byte_map.h"
#include "ft_cstring.h"

t_err	ft_put_multiline(int fd, const char *str, const void *prefix, size_t l)
{
	size_t	length;
	t_byte	map[1 << CHAR_BIT];

	ft_byte_map(map, true, (t_byte *) "\n");
	while (true)
	{
		length = ft_strlen_until_map(str, map);
		if (ft_write(fd, str, length))
			return (true);
		str += length;
		if (!*str)
			return (false);
		str++;
		if (ft_write(fd, "\n", 1)
			|| ft_write(fd, prefix, l))
			return (true);
	}
}
