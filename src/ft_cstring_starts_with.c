/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cstring_starts_with.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 02:09:20 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 02:16:46 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cstring.h"

bool	ft_cstring_starts_with(const char *str, const char *starts_with)
{
	while (*str && *starts_with && *str == *starts_with)
	{
		str++;
		starts_with++;
	}
	return (!*starts_with);
}
