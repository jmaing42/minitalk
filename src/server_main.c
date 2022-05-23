/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:24:27 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/24 03:19:31 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "ft_io.h"
#include "ft_memory.h"

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
	init_context(c());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (true)
		pause();
	return (EXIT_FAILURE);
}
