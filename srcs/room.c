/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:59:01 by apion             #+#    #+#             */
/*   Updated: 2019/04/29 16:50:28 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "customlibft.h"

static int	cmp_room_name(char *str, t_room **room)
{
	return (ft_strcmp(str, (*room)->name));
}

static int	cmp_first_room_name_in_tube(char *str, t_room **room)
{
	int		id_dash;

	id_dash = 0;
	while (str[id_dash] != '-')
		++id_dash;
	return (ft_strncmp(str, (*room)->name, id_dash));
}

int			get_room_id_by_name(char *str, t_env *env, int context)
{
	t_array_args	array_args;
	int				(*cmp)();

	array_args = (t_array_args)
			{env->rooms_array, sizeof(t_room *), env->nb_room};
	if (context == ROOM_NAME_IN_TUBE)
		cmp = &cmp_first_room_name_in_tube;
	else
		cmp = &cmp_room_name;
	return (ft_bsearch_id(str, &array_args, *cmp));
}
