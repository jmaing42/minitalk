/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:23:37 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/02 02:05:51 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdlib.h>
#include <limits.h>

#include "ft_io.h"
#include "ft_memory.h"
#include "ft_malloc.h"
#include "ft_exit.h"
#include "ft_simple_map.h"
#include "ft_stringbuilder.h"

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
		session->message = new_stringbuilder(c()->options.buffer_size);
		if (!session->message)
			ft_exit(EXIT_FAILURE);
	}
	if (kill(sender, SIGUSR1) || ((!session->length || !session->message)
			&& session->length_length == sizeof(size_t) * CHAR_BIT))
	{
		if (!session->length
			&& session->length_length == sizeof(size_t) * CHAR_BIT)
			show_session(sender, session->message);
		free_session(sender, session);
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
		if (stringbuilder_append_char(session->message, session->curr))
			ft_exit(EXIT_FAILURE);
		session->curr_length = 0;
		session->curr = 0;
		if (session->message->length == session->length)
		{
			show_session(sender, session->message);
			free_session(sender, session);
			(void)kill(sender, SIGUSR1);
			*mut_done = true;
			return (true);
		}
	}
	if (kill(sender, SIGUSR1))
	{
		free_session(sender, session);
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
	session = get_session(sender);
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

static void	handle_timeout(void)
{
	t_session_timeout_node	*node;
	t_session_timeout_node	*next;

	c()->busy = true;
	while (c()->head)
	{
		node = c()->head;
		next = node->next;
		c()->head = next;
		(void)kill(node->pid, SIGUSR2);
		if (ft_put_string(STDOUT_FILENO, "Timeout: ")
			|| ft_put_number(STDOUT_FILENO, node->pid)
			|| ft_put_string(STDOUT_FILENO, " (disconnecting...)\n\n"))
			ft_exit(EXIT_FAILURE);
		(void)ft_simple_map_static_pop(c()->sessions, (void *)&node->pid, NULL);
		free(node->self->message);
		free(node->self);
	}
	c()->tail = NULL;
	c()->busy = false;
}

void	main_loop(void)
{
	while (true)
	{
		c()->woke_up = false;
		if (c()->head)
		{
			usleep(c()->options.timeout);
			if (!c()->woke_up)
				handle_timeout();
		}
		else
			pause();
	}
}
