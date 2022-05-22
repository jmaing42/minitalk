/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:22:31 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/23 02:47:25 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

#include <stdlib.h>
#include <unistd.h>

#include "ft_io.h"
#include "ft_lib.h"

void	on_success(void)
{
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		return (EXIT_FAILURE);
	}
	return (send_message(ft_atoi(argv[1]), argv[2]));
}
