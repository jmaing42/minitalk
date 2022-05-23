/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringbuilder.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:33:58 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/23 08:36:28 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGBUILDER_H
# define FT_STRINGBUILDER_H

# include "ft_types.h"
# include "ft_string.h"

typedef struct s_stringbuilder_node
{
	struct s_stringbuilder_node	*next;
	size_t						capacity;
	size_t						length;
	char						str[];
}	t_stringbuilder_node;

typedef struct s_stringbuilder
{
	size_t					length;
	t_stringbuilder_node	*head;
	t_stringbuilder_node	*tail;
	size_t					buffer_size;
}	t_stringbuilder;

t_stringbuilder	*new_stringbuilder(
					size_t buffer_size);
void			stringbuilder_free(
					t_stringbuilder *self);
t_err			stringbuilder_append(
					t_stringbuilder *self,
					t_string *str);
t_err			stringbuilder_append_c(
					t_stringbuilder *self,
					const char *str);
t_err			stringbuilder_append_buffer(
					t_stringbuilder *self,
					size_t length,
					const char *buf);
t_err			stringbuilder_append_char(
					t_stringbuilder *self,
					char c);
t_string		*stringbuilder_to_string(
					t_stringbuilder *self,
					size_t offset);
char			*stringbuilder_to_cstring(
					t_stringbuilder *self,
					size_t offset);

#endif
