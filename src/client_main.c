/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:22:31 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 18:33:43 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

#include <stdlib.h>
#include <signal.h>

#include "ft_lib.h"
#include "ft_memory.h"
#include "ft_cstring.h"

#define ENVP_TIMEOUT "TIMEOUT="
#define DEFAULT_TIMEOUT 42042

static sig_atomic_t	g_ack_received;

static void	set_ack_true(int signal)
{
	(void)signal;
	g_ack_received = 1;
}

static void	init(
	t_context *context,
	const char *pid,
	const char *str,
	char **environ
)
{
	context->server = ft_atoi(pid);
	if (ft_atoi(pid) != context->server)
		exit(EXIT_FAILURE);
	context->length = ft_strlen(str);
	context->length_length = 0;
	context->sent = 0;
	context->curr_length = 0;
	context->message = str;
	context->timeout = DEFAULT_TIMEOUT;
	environ--;
	while (*++environ)
		if (ft_cstring_starts_with(*environ, ENVP_TIMEOUT))
			context->timeout = (ft_atoi(*environ + sizeof(ENVP_TIMEOUT) - 1));
	signal(SIGUSR1, set_ack_true);
	signal(SIGUSR2, timeout_exit);
}

static void	main_loop(t_context *context)
{
	int	signal_to_send;

	g_ack_received = 0;
	while (true)
	{
		signal_to_send = SIGUSR1;
		if (handler(context, !!g_ack_received))
			signal_to_send = SIGUSR2;
		g_ack_received = 0;
		if (kill(context->server, signal_to_send))
			exit(EXIT_FAILURE);
		usleep(context->timeout);
	}
}

#ifndef NO_MOULINETTE

int	main(int argc, char **argv, char **envp)
{
	t_context	context;

	if (argc != 3)
		return (EXIT_FAILURE);
	init(&context, argv[1], argv[2], envp);
	main_loop(&context);
	return (EXIT_FAILURE);
}

#else

extern char			**environ;

int	main(int argc, char **argv)
{
	t_context	context;

	if (argc != 3)
		return (EXIT_FAILURE);
	init(&context, argv[1], argv[2], environ);
	main_loop(&context);
	return (EXIT_FAILURE);
}

#endif
