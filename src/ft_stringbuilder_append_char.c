/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringbuilder_append_char.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:59:01 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/22 21:40:37 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stringbuilder.h"

t_err	stringbuilder_append_char(t_stringbuilder *self, char c)
{
	return (stringbuilder_append_buffer(self, 1, &c));
}
