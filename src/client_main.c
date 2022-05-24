/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:22:31 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/24 22:30:42 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "ft_io.h"
#include "ft_lib.h"
#include "ft_memory.h"
#include "ft_cstring.h"

t_context	*c(void)
{
	static t_context	context;

	return (&context);
}

void	handle_message(bool ack)
{
	int	tmp;

	if (ack)
	{
		write(2, &"01"[!!(c()->message[c()->sent] & (1 << (CHAR_BIT - 1 - c()->curr_length)))], 1);
		if (++(c()->curr_length) == CHAR_BIT)
		{
			c()->curr_length = 0;
			if (++(c()->sent) == c()->length)
				exit(EXIT_SUCCESS);
		}
	}
	tmp = SIGUSR1;
	if (c()->message[c()->sent] & (1 << (CHAR_BIT - 1 - c()->curr_length)))
		tmp = SIGUSR2;
	if (kill(c()->server, tmp))
		exit(EXIT_FAILURE);
}

void	handle(bool ack)
{
	int	tmp;

	if (c()->length_length != sizeof(size_t) * CHAR_BIT)
	{
		if (ack)
			write(2, &"01"[!!(c()->length & (((size_t) 1) << (sizeof(size_t) * CHAR_BIT - 1 - c()->length_length)))], 1);
		if (ack && ++(c()->length_length) == sizeof(size_t) * CHAR_BIT)
			return (handle_message(false));
		tmp = SIGUSR1;
		if (c()->length & (((size_t) 1) << (
					sizeof(size_t) * CHAR_BIT - 1 - c()->length_length)))
			tmp = SIGUSR2;
		if (kill(c()->server, tmp))
			exit(EXIT_FAILURE);
	}
	else
		return (handle_message(ack));
}

void	handler(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGUSR1)
		handle(true);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
		return (EXIT_FAILURE);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	c()->length = ft_strlen(argv[2]);
	c()->length_length = 0;
	c()->sent = 0;
	c()->curr_length = 0;
	c()->server = ft_atoi(argv[1]);
	c()->message = argv[2];
	handle(false);
	while (true)
	{
		pause();
	}
	return (EXIT_FAILURE);
}
