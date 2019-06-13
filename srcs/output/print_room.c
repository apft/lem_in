/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:48:31 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 17:49:09 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"
#include "libft.h"
#include "ft_printf.h"

void	print_room(t_room *room, char *after)
{
	ft_printf("%c%c%s(%s:%s:%s:%d:%s-%s:%d)%s",
		is_junction(room) ? '*' : ' ',
		is_closed_path(room) ? '~' : ' ',
		room->name,
		room->from ? room->from->name : ".",
		room->from_junction ? room->from_junction->name : ".",
		room->next ? room->next->name : ".",
		room->visited,
		external_cost(room) == COST_INF ? "inf" : ft_itoa(external_cost(room)),
		internal_cost(room) == COST_INF ? "inf" : ft_itoa(internal_cost(room)),
		room->dst,
		after);
}
