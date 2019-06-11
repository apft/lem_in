/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <pion@student.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:31:17 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 14:33:40 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "error.h"
#include <stdlib.h>
#include "ft_printf.h"

static void	free_room(void *room, size_t size)
{
	(void)size;
	free((void *)((t_room *)room)->name);
	free((void *)((t_room *)room));
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
	if (env->map)
		ft_lstdel(&env->map, &free_room);
	if (env->rooms_array)
		ft_memdel((void **)&env->rooms_array);
	if (env->matrix)
		free_ptr_array_to_index((void ***)&env->matrix, env->nb_rooms);
	if (env->paths_array)
		free_ptr_array_to_index((void ***)&env->paths_array, env->nb_paths);
	return (SUCCESS);
}
