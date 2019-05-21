/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:43:55 by apion             #+#    #+#             */
/*   Updated: 2019/05/21 19:44:47 by apion            ###   ########.fr       */
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

static int has_path_and_not_visited_or_is_closed(t_env *env, t_room *current, int i)
{
	return (env->matrix[current->id][i]
			&& !env->rooms_array[i]->visited
			&& !(env->rooms_array[i]->parent == env->start
				&& is_closed_path(env->rooms_array[i])));
}

static int	bfs_max_flow(t_env *env, t_room *start)
{
	t_queue	queue;
	t_room	*current;
	t_room	*child;
	int		i;

	queue = (t_queue){0, 0};
	enqueue(&queue, (void *)start);
	start->visited = 1;
	while (queue.head)
	{
		current = (t_room *)dequeue(&queue);
		if (current == env->end)
			return (save_path_and_clear_queue(current, &queue, env));
		i = 0;
		while (i < env->nb_room)
		{
			if (has_path_and_not_visited_or_is_closed(env, current, i))
			{
				child = env->rooms_array[i];
				//ft_printf("%s > ", child->name);
				child->visited = 1;
				if (is_closed_path(child))
				{
					if (bfs_max_flow(env, open_path_to_start(child, env)) == SUCCESS)
					{
						child->parent = current;
						current->next = child;
						return (save_path_and_clear_queue(current, &queue, env));
					}
					else
						close_path_to_start(child, env);
				}
				else
				{
					child->parent = current;
					enqueue(&queue, (void *)child);
				}
			}
			++i;
		}
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
	//	ft_printf("\n");
	//	ft_printf("Loop %d:\n", i++);
	//	print_paths(env);
	}
	ft_printf("\n");
	return (SUCCESS);
}
