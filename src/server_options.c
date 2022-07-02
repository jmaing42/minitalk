/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 01:50:00 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/07/02 12:57:48 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include "ft_lib.h"
#include "ft_cstring.h"
#include "ft_malloc.h"

#define ENVP_MESSAGE_FORMAT_HEADER "MESSAGE_FORMAT_HEADER="
#define ENVP_MESSAGE_FORMAT_LINE "MESSAGE_FORMAT_LINE="
#define ENVP_MESSAGE_FORMAT_FOOTER "MESSAGE_FORMAT_FOOTER="
#define ENVP_MESSAGE_FORMAT_TIMEOUT "MESSAGE_FORMAT_TIMEOUT="
#define ENVP_BUFFER_SIZE "BUFFER_SIZE="
#define ENVP_TIMEOUT "TIMEOUT="

#define DEFAULT_MESSAGE_FORMAT_HEADER "Message from %P (%L bytes)%N"
#define DEFAULT_MESSAGE_FORMAT_LINE "|%T"
#define DEFAULT_MESSAGE_FORMAT_FOOTER "%N%N"
#define DEFAULT_MESSAGE_FORMAT_TIMEOUT "Timeout: %P (disconnecting...)%N%N"
#define DEFAULT_BUFFER_SIZE 1024
#define DEFAULT_TIMEOUT 420420

#define BUFFER_SIZE_MIN 16
#define BUFFER_SIZE_MAX 16384
#define TIMEOUT_MIN 100
#define TIMEOUT_MAX 1000000

static char	*line(const char *str)
{
	size_t		len;
	const char	*tmp;
	char		*result;

	len = 0;
	tmp = str - 1;
	while (*++tmp)
	{
		if (tmp[0] == '%' && tmp[1] == 'T')
			tmp++;
		len++;
	}
	result = (char *)ft_malloc(len + 1);
	result[len] = '\0';
	len = 0;
	tmp = str - 1;
	while (*++tmp)
	{
		if (tmp[0] == '%' && tmp[1] == 'T')
			result[len++] = *++tmp - 'T' + '\t';
		else
			result[len++] = *tmp;
	}
	return (result);
}

static uintmax_t	normalize(uintmax_t min, uintmax_t value, uintmax_t max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static bool	match(const char *str, const char *starts_with, const char **out)
{
	while (*str && *starts_with && *str == *starts_with)
	{
		str++;
		starts_with++;
	}
	if (*starts_with)
		return (false);
	*out = str;
	return (true);
}

static void	options_default(void)
{
	c()->options.message_format_header = DEFAULT_MESSAGE_FORMAT_HEADER;
	c()->options.message_format_line = DEFAULT_MESSAGE_FORMAT_LINE;
	c()->options.message_format_footer = DEFAULT_MESSAGE_FORMAT_FOOTER;
	c()->options.message_format_timeout = DEFAULT_MESSAGE_FORMAT_TIMEOUT;
	c()->options.buffer_size = DEFAULT_BUFFER_SIZE;
	c()->options.timeout = DEFAULT_TIMEOUT;
}

void	parse_options(char **environ)
{
	const char	*tmp;

	options_default();
	environ--;
	while (*++environ)
	{
		if (match(*environ, ENVP_MESSAGE_FORMAT_HEADER, &tmp))
			c()->options.message_format_header = tmp;
		if (match(*environ, ENVP_MESSAGE_FORMAT_LINE, &tmp))
			c()->options.message_format_line = tmp;
		if (match(*environ, ENVP_MESSAGE_FORMAT_FOOTER, &tmp))
			c()->options.message_format_footer = tmp;
		if (match(*environ, ENVP_MESSAGE_FORMAT_TIMEOUT, &tmp))
			c()->options.message_format_timeout = tmp;
		if (match(*environ, ENVP_BUFFER_SIZE, &tmp))
			(c()->options.buffer_size)
				= normalize(BUFFER_SIZE_MIN, ft_atoi(tmp), BUFFER_SIZE_MAX);
		if (match(*environ, ENVP_TIMEOUT, &tmp))
			(c()->options.timeout)
				= normalize(TIMEOUT_MIN, ft_atoi(tmp), TIMEOUT_MAX);
	}
	c()->options.message_format_line = line(c()->options.message_format_line);
	c()->options.message_format_line_length = ft_strlen(
		c()->options.message_format_line);
}
