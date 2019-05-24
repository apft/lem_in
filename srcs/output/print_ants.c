/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 07:53:30 by apion             #+#    #+#             */
/*   Updated: 2019/05/24 10:37:03 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "ft_printf.h"

static int	is_closed_path(t_room *room)
{
	return (room->flag & FL_CLOSE_PATH);
}

static int	has_oriented_tube_between_rooms(int id_room_a, int id_room_b, t_env *env)
{
	return (env->matrix[id_room_a][id_room_b]);
}

static int	has_ant_in_room(t_room *room)
{
	return (room->ant > 0);
}

static int	move_ant_to_room(t_room *from, t_room *room, t_env *env)
{
	int		ant_nb;

	if (from == env->start)
	{
		ant_nb = env->nb_ants - env->start->ant + 1;
		from->ant -= 1;
	}
	else
	{
		ant_nb = from->ant;
		from->ant = 0;
	}
	if (room == env->end)
		room->ant -= 1;
	else
		room->ant = ant_nb;
	ft_printf("L%d-%s ", ant_nb, room->name);
	return (SUCCESS);
}

static int	search_first_empty_room_on_path(t_room *from, t_room *current, t_env *env)
{
	while (current != env->end)
	{
		if (!has_ant_in_room(current))
		{
			if (!from->ant)
			{
				from = current;
				current = current->next;
			}
			else
				break ;
		}
		else
		{
			from = current;
			current = current->next;
		}
	}
	if (from->ant && (!has_ant_in_room(current) || current == env->end))
		return (move_ant_to_room(from, current, env));
	return (ERROR);
}

static int	apply_foreach_path_from_start(t_env *env, int (*fct)())
{
	t_room *current;
	int		has_moved;
	int		i;

	has_moved = 0;
	i = 0;
	while (i < env->nb_room)
	{
		current = env->rooms_array[i];
		if (has_oriented_tube_between_rooms(env->start->id, current->id, env))
		{
			if (is_closed_path(current))
				has_moved = fct(env->start, current, env) == SUCCESS;
		}
		++i;
	}
	return (has_moved);
}

void	print_ants(t_env *env)
{
	int		i;
	
	env->start->ant = env->nb_ants;
	env->end->ant = env->nb_ants;
	i = 0;
	while (env->end->ant)
	{
		while(apply_foreach_path_from_start(env, &search_first_empty_room_on_path))
			;
		++i;
		ft_printf("\n");
	}
	ft_printf("\nNombre de lignes: %d\n", i);
}
