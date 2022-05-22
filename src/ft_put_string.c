/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:28:40 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/23 02:47:51 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"

#include "ft_cstring.h"

t_err	ft_put_string(int fd, const char *str)
{
	return (ft_write(fd, str, ft_strlen(str)));
}
