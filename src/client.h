/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 02:36:19 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/27 19:41:45 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>

typedef struct s_context
{
	pid_t		server;
	const char	*message;
	size_t		length;
	size_t		length_length;
	size_t		sent;
	int			curr_length;
	int			next_signal;
}	t_context;

#endif
