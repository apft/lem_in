/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bakery.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:47:01 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 11:35:59 by pion             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parser.h"
#include "cleaner.h"
#include "error.h"
#include "libft.h"
#include <stdlib.h>

static void	add_to_array(t_rb_node *node, t_env *env)
{
	t_room		*room;
	static int	index;

	room = (t_room *)node->data;
	room->id = index;
	env->rooms_array[index] = room;
	++index;
}

static int	tree_to_array(t_env *env)
{
	env->rooms_array = (t_room **)malloc(sizeof(t_room *) * env->nb_rooms);
	if (!env->rooms_array)
		return (errno);
	btree_apply_infix(env->rooms_tree, (void *)env, &add_to_array);
	return (SUCCESS);
}

static int	create_adjacency_matrix(t_env *env)
{
	int		i;

	env->matrix = (int **)ft_memalloc(sizeof(int *) * env->nb_rooms);
	if (!env->matrix)
		return (errno);
	i = 0;
	while (i < env->nb_rooms)
	{
		(env->matrix)[i] = (int *)ft_memalloc(sizeof(int) * env->nb_rooms);
		if (!(env->matrix)[i])
		{
			free_ptr_array_to_index((void ***)&(env->matrix), i);
			return (errno);
		}
		++i;
	}
	return (SUCCESS);
}

int			check_environment(t_env *env, int status)
{
	if ((status > err_ants_begin && status < err_ants_end)
		|| (status > err_room_begin && status < err_room_end)
		|| (status > err_env_begin && status < err_env_end)
		|| !env->rooms_array || !env->matrix)
		return (status);
	return (SUCCESS);
}

int			bake_environment(t_env *env, unsigned int *cmd_flag)
{
	*cmd_flag ^= BLK_ROOM | BLK_TUBE;
	if (!env->rooms_tree)
		return (err_env_empty);
	if (!env->start)
		return (err_env_empty_start);
	if (!env->end)
		return (err_env_empty_end);
	if (tree_to_array(env) != SUCCESS)
		return (err_env_lst_to_array);
	if (create_adjacency_matrix(env) != SUCCESS)
		return (err_env_adjacency_matrix);
	return (SUCCESS);
}
