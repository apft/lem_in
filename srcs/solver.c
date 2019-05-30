/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/05/30 15:55:43 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "env.h"
#include "customlibft.h"
#include "error.h"
#include "output.h"
#include "ft_printf.h"

static int	is_closed_path(t_room *room)
{
	return (room->flag & FL_CLOSE_PATH);
}

static int	is_junction(t_room *room)
{
	return ((long)room->from_junction);
}

static int	is_linked_on_same_path(t_room *room_a, t_room *room_b)
{
	if (!room_a || !room_b)
		return (0);
	if (!is_closed_path(room_a) || !is_closed_path(room_b))
		return (0);
	return (room_a->next == room_b || room_b->next == room_a);
}

static int	external_cost(t_room *room)
{
	return (room->cost[0]);
}

static int	internal_cost(t_room *room)
{
	return (room->cost[1]);
}

/**
 * Je suis finalement plus tres convaincu par cette fonction de cout...
 * si current et current_from sur le meme chemin solution alors retourner internal_cost(current)
 * sinon retourner external_cost(current)
 * 
 * cela implique que 'from' n'a pas ete modifie entre temps (sauf dans le cas
 * ou current est revisite et neighbour ajoute en tete de file)
 * 
 * de plus 'from' est utilise pour s'assurer que le current->from est sur le
 * meme chemin que current. Donc m'est avis que l'on doit tout faire pour
 * conserver 'from' le plus coherent possible
*/
static int	cost(t_room *room)
{
	if (is_linked_on_same_path(room, room->from))
		return (internal_cost(room));
	return (external_cost(room));
	//return (ft_min(external_cost(room), internal_cost(room)));
}

static int	has_oriented_tube_between_rooms(int id_room_a, int id_room_b, t_env *env)
{
	return (env->matrix[id_room_a][id_room_b]);
}

static void	apply_foreach_room_linked_to_ref(t_room *ref, t_env *env, void *data, void (*fct)())
{
	t_room	*neighbour;
	int		i;

	i = 0;
	while (i < env->nb_room)
	{
		if (has_oriented_tube_between_rooms(ref->id, i, env))
		{
			neighbour = env->rooms_array[i];
			fct(ref, neighbour, env, data);
		}
		++i;
	}
}

static void	open_path(t_room **room_from, t_room *first_next)
{
	t_room	*current;
	t_room	*next;

	current = (*room_from)->next;
	(*room_from)->next = first_next;
	while (!is_junction(current))
	{
		current->flag ^= FL_CLOSE_PATH;
		next = current->next;
		current->next = 0;
		current = next;
	}
	*room_from = current->from_junction;
	if (is_closed_path(*room_from))
		open_path(room_from, current);
	(*room_from)->next = current;
	(*room_from)->flag |= FL_CLOSE_PATH;
}

static int	save_path(t_env *env)
{
	t_room	*current;
	t_room	*next;

	current = env->end;
	next = 0;
	while (current->from)
	{
		if (current != env->end)
		{
			if (!is_closed_path(current))
			{
				current->flag |= FL_CLOSE_PATH;
				current->next = next;
			}
			else
				open_path(&current, next);
		}
		else
			current->next = next;
		next = current;
		current = current->from;
	}
	return (SUCCESS);
}

static void	search_for_valid_neighbour(t_room *current, t_room *neighbour, t_env *env, t_queue *queue)
{
	if (neighbour == current->from)
		return ;
	if (current == env->start && is_closed_path(neighbour))
		return ;
	if (is_closed_path(current))
	{
		if (neighbour == current->next)
			return ;
		else if (!is_linked_on_same_path(current, current->from)
				&& !is_linked_on_same_path(current, neighbour))
			return ;
	}
	else
	{
		if (is_closed_path(neighbour) && neighbour->from == env->start)
			return ;
	}
	if (is_closed_path(neighbour))
	{
		if (is_linked_on_same_path(current, neighbour))
		{
			if (internal_cost(neighbour) <= (cost(current) - 1))
				return ;
			neighbour->cost[1] = cost(current) - 1;
		}
		else
		{
			if (external_cost(neighbour) <= (cost(current) + 1))
				return ;
			if (internal_cost(neighbour) <= (cost(current) + 1))
				return ;
			neighbour->cost[0] = cost(current) + 1;
			neighbour->from_junction = current;
		}
	}
	else
	{
		if (is_closed_path(current))
		{
			if (is_linked_on_same_path(current, current->from))
			{
				if (external_cost(neighbour) <= (internal_cost(current) + 1))
					return ;
				neighbour->cost[0] = internal_cost(current) + 1;
			}
			else
			{
				// impossible: current est une jonction
			}
		}
		else
		{
			if (external_cost(neighbour) <= (external_cost(current) + 1))
				return ;
			neighbour->cost[0] = external_cost(current) + 1;
		}
	}
	ft_printf("%s%s(%s:%d) ", is_closed_path(neighbour) ? "^" : "", neighbour->name, neighbour->from ? neighbour->from->name : ".", neighbour->visited);
	neighbour->from = current;
	if (neighbour->visited == VISITED_EMPTY)
	{
		neighbour->visited = VISITED_AS_NEIGHBOUR;
		enqueue(queue, (void *)neighbour);
	}
	else if (neighbour->visited == VISITED_AS_CURRENT)
	{
		neighbour->visited = VISITED_AS_NEIGHBOUR;
		prequeue(queue, (void *)neighbour);
	}
}

static void	bfs_max_flow(t_env *env, t_queue *queue)
{
	t_room	*current;

	while (queue->head)
	{
		current = (t_room *)dequeue(queue);
		current->visited = VISITED_AS_CURRENT;
		ft_printf("%s(%s:%s-%s)%s->{", current->name, current->from ? current->from->name : ".", external_cost(current) == INT_MAX - 1 ? "inf" : ft_itoa(external_cost(current)), internal_cost(current) == INT_MAX - 1 ? "inf" : ft_itoa(internal_cost(current)), is_junction(current) ? "*" : (is_closed_path(current) ? "~" : ""));
		apply_foreach_room_linked_to_ref(current, env, queue, &search_for_valid_neighbour);
		ft_printf("} > ");
	}
}

static void	initialize(t_env *env, t_queue *queue)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
	{
		env->rooms_array[i]->visited = VISITED_EMPTY;
		env->rooms_array[i]->from_junction = (void *)0;
		env->rooms_array[i]->from = (void *)0;
		env->rooms_array[i]->cost[0] = INT_MAX - 1;
		env->rooms_array[i]->cost[1] = INT_MAX - 1;
		++i;
	}
	env->start->cost[0] = 0;
	*queue = (t_queue){0, 0};
	enqueue(queue, (void *)env->start);
}

static int	has_augmenting_path(t_env *env)
{
	t_queue	queue;

	initialize(env, &queue);
	bfs_max_flow(env, &queue);
	if (env->end->cost[0] == INT_MAX - 1)
		return (ERROR);
	save_path(env);
	return (SUCCESS);
}

int		solver(t_env *env)
{
	int		flow;
	int		i;

	flow = 0;
	i = 0;
	while (has_augmenting_path(env) == SUCCESS)
	{
		flow += env->end->cost[0] - 1;
		ft_printf("\n");
		ft_printf("Loop %d:\n", i++);
		print_paths(env);
	}
	ft_printf("\n\nflow= %d", flow);
	return (SUCCESS);
}
