/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:23:37 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 03:32:14 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdlib.h>
#include <limits.h>

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
	session->timeout_node.pid = key;
	session->timeout_node.self = session;
	session->timeout_node.next = NULL;
	session->timeout_node.prev = c()->tail;
	if (c()->tail)
		c()->tail->next = &session->timeout_node;
	else
		c()->head = &session->timeout_node;
	c()->tail = &session->timeout_node;
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

static bool	handle_length(
	t_session *session,
	pid_t sender,
	bool data,
	bool *mut_done
)
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
		if (session->timeout_node.prev)
			session->timeout_node.prev->next = session->timeout_node.next;
		else
			c()->head = session->timeout_node.next;
		if (session->timeout_node.next)
			session->timeout_node.next->prev = session->timeout_node.prev;
		else
			c()->tail = session->timeout_node.prev;
		free(session->message);
		free(session);
		*mut_done = true;
	}
	return (true);
}

static bool	handle_message(
	t_session *session,
	pid_t sender,
	bool data,
	bool *mut_done
)
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
			if (session->timeout_node.prev)
				session->timeout_node.prev->next = session->timeout_node.next;
			else
				c()->head = session->timeout_node.next;
			if (session->timeout_node.next)
				session->timeout_node.next->prev = session->timeout_node.prev;
			else
				c()->tail = session->timeout_node.prev;
			free(session->message);
			free(session);
			(void)kill(sender, SIGUSR1);
			*mut_done = true;
			return (true);
		}
	}
	if (kill(sender, SIGUSR1))
	{
		(void)ft_simple_map_static_pop(
			c()->sessions, &sender, (void **)&session);
		if (session->timeout_node.prev)
			session->timeout_node.prev->next = session->timeout_node.next;
		else
			c()->head = session->timeout_node.next;
		if (session->timeout_node.next)
			session->timeout_node.next->prev = session->timeout_node.prev;
		else
			c()->tail = session->timeout_node.prev;
		free(session->message);
		free(session);
		*mut_done = true;
	}
	return (true);
}

void	handler(int signal, siginfo_t *info, void *context)
{
	const pid_t	sender = info->si_pid;
	const bool	data = (signal == SIGUSR2);
	bool		done;
	t_session	*session;

	(void) context;
	c()->woke_up = true;
	if (!sender || c()->busy)
		return ;
	session = get_or_new(c()->sessions, sender);
	done = false;
	if ((handle_length(session, sender, data, &done)
			|| handle_message(session, sender, data, &done))
		&& !done && c()->tail != &session->timeout_node)
	{
		if (!session->timeout_node.prev)
			c()->head = session->timeout_node.next;
		else
			session->timeout_node.prev->next = session->timeout_node.next;
		session->timeout_node.next->prev = session->timeout_node.prev;
		c()->tail->next = &session->timeout_node;
		session->timeout_node.prev = c()->tail;
		session->timeout_node.next = NULL;
		c()->tail = &session->timeout_node;
	}
}
