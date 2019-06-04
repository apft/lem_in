/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:19:48 by apion             #+#    #+#             */
/*   Updated: 2019/06/04 17:31:59 by jkettani         ###   ########.fr       */
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

static int	cmp_array_length(t_path **elm1, t_path **elm2)
{
	return ((*elm1)->length - (*elm2)->length);
}

static void	sort_array_path(t_env *env)
{
	t_array_args	args;

	args = (t_array_args){env->paths_array, sizeof(t_path *), env->nb_path,
				&cmp_array_length};
	array_merge_sort(&args);
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
	*env->paths_array[*index] = (t_path){current, current, current, length};
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
	while (i < env->nb_path)
	{
		ft_printf("Path %d:\n", i);
		ft_printf("  > length = %d\n", env->paths_array[i]->length);
		i++;
	}
}

int			fill_path_array(t_env *env)
{
	int		status;

	status = create_path_array(env, env->nb_path);
	if (status != SUCCESS)
		return (status);
	sort_array_path(env);
	update_paths_links(env);
	print_array_path(env);
	return (SUCCESS);
}
