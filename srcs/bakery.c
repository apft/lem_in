/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bakery.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:47:01 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 10:59:38 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "parser.h"
#include "cleaner.h"
#include "error.h"
#include "libft.h"
#include "generic_merge_sort.h"

static int	lst_to_array(t_env *env)
{
	t_list		*map;
	int			i;

	env->rooms_array = (t_room **)ft_memalloc(sizeof(t_room *) * env->nb_rooms);
	if (!env->rooms_array)
		return (errno);
	map = env->map;
	i = 0;
	while (map)
	{
		env->rooms_array[i] = (t_room *)(map->content);
		++i;
		map = map->next;
	}
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
	if ((status > ERR_ANTS_BEGIN && status < ERR_ANTS_END)
		|| (status > ERR_ROOM_BEGIN && status < ERR_ROOM_END)
		|| (status > ERR_ENV_BEGIN && status < ERR_ENV_END)
		|| !env->rooms_array || !env->matrix)
		return (status);
	return (SUCCESS);
}

int			cmp_rooms_name(t_room **room1, t_room **room2)
{
	return (ft_strcmp((*room1)->name, (*room2)->name));
}

int			create_ordered_rooms_array(t_env *env)
{
	t_array_args	args;
	int				i;

	if (lst_to_array(env) != SUCCESS)
		return (ERR_ENV_LST_TO_ARRAY);
	args = (t_array_args){env->rooms_array, sizeof(t_room *), env->nb_rooms,
				&cmp_rooms_name};
	if (array_merge_sort(&args) != SUCCESS)
		return (ERR_ENV_ARRAY_SORT);
	i = 0;
	while (i < env->nb_rooms)
	{
		env->rooms_array[i]->id = i;
		++i;
	}
	return (SUCCESS);
}

int			bake_environment(t_env *env, unsigned int *cmd_flag)
{
	int		status;

	*cmd_flag ^= BLK_ROOM | BLK_TUBE;
	if (!env->map)
		return (ERR_ENV_EMPTY);
	if (!env->start)
		return (ERR_ENV_EMPTY_START);
	if (!env->end)
		return (ERR_ENV_EMPTY_END);
	status = create_ordered_rooms_array(env);
	if (status != SUCCESS)
		return (status);
	if (create_adjacency_matrix(env) != SUCCESS)
		return (ERR_ENV_ADJACENCY_MATRIX);
	return (SUCCESS);
}
