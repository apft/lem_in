/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:29:50 by apion             #+#    #+#             */
/*   Updated: 2019/06/06 13:36:18 by pion             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_printf.h"

int		external_cost(t_room *room)
{
	return (room->cost[0]);
}

int		internal_cost(t_room *room)
{
	return (room->cost[1]);
}

int		is_junction(t_room *room)
{
	return (room->from_junction != (void *)0);
}

int		is_closed_path(t_room *room)
{
	return (room->flag & FL_CLOSE_PATH);
}

int		is_linked_on_same_path(t_room *room_a, t_room *room_b)
{
	if (!room_a || !room_b)
		return (0);
	if (!is_closed_path(room_a) || !is_closed_path(room_b))
		return (0);
	return (room_a->next == room_b || room_b->next == room_a);
}

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
