/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_context.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:36:29 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/24 03:19:49 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdlib.h>
#include <signal.h>

#include "ft_exit.h"

t_context	*c(void)
{
	static t_context	context;

	return (&context);
}

void	init_context(t_context *context)
{
	context->sessions = new_ft_simple_map_static(sizeof(pid_t));
	if (!context->sessions)
		ft_exit(EXIT_FAILURE);
}
