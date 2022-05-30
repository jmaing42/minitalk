/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:58:21 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/30 17:34:19 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

#include <stdlib.h>
#include <limits.h>
#include <signal.h>

static bool	process_message(t_context *context, bool *out_result, bool *mut_ack)
{
	if (*mut_ack)
	{
		if (++(context->curr_length) == CHAR_BIT)
		{
			context->curr_length = 0;
			if (++(context->sent) == context->length)
				exit(EXIT_SUCCESS);
		}
	}
	*out_result = !!(context->message[context->sent]
			& (1 << (CHAR_BIT - 1 - context->curr_length)));
	return (true);
}

static bool	process_length(t_context *context, bool *out_result, bool *mut_ack)
{
	if (context->length_length != sizeof(size_t) * CHAR_BIT)
	{
		if (*mut_ack && ++(context->length_length) == sizeof(size_t) * CHAR_BIT)
		{
			*mut_ack = false;
			return (false);
		}
		*out_result = !!(context->length & (
					((size_t) 1) << (
						sizeof(size_t) * CHAR_BIT - 1 - context->length_length
						)
					)
				);
		return (true);
	}
	else if (!context->length)
		exit(EXIT_SUCCESS);
	else
		return (false);
}

bool	handler(t_context *context, bool ack)
{
	bool	result;

	if (
		process_length(context, &result, &ack)
		|| process_message(context, &result, &ack)
	)
		return (result);
	exit(EXIT_FAILURE);
}
