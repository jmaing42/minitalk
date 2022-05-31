/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:22:31 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 03:56:41 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

#include <stdlib.h>
#include <signal.h>

#include "ft_lib.h"
#include "ft_memory.h"
#include "ft_cstring.h"

#define ENVP_TIMEOUT_START "TIMEOUT="
#define DEFAULT_TIMEOUT 42042

static sig_atomic_t	g_ack_received;

static void	init_context(t_context *context, const char *pid, const char *str)
{
	context->server = ft_atoi(pid);
	if (ft_atoi(pid) != context->server)
		exit(EXIT_FAILURE);
	context->length = ft_strlen(str);
	context->length_length = 0;
	context->sent = 0;
	context->curr_length = 0;
	context->message = str;
}

static void	set_ack_true(int signal)
{
	(void)signal;
	g_ack_received = 1;
}

static void	timeout_exit(int signal)
{
	(void)signal;
	exit(EXIT_FAILURE);
}

static useconds_t	parse_timeout(char **environ)
{
	environ--;
	while (*++environ)
		if (ft_cstring_starts_with(*environ, ENVP_TIMEOUT_START))
			return (ft_atoi(*environ + sizeof(ENVP_TIMEOUT_START) - 1));
	return (DEFAULT_TIMEOUT);
}

int	main(int argc, char **argv, char **envp)
{
	const useconds_t	timeout = parse_timeout(envp);
	t_context			context;
	int					signal_to_send;

	if (argc != 3)
		return (EXIT_FAILURE);
	init_context(&context, argv[1], argv[2]);
	signal(SIGUSR1, set_ack_true);
	signal(SIGUSR2, timeout_exit);
	g_ack_received = 0;
	while (true)
	{
		signal_to_send = SIGUSR1;
		if (handler(&context, !!g_ack_received))
			signal_to_send = SIGUSR2;
		g_ack_received = 0;
		if (kill(context.server, signal_to_send))
			exit(EXIT_FAILURE);
		usleep(timeout);
	}
	return (EXIT_FAILURE);
}
