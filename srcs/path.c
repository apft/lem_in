/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:19:48 by apion             #+#    #+#             */
/*   Updated: 2019/06/06 15:03:47 by pion             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "path.h"
#include "generic_merge_sort.h"
#include "error.h"
#include "ft_printf.h"

int		free_unfully_malloced_path_matrix_and_return(t_path ***matrix, int index)
{
	while (index--)
		free((*matrix)[index]);
	free(*matrix);
	*matrix = 0;
	return (errno);
}

static int	compute_path_length(t_room *current)
{
	int		length;

	length = 0;
	while (current)
	{
		current = current->next;
		++length;
	}
	return (length);
}

static void	compute_streams(t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (i < env->nb_path)
	{
		j = i;
		while (j--)
			env->paths_array[i]->nb_ants_stream += env->paths_array[i]->length
				- env->paths_array[j]->length + 1;
		++i;
	}
}

static int	cmp_array_length(t_path **elm1, t_path **elm2)
{
	return ((*elm1)->length - (*elm2)->length);
}

static int	sort_array_path(t_env *env)
{
	t_array_args	args;
	int				status;

	args = (t_array_args){env->paths_array, sizeof(t_path *), env->nb_path,
				&cmp_array_length};
	status = array_merge_sort(&args);
	if (status != SUCCESS)
		return (status);
	return (SUCCESS);
}

static void	update_paths_links(t_env *env)
{
	int		i;
	t_room	*current;
	t_room	*from;

	i = 0;
	while (i < env->nb_path)
	{
		from = env->start;
		current = env->paths_array[i]->front;
		while (current != env->end)
		{
			current->from = from;
			from = current;
			current = current->next;
		}
		++i;
	}
}

static int	add_path_to_array(t_room *start, t_room *current, t_env *env, int *index)
{
	int		length;

	(void)start;
	if (!is_closed_path(current))
		return (SUCCESS);
	env->paths_array[*index] = (t_path *)malloc(sizeof(t_path));
	if (!env->paths_array[*index])
		return (free_unfully_malloced_path_matrix_and_return(&env->paths_array, *index));
	length = compute_path_length(current);
	*env->paths_array[*index] = (t_path){current, current, current, length, 0, 0};
	++(*index);
	return (SUCCESS);
}

static int	create_path_array(t_env *env, int nb_path)
{
	int		status;
	int		i;

	env->paths_array = (t_path **)malloc(sizeof(t_path *) * nb_path);
	if (!env->paths_array)
		return (errno);
	i = 0;
	status = apply_foreach_room_linked_to_ref(env->start, env, &i, &add_path_to_array);
	if (status != SUCCESS)
		return (status);
	return (SUCCESS);
}

void		print_array_path(t_env *env)
{
	int		i;

	i = 0;
	ft_printf("\nPaths ordered:\n");
	while (i < env->nb_path)
	{
		ft_printf("%d: (%d, %s, %d)", i, env->paths_array[i]->length,
				env->paths_array[i]->back->name,
				env->paths_array[i]->nb_ants_stream);
		if (i < env->nb_path - 1)
			ft_printf(" | ");
		i++;
	}
	ft_printf("\n");
}

void		print_ants_line(t_env *env, int *last_ant)
{
	int		i;
	int		paths_covered;
	t_path	*path;

	paths_covered = 0;
	i = 0;
	while (paths_covered < env->nb_path)
	{
		i = 0;
		while (i < env->nb_path)
		{
			path = env->paths_array[i];
			if (!path->path_printed)
			{
				if (path->current->ant)
				{
					ft_printf("L%d-%s ", path->current->ant, path->current->next->name);
					if (path->current->next == env->end)
						++(env->end->ant);
					else
					{
						path->current->next->ant = path->current->ant;
						if (path->current == path->front)
							path->front = path->current->next;
					}
					path->current->ant = 0;
					if (path->current->from != env->start)
						path->current = path->current->from;
				}
				else
				{
					path->path_printed = 1;
					++paths_covered;
				}
			}
			++i;
		}
	}
	i = 0;
	while (i < env->nb_path)
	{
		path = env->paths_array[i];
		if (path->back->from == env->start)
		{
			if (*last_ant <= env->nb_ants)
			{
				if (i && (env->nb_ants - *last_ant + 1) < path->nb_ants_stream)
					break ;
				ft_printf("L%d-%s ", *last_ant, path->current->name);
				path->current->ant = *last_ant;
				++(*last_ant);
			}
			else
			{
				if (path->back->next != env->end)
					path->back = path->back->next;
			}
		}
		else
		{
			if (path->back->next != env->end)
				path->back = path->back->next;
		}
		++i;
	}
	ft_printf("\n");
	i = 0;
	while (i < env->nb_path)
	{
		env->paths_array[i]->path_printed = 0;
		env->paths_array[i]->current = env->paths_array[i]->front;
		++i;
	}
}

void		print_ants_lines(t_env *env)
{
	int		last_ant;
	int		j;

	last_ant = 1;
	j = 0;
	ft_printf("\n");
	while (env->end->ant < env->nb_ants)
	{
		print_ants_line(env, &last_ant);
		++j;
	}
	ft_printf("\nNb of lines: %d\n", j);
}

int			fill_path_array(t_env *env)
{
	int		status;

	status = create_path_array(env, env->nb_path);
	if (status != SUCCESS)
		return (status);
	status = sort_array_path(env);
	if (status != SUCCESS)
		return (status);
	compute_streams(env);
	update_paths_links(env);
	print_array_path(env);
	ft_printf("\nNb of ants: %d\n", env->nb_ants);
//	print_ants_lines(env);
	return (SUCCESS);
}
