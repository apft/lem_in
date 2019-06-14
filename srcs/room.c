/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:59:01 by apion             #+#    #+#             */
/*   Updated: 2019/06/14 11:19:12 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "customlibft.h"
#include <stdlib.h>

#define ROOM_UNDEF_VALUE	-1
#define ROOM_EMPTY_VALUE	0

t_room	*create_empty_room(void)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(*room));
	if (!room)
		return (0);
	*room = (t_room){
		(void *)0,
		ROOM_UNDEF_VALUE,
		ROOM_UNDEF_VALUE,
		ROOM_UNDEF_VALUE,
		(void *)0,
		(void *)0,
		(void *)0,
		VISITED_EMPTY,
		{COST_INF, COST_INF},
		ROOM_EMPTY_VALUE,
		ROOM_EMPTY_VALUE,
		ROOM_EMPTY_VALUE};
	return (room);
}

int		external_cost(t_room *room)
{
	return (room->cost[0]);
}

int		internal_cost(t_room *room)
{
	return (room->cost[1]);
}

int		get_room_id_by_name(char *str, t_env *env, int (*cmp)())
{
	t_array_args	array_args;

	array_args = (t_array_args){env->rooms_array, sizeof(t_room *),
		env->nb_rooms};
	return (ft_bsearch_id(str, &array_args, cmp));
}

int		cmp_room_name(void *room1, void *room2)
{
	return (ft_strcmp(((t_room *)room1)->name, ((t_room *)room2)->name));
}
