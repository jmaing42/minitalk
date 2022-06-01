/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:24:27 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/02 02:26:48 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdint.h>
#include <stdlib.h>

#include "ft_io.h"
#include "ft_memory.h"
#include "ft_exit.h"

t_context	*c(void)
{
	static t_context	context;

	return (&context);
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

static void	init(char **environ)
{
	ft_put_string(STDOUT_FILENO, "Server pid is ");
	ft_put_number(STDOUT_FILENO, getpid());
	ft_put_string(STDOUT_FILENO, ". enjoy!\n");
	c()->sessions = new_ft_simple_map_static(sizeof(pid_t));
	if (!c()->sessions)
		ft_exit(EXIT_FAILURE);
	c()->head = NULL;
	c()->tail = NULL;
	c()->busy = false;
	parse_options(environ);
	set_signal_handler();
}

#ifndef NO_MOULINETTE

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init(envp);
	main_loop();
	return (EXIT_FAILURE);
}

#else

extern char	**environ;

int	main(void)
{
	init(environ);
	main_loop();
	return (EXIT_FAILURE);
}

#endif
