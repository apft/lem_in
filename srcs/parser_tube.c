/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:24:44 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/12 12:28:54 by pion             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "libft.h"
#include "customlibft.h"
#include "parser.h"

static int	cmp_room_name(char *str, t_room **room)
{
	return (ft_strcmp(str, (*room)->name));
}

static int	cmp_first_room_name_in_tube(char *str, t_room **room)
{
	int		id_dash;
	int		res;

	id_dash = 0;
	while (str[id_dash] != '-')
		++id_dash;
	res = ft_strncmp(str, (*room)->name, id_dash);
	if (res == 0)
		return (res - (*room)->name[id_dash]);
	else
		return (res);
}

int			handle_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	int		id_dash;
	int		id_room1;
	int		id_room2;

	if (ft_nchar(line, '-') != 1)
		return (ERR_TUBE_INVALID_NB_DASH);
	if (*cmd_flag & (CMD_START | CMD_END))
		return (ERR_ENV_WRONG_CMD_START_OR_END);
	id_dash = 0;
	while (line[id_dash] != '-')
		++id_dash;
	id_room1 = get_room_id_by_name(line, env, &cmp_first_room_name_in_tube);
	if (id_room1 < 0)
		return (ERR_TUBE_ROOM_NOT_FOUND);
	id_room2 = get_room_id_by_name(line + id_dash + 1, env, &cmp_room_name);
	if (id_room2 < 0)
		return (ERR_TUBE_ROOM_NOT_FOUND);
	env->matrix[id_room1][id_room2] = 1;
	env->matrix[id_room2][id_room1] = 1;
	return (SUCCESS);
}
