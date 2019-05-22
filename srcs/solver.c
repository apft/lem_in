/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/05/22 10:13:04 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "customlibft.h"
#include "error.h"
#include "output.h"
#include "ft_printf.h"

static int	is_closed_path(t_room *room)
{
	return (room->flag & FL_CLOSE_PATH);
}

static void	clear_queue(t_queue *queue)
{
	while (dequeue(queue) || queue->head)
		;
}

static int save_path_and_clear_queue(t_room *end, t_queue *queue, t_env *env)
{
	t_room	*current;

	ft_printf("]} ");
	current = end;
	while (current->parent)
	{
		if (current != env->end)
			current->flag |= FL_CLOSE_PATH;
		current->parent->next = current;
		current = current->parent;
	}
	clear_queue(queue);
	return (SUCCESS);
}

static t_room	*open_path_to_start(t_room *current, t_env *env)
{
	while (current->parent != env->start)
	{
		current = current->parent;
		current->next = 0;
		if (is_closed_path(current))
			current->flag ^= FL_CLOSE_PATH;
	}
	return (current);
}

static t_room	*close_path_to_start(t_room *current, t_env *env)
{
	while (current->parent != env->start)
	{
		current->parent->next = current;
		current = current->parent;
		current->flag |= FL_CLOSE_PATH;
	}
	return (current);
}

static int	has_oriented_tube_between_rooms(int id_room_a, int id_room_b, t_env *env)
{
	return (env->matrix[id_room_a][id_room_b]);
}

static int	is_room_already_visited(t_room *room)
{
	return (room->visited);
}

static int	bfs_max_flow(t_env *env, t_room *start)
{
	t_queue	queue;
	t_room	*current;
	t_room	*neighbour;
	int		i;

	queue = (t_queue){0, 0};
	enqueue(&queue, (void *)start);
	start->visited = 1;
	while (queue.head)
	{
		current = (t_room *)dequeue(&queue);
		ft_printf("%s->{", current->name);
		i = 0;
		while (i < env->nb_room)
		{
			if (has_oriented_tube_between_rooms(current->id, i, env)
					&& !is_room_already_visited(env->rooms_array[i]))
			{
				neighbour = env->rooms_array[i];
				if (!is_closed_path(neighbour) || (neighbour->parent != start))
				{
					ft_printf("%s", neighbour->name);
					neighbour->visited = 1;
					if (is_closed_path(neighbour))
					{
						ft_printf("* [");
						if (bfs_max_flow(env, open_path_to_start(neighbour, env)) == SUCCESS)
						{
							neighbour->parent = current;
							current->next = neighbour;
							return (save_path_and_clear_queue(current, &queue, env));
						}
						else
						{
							close_path_to_start(neighbour, env);
							ft_printf("].");
						}
					}
					else
					{
						neighbour->parent = current;
						if (neighbour == env->end)
							return (save_path_and_clear_queue(neighbour, &queue, env));
						enqueue(&queue, (void *)neighbour);
						ft_printf(" ");
					}
				}
			}
			++i;
		}
		ft_printf("} > ");
	}
	return (ERROR);
}

static int	has_augmenting_path(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_room)
		env->rooms_array[i++]->visited = 0;
	return (bfs_max_flow(env, env->start));
}

int		solver(t_env *env)
{
	int	i;

	i = 0;
	while (has_augmenting_path(env) == SUCCESS)
	{
		ft_printf("\n");
		ft_printf("Loop %d:\n", i++);
		print_paths(env);
	}
	ft_printf("\n");
	return (SUCCESS);
}
