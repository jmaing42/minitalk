/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_byte_map.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:52:10 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/23 08:28:40 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BYTE_MAP_H
# define FT_BYTE_MAP_H

# include <stdarg.h>

# include "ft_types.h"

/**
 * @brief bake map for single set
 *
 * @param map out parameter to get result
 * @param include_null indicate whether include NULL
 * @param set input
 */
void	ft_byte_map(t_byte *map, bool include_null, const t_byte *set);

#endif
