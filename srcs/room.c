/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:59:01 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 17:01:51 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "customlibft.h"

static int	cmp_room_name(char *str, t_room **room)
{
	return (ft_strcmp(str, (*room)->name));
}

static int	cmp_first_room_name_in_tube(char *str, t_room **room)
{
	int		id_dash;
	int		res;

	id_dash = 0;
	while (str[id_dash] != '-')
		++id_dash;
	res = ft_strncmp(str, (*room)->name, id_dash);
	if (res == 0)
		return (res - (*room)->name[id_dash]);
	else
		return (res);
}

int			get_room_id_by_name(char *str, t_env *env, int context)
{
	t_array_args	array_args;
	int				(*cmp)();

	array_args = (t_array_args)
			{env->rooms_array, sizeof(t_room *), env->nb_rooms};
	if (context == ROOM_NAME_IN_TUBE)
		cmp = &cmp_first_room_name_in_tube;
	else
		cmp = &cmp_room_name;
	return (ft_bsearch_id(str, &array_args, *cmp));
}

int			closed_room_as_junction(t_room *current)
{
	if (!is_closed_path(current))
		return (0);
	return (is_junction(current) && internal_cost(current) == COST_INF);
}

int			has_oriented_tube_between_rooms_by_id(int id_room_a, int id_room_b,
					t_env *env)
{
	return (env->matrix[id_room_a][id_room_b]);
}

int			has_oriented_tube_between_rooms(t_room *room_a, t_room *room_b,
					t_env *env)
{
	return (has_oriented_tube_between_rooms_by_id(room_a->id, room_b->id, env));
}
