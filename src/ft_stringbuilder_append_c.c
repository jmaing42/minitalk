/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringbuilder_append_c.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:33:58 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/22 21:00:36 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stringbuilder.h"

#include "ft_cstring.h"

t_err	stringbuilder_append_c(t_stringbuilder *self, const char *str)
{
	return (stringbuilder_append_buffer(self, ft_strlen(str), str));
}
