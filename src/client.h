/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:36:19 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 18:28:59 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>

typedef struct s_context
{
	pid_t			server;
	const char		*message;
	size_t			length;
	size_t			length_length;
	size_t			sent;
	uint_fast8_t	curr_length;
	useconds_t		timeout;
}	t_context;

bool	handler(t_context *context, bool ack);
void	timeout_exit(int signal);

#endif
