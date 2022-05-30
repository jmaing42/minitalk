/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:36:19 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/30 17:25:27 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <stdbool.h>

typedef struct s_context
{
	pid_t		server;
	const char	*message;
	size_t		length;
	size_t		length_length;
	size_t		sent;
	int			curr_length;
}	t_context;

bool	handler(t_context *context, bool ack);

#endif
