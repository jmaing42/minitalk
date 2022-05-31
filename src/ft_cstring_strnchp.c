/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cstring_strnchp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:25:46 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/31 20:42:12 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cstring.h"

#ifdef DEVELOPMENT

# include <stdlib.h>
# include <unistd.h>

# include "ft_io.h"
# include "ft_exit.h"

size_t	ft_strnchp(const char *str, size_t max_len, char ch)
{
	size_t	result;

	if (!str)
	{
		ft_put_string(
			STDERR_FILENO,
			"ft_strnchp(): wrong parameter given\n");
		ft_exit(EXIT_FAILURE);
		return (0);
	}
	result = -1;
	while (++result < max_len && str[result])
		if (str[result] == ch)
			break ;
	return (result);
}

size_t	ft_strnrchp(const char *str, size_t max_len, char ch)
{
	size_t	result;
	size_t	i;

	if (!str)
	{
		ft_put_string(
			STDERR_FILENO,
			"ft_strnrchp(): wrong parameter given\n");
		ft_exit(EXIT_FAILURE);
		return (0);
	}
	i = -1;
	result = -1;
	while (++i < max_len && str[i])
		if (str[i] == ch)
			result = i;
	return (result);
}

#else

size_t	ft_strnchp(const char *str, size_t max_len, char ch)
{
	size_t	result;

	result = -1;
	while (++result < max_len && str[result])
		if (str[result] == ch)
			break ;
	return (result);
}

size_t	ft_strnrchp(const char *str, size_t max_len, char ch)
{
	size_t	result;
	size_t	i;

	i = -1;
	result = -1;
	while (++i < max_len && str[i])
		if (str[i] == ch)
			result = i;
	return (result);
}

#endif
