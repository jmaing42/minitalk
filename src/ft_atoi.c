/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:34:22 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/23 02:34:36 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lib.h"

intmax_t	ft_atoi(const char *str)
{
	int			sgn;
	intmax_t	result;

	result = 0;
	sgn = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
	{
		str++;
		sgn = -1;
	}
	else if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
		result = result * 10 + (*str++ - '0') * sgn;
	return (result);
}
