/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:29:33 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/23 02:31:48 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"

static t_err	internal(int fd, intmax_t i)
{
	int	sgn;

	if (!i)
		return (0);
	sgn = 1;
	if (i < 0)
		sgn = -1;
	return (
		internal(fd, i / 10)
		|| ft_write(fd, &"0123456789"[(i % 10) * sgn], 1)
	);
}

t_err	ft_put_number(int fd, intmax_t i)
{
	if (!i)
		return (ft_put_string(fd, "0"));
	if (i < 0 && ft_put_string(fd, "-"))
		return (true);
	return (internal(fd, i));
}
