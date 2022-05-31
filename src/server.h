/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:17:20 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 02:57:10 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdint.h>
# include <unistd.h>
# include <signal.h>

# include "ft_simple_map.h"

typedef struct s_session_timeout_node
{
	struct s_session_timeout_node	*prev;
	struct s_session_timeout_node	*next;
	struct s_session				*self;
	pid_t							pid;
}	t_session_timeout_node;

typedef struct s_session
{
	size_t					length;
	size_t					length_length;
	size_t					received;
	char					*message;
	char					curr;
	uint_least8_t			curr_length;
	t_session_timeout_node	timeout_node;
}	t_session;

typedef struct s_context
{
	t_ft_simple_map_static	*sessions;
	t_session_timeout_node	*head;
	t_session_timeout_node	*tail;
	useconds_t				timeout;
	volatile bool			woke_up;
	volatile bool			busy;
}	t_context;

t_context	*c(void);
void		handler(int signal, siginfo_t *info, void *context);
void		handle_timeout(void);

#endif
