/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:24:27 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/27 21:36:47 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "ft_exit.h"
#include "ft_io.h"
#include "ft_memory.h"

t_context	*c(void)
{
	static t_context	context;

	return (&context);
}

void	server_loop(void)
{
	pid_t		client;
	t_session	*session;

	pause();
	if (c()->next_client && kill(c()->next_client, c()->next_signal))
	{
		if (ft_simple_map_static_pop(c()->sessions, &client, (void **)&session))
		{
			stringbuilder_free(session->message);
			free(session);
		}
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_put_string(1, "Server pid is ");
	ft_put_number(1, getpid());
	ft_put_string(1, ". enjoy!\n");
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	c()->sessions = new_ft_simple_map_static(sizeof(pid_t));
	if (!c()->sessions)
		ft_exit(EXIT_FAILURE);
	c()->next_client = 0;
	while (true)
		server_loop();
	return (EXIT_FAILURE);
}
