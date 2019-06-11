/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_is.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:29:50 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 18:08:11 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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

int		is_closed_room_as_junction(t_room *current)
{
	if (!is_closed_path(current))
		return (0);
	return (is_junction(current) && internal_cost(current) == COST_INF);
}

int		is_room_name_equal(t_room *room1, t_room *room2)
{
	return (ft_strcmp(room1->name, room2->name));
}
