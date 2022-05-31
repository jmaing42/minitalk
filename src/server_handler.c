/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:23:37 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 01:22:41 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <signal.h>

#include "ft_memory.h"
#include "ft_malloc.h"
#include "ft_exit.h"
#include "ft_simple_map.h"
#include "ft_io.h"

static t_session	*get_or_new(t_ft_simple_map_static *map, pid_t key)
{
	t_session	*session;

	if (!ft_simple_map_static_get(map, &key, (void **)&session))
		return (session);
	session = (t_session *)ft_malloc(sizeof(t_session));
	session->message = NULL;
	session->received = 0;
	session->length = 0;
	session->length_length = 0;
	session->curr = 0;
	session->curr_length = 0;
	if (ft_simple_map_static_set(map, &key, session))
		ft_exit(EXIT_FAILURE);
	return (session);
}

static void	print_message(pid_t sender, const char *message, size_t length)
{
	if (
		ft_put_string(STDOUT_FILENO, "Message from ")
		|| ft_put_number(STDOUT_FILENO, sender)
		|| ft_put_string(STDOUT_FILENO, " (")
		|| ft_put_number(STDOUT_FILENO, length)
		|| ft_put_string(STDOUT_FILENO, " bytes)\n|\t")
		|| ft_put_multiline(STDOUT_FILENO, message, "|\t", 2)
		|| ft_put_string(STDOUT_FILENO, "\n\n")
	)
		ft_exit(EXIT_FAILURE);
}

static bool	handle_length(t_session *session, pid_t sender, bool data)
{
	if (session->length_length == sizeof(size_t) * CHAR_BIT)
		return (false);
	session->length_length++;
	session->length = (session->length << 1) | data;
	if (session->length_length == sizeof(size_t) * CHAR_BIT)
	{
		session->message = (char *)ft_malloc(session->length + 1);
		session->message[session->length] = '\0';
	}
	if (kill(sender, SIGUSR1) || ((!session->length || !session->message)
			&& session->length_length == sizeof(size_t) * CHAR_BIT))
	{
		if (!session->length
			&& session->length_length == sizeof(size_t) * CHAR_BIT)
			print_message(sender, session->message, session->length);
		(void)ft_simple_map_static_pop(c()->sessions, (void *)&sender, NULL);
		free(session->message);
		free(session);
	}
	return (true);
}

static bool	handle_message(t_session *session, pid_t sender, bool data)
{
	session->curr = (session->curr << 1) | data;
	if (++(session->curr_length) == CHAR_BIT)
	{
		session->message[session->received++] = session->curr;
		session->curr_length = 0;
		session->curr = 0;
		if (session->received == session->length)
		{
			print_message(sender, session->message, session->length);
			(void)ft_simple_map_static_pop(
				c()->sessions, (void *)&sender, NULL);
			free(session->message);
			free(session);
			(void)kill(sender, SIGUSR1);
			return (true);
		}
	}
	if (kill(sender, SIGUSR1))
	{
		(void)ft_simple_map_static_pop(
			c()->sessions, &sender, (void **)&session);
		free(session->message);
		free(session);
	}
	return (true);
}

void	handler(int signal, siginfo_t *info, void *context)
{
	const pid_t			sender = info->si_pid;
	t_session *const	session = get_or_new(c()->sessions, sender);

	(void) context;
	if (!sender)
		return ;
	if (
		!(
			handle_length(session, sender, signal == SIGUSR2)
			|| handle_message(session, sender, signal == SIGUSR2)
		)
	)
	{
		(void)kill(sender, SIGUSR2);
		(void)ft_simple_map_static_pop(c()->sessions, (void *)&sender, NULL);
		free(session->message);
		free(session);
	}
}
