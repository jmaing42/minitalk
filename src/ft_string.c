/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:35:54 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/22 20:40:39 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

#include <stdlib.h>

#include "ft_cstring.h"
#include "ft_memory.h"

t_string	*ft_string_from_cstring(const char *str)
{
	const size_t	length = ft_strlen(str);
	t_string *const	result = (t_string *)malloc(sizeof(t_string) + length);

	if (!result)
		return (NULL);
	result->len = length;
	ft_memcpy((char *)result->str, str, length);
	return (result);
}

t_string	*ft_string_duplicate(const t_string *str)
{
	return ((t_string *)ft_memdup(str, sizeof(t_string) + str->len));
}
