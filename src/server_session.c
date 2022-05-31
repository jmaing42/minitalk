/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_session.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 03:43:05 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/01 03:50:29 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdlib.h>

#include "ft_io.h"
#include "ft_malloc.h"
#include "ft_exit.h"

void	show_session(pid_t sender, const char *message, size_t length)
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

void	free_session(pid_t pid, t_session *session)
{
	(void)ft_simple_map_static_pop(c()->sessions, (void *)&pid, NULL);
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
}

t_session	*get_session(pid_t key)
{
	t_session	*session;

	if (!ft_simple_map_static_get(c()->sessions, &key, (void **)&session))
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
	if (ft_simple_map_static_set(c()->sessions, &key, session))
		ft_exit(EXIT_FAILURE);
	return (session);
}
