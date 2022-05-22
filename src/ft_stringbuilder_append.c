/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringbuilder_append.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:33:58 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/22 21:00:47 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stringbuilder.h"

t_err	stringbuilder_append(t_stringbuilder *self, t_string *str)
{
	return (stringbuilder_append_buffer(self, str->len, str->str));
}
