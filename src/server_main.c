/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:24:27 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 04:00:15 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdint.h>
#include <stdlib.h>

#include "ft_io.h"
#include "ft_lib.h"
#include "ft_memory.h"
#include "ft_cstring.h"
#include "ft_exit.h"

#define ENVP_TIMEOUT_START "TIMEOUT="
#define DEFAULT_TIMEOUT 420420

t_context	*c(void)
{
	static t_context	context;

	return (&context);
}

static void	init_context(char **environ)
{
	c()->sessions = new_ft_simple_map_static(sizeof(pid_t));
	if (!c()->sessions)
		ft_exit(EXIT_FAILURE);
	c()->timeout = DEFAULT_TIMEOUT;
	c()->head = NULL;
	c()->tail = NULL;
	c()->busy = false;
	environ--;
	while (*++environ)
	{
		if (ft_cstring_starts_with(*environ, ENVP_TIMEOUT_START))
		{
			c()->timeout = ft_atoi(*environ + sizeof(ENVP_TIMEOUT_START) - 1);
			break ;
		}
	}
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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_put_string(STDOUT_FILENO, "Server pid is ");
	ft_put_number(STDOUT_FILENO, getpid());
	ft_put_string(STDOUT_FILENO, ". enjoy!\n");
	init_context(envp);
	set_signal_handler();
	main_loop();
	return (EXIT_FAILURE);
}
