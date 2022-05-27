/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:23:37 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/27 21:47:35 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdlib.h>
#include <limits.h>
#include <signal.h>

#include "ft_memory.h"
#include "ft_malloc.h"
#include "ft_exit.h"
#include "ft_simple_map.h"
#include "ft_stringbuilder.h"
#include "ft_io.h"

static t_session	*get_or_new(t_ft_simple_map_static *map, pid_t key)
{
	t_session	*session;

	if (!ft_simple_map_static_get(map, &key, (void **)&session))
		return (session);
	session = (t_session *)ft_malloc(sizeof(t_session));
	session->message = new_stringbuilder(1024);
	if (!session->message)
		ft_exit(EXIT_FAILURE);
	session->length = 0;
	session->length_length = 0;
	session->curr = 0;
	session->curr_length = 0;
	if (ft_simple_map_static_set(map, &key, session))
		ft_exit(EXIT_FAILURE);
	return (session);
}

static void	print_message(pid_t sender, t_stringbuilder *message)
{
	char *const	str = stringbuilder_to_cstring(message, 0);

	if (
		!str
		|| ft_put_string(1, "Message from ")
		|| ft_put_number(1, sender)
		|| ft_put_string(1, ":\n|\t")
		|| ft_put_multiline(1, str, "|\t", 2)
		|| ft_put_string(1, "\n")
	)
		ft_exit(EXIT_FAILURE);
	free(str);
}

void	handle_message(int signal, pid_t sender, t_session *session)
{
	session->curr = (session->curr << 1) | (signal == SIGUSR2);
	if (++(session->curr_length) == CHAR_BIT)
	{
		if (stringbuilder_append_char(session->message, session->curr))
			ft_exit(EXIT_FAILURE);
		session->curr_length = 0;
		session->curr = 0;
		if (session->message->length == session->length)
		{
			print_message(sender, session->message);
			ft_simple_map_static_pop(c()->sessions, (void *)&sender, NULL);
			stringbuilder_free(session->message);
			free(session);
			(void)kill(sender, SIGUSR1);
			c()->next_client = 0;
			return ;
		}
	}
	c()->next_signal = SIGUSR1;
}

void	handler(int signal, siginfo_t *info, void *context)
{
	t_session	*session;

	(void) context;
	c()->next_client = info->si_pid;
	if (!c()->next_client)
		return ;
	session = get_or_new(c()->sessions, c()->next_client);
	if (session->length_length != sizeof(size_t) * CHAR_BIT)
	{
		session->length_length++;
		session->length = (session->length << 1) | (signal == SIGUSR2);
		c()->next_client = c()->next_client;
		c()->next_signal = SIGUSR1;
		if (session->length_length == sizeof(size_t) * CHAR_BIT
			&& !session->length)
		{
			ft_simple_map_static_pop(
				c()->sessions, (void *)&c()->next_client, NULL);
			stringbuilder_free(session->message);
			free(session);
		}
		return ;
	}
	return (handle_message(signal, c()->next_client, session));
}
