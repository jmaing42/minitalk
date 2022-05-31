/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:24:27 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 03:35:01 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdint.h>
#include <stdlib.h>

#include "ft_exit.h"
#include "ft_io.h"
#include "ft_memory.h"

t_context	*c(void)
{
	static t_context	context;

	return (&context);
}

static void	init_context(void)
{
	c()->sessions = new_ft_simple_map_static(sizeof(pid_t));
	if (!c()->sessions)
		ft_exit(EXIT_FAILURE);
	c()->timeout = 60000;
	c()->head = NULL;
	c()->tail = NULL;
	c()->busy = false;
}

static void	set_signal_handler(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	if (
		sigemptyset(&sa.sa_mask)
		|| sigaction(SIGUSR1, &sa, NULL)
		|| sigaction(SIGUSR2, &sa, NULL)
	)
		exit(EXIT_FAILURE);
}

static void	main_loop(void)
{
	while (true)
	{
		c()->woke_up = false;
		if (c()->head)
		{
			usleep(c()->timeout);
			if (!c()->woke_up)
				handle_timeout();
		}
		else
			pause();
	}
}

int	main(void)
{
	ft_put_string(STDOUT_FILENO, "Server pid is ");
	ft_put_number(STDOUT_FILENO, getpid());
	ft_put_string(STDOUT_FILENO, ". enjoy!\n");
	init_context();
	set_signal_handler();
	main_loop();
	return (EXIT_FAILURE);
}
