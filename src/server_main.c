/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:24:27 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/23 02:44:16 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

#include "ft_io.h"

int	main(void)
{
	const intmax_t	pid = getpid();

	ft_put_string(1, "Server pid is ");
	ft_put_number(1, pid);
	ft_put_string(1, ". enjoy!\n");
}
