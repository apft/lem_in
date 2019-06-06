/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <pion@student.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:31:17 by apion             #+#    #+#             */
/*   Updated: 2019/06/06 10:56:05 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "libft.h"
#include "error.h"

static void	free_room(void *room, size_t size)
{
	(void)size;
	free((void *)((t_room *)room)->name);
	free((void *)((t_room *)room));
}

static void	free_matrix(int ***matrix, size_t size)
{
	while (size--)
		free((*matrix)[size]);
	free(*matrix);
	*matrix = 0;
}

static void	free_array_path(t_path ***array_path, size_t size)
{
	while (size--)
		free((*array_path)[size]);
	free(*array_path);
	*array_path = 0;
}

int			free_mem(t_env *env)
{
	if (env->lines)
		list_line_del_all(&env->lines);
	if (env->map)
		ft_lstdel(&env->map, &free_room);
	if (env->rooms_array)
		ft_memdel((void **)&env->rooms_array);
	if (env->matrix)
		free_matrix(&env->matrix, env->nb_rooms);
	if (env->paths_array)
		free_array_path(&env->paths_array, env->nb_paths);
	return (SUCCESS);
}
