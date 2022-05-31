/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_timeout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 02:48:04 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 03:40:53 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdlib.h>

#include "ft_io.h"
#include "ft_exit.h"

#include <stdio.h>
#include <limits.h>

void	handle_timeout(void)
{
	t_session_timeout_node	*node;
	t_session_timeout_node	*next;

	c()->busy = true;
	while (c()->head)
	{
		node = c()->head;
		next = node->next;
		c()->head = next;
		if (next)
			next->prev = NULL;
		else
			c()->tail = NULL;
		(void)kill(node->pid, SIGUSR2);
		if (ft_put_string(STDOUT_FILENO, "Timeout: ")
			|| ft_put_number(STDOUT_FILENO, node->pid)
			|| ft_put_string(STDOUT_FILENO, " (disconnecting...)\n"))
			ft_exit(EXIT_FAILURE);
		(void)ft_simple_map_static_pop(c()->sessions, (void *)&node->pid, NULL);
		free(node->self->message);
		free(node->self);
	}
	c()->busy = false;
}
