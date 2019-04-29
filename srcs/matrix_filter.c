/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_filter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 12:49:20 by apion             #+#    #+#             */
/*   Updated: 2019/04/29 15:27:37 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	clean_diag(int **matrix, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		matrix[i][i] = 0;
		++i;
	}
}

static void	remove_back_to_start(int **matrix, int size, int id_start)
{
	int		i;

	i = 0;
	while (i < size)
	{
		matrix[i][id_start] = 0;
		++i;
	}
}

static void	remove_back_from_end(int **matrix, int size, int id_end)
{
	int		i;

	i = 0;
	while (i < size)
	{
		matrix[id_end][i] = 0;
		++i;
	}
}

void		matrix_filter(t_env *env)
{
	clean_diag(env->matrix, env->nb_room);
	remove_back_to_start(
			env->matrix,
			env->nb_room,
			get_room_id(env->start->name, env, ROOM_NAME_ONLY));
	remove_back_from_end(
			env->matrix,
			env->nb_room,
			get_room_id(env->end->name, env, ROOM_NAME_ONLY));

}
