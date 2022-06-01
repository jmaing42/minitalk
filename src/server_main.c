/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:24:27 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 18:40:48 by Juyeong Maing    ###   ########.fr       */
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

#define ENVP_BUFFER_SIZE "BUFFER_SIZE="
#define ENVP_TIMEOUT "TIMEOUT="
#define DEFAULT_BUFFER_SIZE 1024
#define DEFAULT_TIMEOUT 420420

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
	c()->buffer_size = DEFAULT_BUFFER_SIZE;
	c()->timeout = DEFAULT_TIMEOUT;
	c()->head = NULL;
	c()->tail = NULL;
	c()->busy = false;
	environ--;
	while (*++environ)
	{
		if (ft_cstring_starts_with(*environ, ENVP_BUFFER_SIZE))
			c()->buffer_size = ft_atoi(*environ + sizeof(ENVP_BUFFER_SIZE) - 1);
		if (ft_cstring_starts_with(*environ, ENVP_TIMEOUT))
			c()->timeout = ft_atoi(*environ + sizeof(ENVP_TIMEOUT) - 1);
	}
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
