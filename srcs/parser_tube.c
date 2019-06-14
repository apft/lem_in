/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:24:44 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/12 17:18:42 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "libft.h"
#include "customlibft.h"
#include "parser.h"

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

static int	cmp_second_room_name_in_tube(char *str, t_room **room)
{
	return (ft_strcmp(str, (*room)->name));
}

int			handle_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	int		id_dash;
	int		id_room1;
	int		id_room2;

	if (ft_nchar(line, '-') != 1)
		return (err_tube_invalid_nb_dash);
	if (*cmd_flag & (CMD_START | CMD_END))
		return (err_env_wrong_cmd_start_or_end);
	id_dash = 0;
	while (line[id_dash] != '-')
		++id_dash;
	id_room1 = get_room_id_by_name(line, env, &cmp_first_room_name_in_tube);
	if (id_room1 < 0)
		return (err_tube_room_not_found);
	id_room2 = get_room_id_by_name(
			line + id_dash + 1, env, &cmp_second_room_name_in_tube);
	if (id_room2 < 0)
		return (err_tube_room_not_found);
	env->matrix[id_room1][id_room2] = 1;
	env->matrix[id_room2][id_room1] = 1;
	return (SUCCESS);
}
