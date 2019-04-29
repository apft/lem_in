/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <pion@student.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:31:17 by apion             #+#    #+#             */
/*   Updated: 2019/04/29 12:36:28 by apion            ###   ########.fr       */
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

int			free_mem(t_env *env)
{
	if (env->lines)
		list_line_del_all(&env->lines);
	if (env->map)
		ft_lstdel(&env->map, &free_room);
	if (env->rooms_array)
		ft_memdel((void **)&env->rooms_array);
	if (env->matrix)
		free_matrix(&env->matrix, env->nb_room);
	return (SUCCESS);
}
