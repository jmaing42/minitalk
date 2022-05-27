/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:17:20 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/27 19:53:15 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <signal.h>

# include "ft_stringbuilder.h"
# include "ft_simple_map.h"

typedef struct s_session
{
	t_stringbuilder	*message;
	size_t			length;
	size_t			length_length;
	char			curr;
	int				curr_length;
}	t_session;

typedef struct s_context
{
	t_ft_simple_map_static	*sessions;
	pid_t					next_client;
	int						next_signal;
}	t_context;

t_context	*c(void);
void		init_context(t_context *context);
void		handler(int signal, siginfo_t *info, void *context);

#endif
