/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:10:15 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/31 16:39:50 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exit.h"

#include <stdbool.h>
#include <stdlib.h>

static void	x(bool execute, void (*cleanup)())
{
	static void	(*cleanup_func)() = NULL;

	if (!execute)
		cleanup_func = cleanup;
	else if (cleanup_func)
		cleanup_func();
}

int	ft_exit(signed char status)
{
	x(true, NULL);
	exit((int) status);
}

void	ft_set_exit_handler(void (*cleanup)())
{
	x(false, cleanup);
}
