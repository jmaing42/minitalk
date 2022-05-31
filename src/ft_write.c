/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:28:13 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/31 16:39:50 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_io.h"

#define WRITE_SIZE_MAX 1048576

t_err	ft_write(
	int fd,
	const void *buf,
	size_t len
)
{
	size_t		remain;
	size_t		to_write;
	ssize_t		wrote;
	const char	*str;

	str = (const char *) buf;
	remain = len;
	while (remain)
	{
		to_write = remain;
		if (to_write > WRITE_SIZE_MAX)
			to_write = WRITE_SIZE_MAX;
		wrote = write(fd, str, to_write);
		if (wrote < 0)
			return (true);
		remain -= (size_t) wrote;
		str = str + wrote;
	}
	return (false);
}
