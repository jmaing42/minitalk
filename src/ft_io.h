/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:50:32 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/31 16:39:50 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IO_H
# define FT_IO_H

# include <stddef.h>
# include <stdint.h>

# include "ft_types.h"

t_err	ft_write(int fd, const void *buf, size_t len);
t_err	ft_put_string(int fd, const char *str);
t_err	ft_put_number(int fd, intmax_t n);
t_err	ft_put_multiline(int fd, const char *str, const void *prefix, size_t l);

#endif
