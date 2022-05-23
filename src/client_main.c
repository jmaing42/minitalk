/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:22:31 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/24 03:10:10 by Juyeong Maing    ###   ########.fr       */
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
		if (!ack)
		{
			tmp = SIGUSR1;
			if (c()->length & (((size_t) 1) << (
						sizeof(size_t) * CHAR_BIT - 1 - c()->length_length)))
				tmp = SIGUSR2;
			if (kill(c()->server, tmp))
				exit(EXIT_FAILURE);
			return ;
		}
		if (++(c()->length_length) != sizeof(size_t) * CHAR_BIT)
			return (handle(false));
		return (handle_message(false));
	}
	return (handle_message(ack));
}

void	handler(int signal, siginfo_t *info, void *context)
{
	const pid_t	sender = info->si_pid;

	(void)context;
	if (sender == c()->server && signal == SIGUSR1)
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
	while (true)
	{
		handle(false);
		usleep(10000);
	}
	return (EXIT_FAILURE);
}
