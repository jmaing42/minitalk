/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:22:31 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/30 15:23:28 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "ft_io.h"
#include "ft_lib.h"
#include "ft_cstring.h"

t_context	*c(void)
{
	static t_context	context;

	return (&context);
}

void	set_next_signal_part2(bool ack)
{
	if (ack)
	{
		if (++(c()->curr_length) == CHAR_BIT)
		{
			c()->curr_length = 0;
			if (++(c()->sent) == c()->length)
				exit(EXIT_SUCCESS);
		}
	}
	c()->next_signal = SIGUSR1;
	if (c()->message[c()->sent] & (1 << (CHAR_BIT - 1 - c()->curr_length)))
		c()->next_signal = SIGUSR2;
}

void	set_next_signal(bool ack)
{
	if (c()->length_length != sizeof(size_t) * CHAR_BIT)
	{
		if (ack && ++(c()->length_length) == sizeof(size_t) * CHAR_BIT)
			return (set_next_signal_part2(false));
		c()->next_signal = SIGUSR1;
		if (c()->length & (((size_t) 1) << (
					sizeof(size_t) * CHAR_BIT - 1 - c()->length_length)))
			c()->next_signal = SIGUSR2;
	}
	else if (!c()->length)
		exit(EXIT_SUCCESS);
	else
		return (set_next_signal_part2(ack));
}

void	set_ack_true(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGUSR1)
		c()->ack = true;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
		return (EXIT_FAILURE);
	sa.sa_sigaction = set_ack_true;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaction(SIGUSR1, &sa, NULL);
	c()->length = ft_strlen(argv[2]);
	c()->length_length = 0;
	c()->sent = 0;
	c()->curr_length = 0;
	c()->server = ft_atoi(argv[1]);
	c()->message = argv[2];
	c()->ack = false;
	while (true)
	{
		if (!c()->ack)
			ft_put_string(STDERR_FILENO, "No ACK;\n");
		set_next_signal(c()->ack);
		if (kill(c()->server, c()->next_signal))
			exit(EXIT_FAILURE);
		c()->ack = false;
		usleep(42042);
	}
	return (EXIT_FAILURE);
}
