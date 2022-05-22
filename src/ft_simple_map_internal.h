/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_map_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 01:42:14 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/16 12:03:50 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIMPLE_MAP_INTERNAL_H
# define FT_SIMPLE_MAP_INTERNAL_H

# include <stddef.h>
# include <stdbool.h>
# include <limits.h>

# define S_FT_SIMPLE_MAP_STATIC_DEFINED

typedef union u_ft_simple_map_static_value
{
	void								*value[1 << CHAR_BIT];
	union u_ft_simple_map_static_value	*array[1 << CHAR_BIT];
}	t_ft_simple_map_static_value;

typedef struct s_ft_simple_map_static
{
	size_t							key_length;
	t_ft_simple_map_static_value	*values;
}	t_ft_simple_map_static;

typedef struct s_ft_simple_map_static_context_set
{
	t_ft_simple_map_static	*self;
	void					*key;
	void					*value;
}	t_ft_simple_map_static_context_set;

typedef struct s_ft_simple_map_static_context_get
{
	t_ft_simple_map_static	*self;
	void					*key;
	void					**out;
}	t_ft_simple_map_static_context_get;

#endif
