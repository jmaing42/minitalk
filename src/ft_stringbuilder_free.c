/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringbuilder_free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:33:58 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/22 20:55:18 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stringbuilder.h"

#include <stdlib.h>

void	stringbuilder_free(t_stringbuilder *self)
{
	t_stringbuilder_node	*current;
	t_stringbuilder_node	*next;

	current = self->head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(self);
}
