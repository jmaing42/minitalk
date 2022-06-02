/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:18:45 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/06/02 20:11:51 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdlib.h>

#include "ft_io.h"
#include "ft_exit.h"

static bool	print_formatted_conversion(char type, pid_t sender, size_t length)
{
	if (!type)
		return (false);
	if (
		(type == '%' && ft_write(STDOUT_FILENO, "%", 1))
		|| (type == '_' && ft_write(STDOUT_FILENO, " ", 1))
		|| (type == 'T' && ft_write(STDOUT_FILENO, "\t", 1))
		|| (type == 'N' && ft_write(STDOUT_FILENO, "\n", 1))
		|| (type == 'P' && ft_put_number(STDOUT_FILENO, sender))
		|| (type == 'L' && ft_put_number(STDOUT_FILENO, length))
	)
		ft_exit(EXIT_FAILURE);
	return (true);
}

static void	print_formatted(const char *format, pid_t sender, size_t length)
{
	size_t		skipped;

	skipped = 0;
	while (*format || skipped)
	{
		if (*format && *format != '%')
		{
			skipped++;
			format++;
			continue ;
		}
		if (skipped && ft_write(STDOUT_FILENO, &format[-skipped], skipped))
			ft_exit(EXIT_FAILURE);
		skipped = 0;
		if (!*format)
			continue ;
		format++;
		if (print_formatted_conversion(*format, sender, length))
			format++;
	}
}

void	print_message(
	pid_t sender,
	size_t length,
	char *message
)
{
	print_formatted(c()->options.message_format_header, sender, length);
	if (
		ft_write(
			STDOUT_FILENO,
			c()->options.message_format_line,
			c()->options.message_format_line_length
		)
		|| ft_put_multiline(
			STDOUT_FILENO,
			message,
			c()->options.message_format_line,
			c()->options.message_format_line_length
		)
	)
		ft_exit(EXIT_FAILURE);
	print_formatted(c()->options.message_format_footer, sender, length);
}

void	print_timeout_message(
	pid_t sender
)
{
	print_formatted(c()->options.message_format_timeout, sender, 0);
}
