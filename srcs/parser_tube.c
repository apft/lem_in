/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:24:44 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/07 14:14:34 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "customlibft.h"

int			handle_tube(char *line, t_env *env)
{
	int		id_dash;
	int		id_room1;
	int		id_room2;

	if (ft_nchar(line, '-') != 1)
		return (ERR_TUBE_INVALID_NB_DASH);
	id_dash = 0;
	while (line[id_dash] != '-')
		++id_dash;
	id_room1 = get_room_id_by_name(line, env, ROOM_NAME_IN_TUBE);
	if (id_room1 < 0)
		return (ERR_TUBE_ROOM_NOT_FOUND);
	id_room2 = get_room_id_by_name(line + id_dash + 1, env, ROOM_NAME_ONLY);
	if (id_room2 < 0)
		return (ERR_TUBE_ROOM_NOT_FOUND);
	env->matrix[id_room1][id_room2] = 1;
	env->matrix[id_room2][id_room1] = 1;
	return (SUCCESS);
}
