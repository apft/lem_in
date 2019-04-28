/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:24:44 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/28 13:49:36 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "libft.h"
#include "customlibft.h"

static char	*get_room_name(t_list *node)
{
	return (((t_room *)node->content)->name);
}

static int	cmp_room1(char *str, t_room **room)
{
	int		id_dash;

	id_dash = 0;
	while (str[id_dash] != '-')
		++id_dash;
	return (ft_strncmp(str, (*room)->name, id_dash));
}

static int	cmp_room2(char *str, t_room **room)
{
	return (ft_strcmp(str, (*room)->name));
}

int			handle_tube(char *line, t_env *env)
{
	int		id_dash;
	int		id_room1;
	int		id_room2;

	if (ft_nchar(line, '-') != 1)
		return (ERR_INVALID_TUBE_DEFINITION);
	id_dash = 0;
	while (line[id_dash] != '-')
		++id_dash;
	id_room1 = ft_bsearch_id(line, &((t_array_args){env->rooms_array, sizeof(t_room *), env->nb_room}), &cmp_room1);
	id_room2 = ft_bsearch_id(line + id_dash + 1, &((t_array_args){env->rooms_array, sizeof(t_room *), env->nb_room}), &cmp_room2);
	if (id_room1 < 0 || id_room2 < 0)
		return (ERR_ROOM_DOES_NOT_EXIST);

	get_room_name(env->map);
	return (SUCCESS);
}
