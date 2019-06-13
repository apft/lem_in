/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <pion@student.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:31:17 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 17:47:23 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "error.h"
#include <stdlib.h>

static void	free_room(void *room)
{
	free((void *)((t_room *)room)->name);
	free((void *)((t_room *)room));
}

int			free_room_and_return(void *room, int status)
{
	free_room(room);
	return (status);
}

static void	free_tree_node(t_rb_node *node)
{
	free_room(node->data);
	free((void *)node);
}

void		free_ptr_array_to_index(void ***array, int last_index)
{
	while (last_index--)
		free(*(*array + last_index));
	free(*array);
	*array = 0;
}

int			free_mem(t_env *env)
{
	if (env->lines)
		list_line_del_all(&env->lines);
	if (env->rooms_tree)
		btree_apply_suffix(env->rooms_tree, (void *)0, &free_tree_node);
	if (env->rooms_array)
		ft_memdel((void **)&env->rooms_array);
	if (env->matrix)
		free_ptr_array_to_index((void ***)&env->matrix, env->nb_rooms);
	if (env->paths_array)
		free_ptr_array_to_index((void ***)&env->paths_array, env->nb_paths);
	return (SUCCESS);
}
