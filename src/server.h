/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:17:20 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/31 16:28:37 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <signal.h>

# include "ft_simple_map.h"

typedef struct s_session
{
	size_t	length;
	size_t	length_length;
	size_t	received;
	char	*message;
	char	curr;
	int		curr_length;
}	t_session;

typedef struct s_context
{
	t_ft_simple_map_static	*sessions;
}	t_context;

t_context	*c(void);
void		handler(int signal, siginfo_t *info, void *context);

#endif
