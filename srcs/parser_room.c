/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:20:57 by apion             #+#    #+#             */
/*   Updated: 2019/05/14 14:22:42 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env.h"
#include "atoi_pos.h"
#include "error.h"
#include "customlibft.h"
#include <limits.h>

static int	extract_coord(char **str_end, int *coord)
{
	while (!ft_isspace(**str_end))
		--(*str_end);
	if (atoi_pos(*str_end, coord, ATOI_NBR_IN_STR) == SUCCESS)
		return (SUCCESS);
	else
		return (ERR_ATOI);
}

static int	cmp_room_name(t_room *room, char *name)
{
	if (ft_strequ(room->name, name))
		return (0);
	return (1);
}

static int	is_room_duplicate(char *name, t_env *env)
{
	if (ft_lstfindfirst(env->map, name, &cmp_room_name))
		return (1);
	return (0);
}

static int	is_print_str(char *str, char *end)
{
	while (str != end)
		if (!ft_isprint(*str++))
			return (0);
	return (1);
}

static int	extract_start_or_end(t_room *room, t_env *env, unsigned int *cmd_flag)
{
	if (env->start && (*cmd_flag & CMD_START))
		return (ERR_ROOM_START_ALREADY_DEFINED);
	if (env->end && (*cmd_flag & CMD_END))
		return (ERR_ROOM_END_ALREADY_DEFINED);
	if (*cmd_flag & CMD_START)
	{
		env->start = room;
		*cmd_flag ^= CMD_START;
	}
	else if (*cmd_flag & CMD_END)
	{
		env->end = room;
		*cmd_flag ^= CMD_END;
	}
	return (SUCCESS);
}

int			handle_room(char *line, t_env *env, unsigned int *cmd_flag)
{
	char	*end;
	t_room	room;
	t_list	*node;

	room = (t_room){0, ROOM_UNDEF_VALUE, ROOM_UNDEF_VALUE, -1, 0, 0, INT_MAX,0};
	if (*cmd_flag & BLK_TUBE)
		return (ERR_INVALID_TUBE);
	if (ft_nchar(line, ' ') != 2)
		return (ERR_INVALID_ROOM_NB_ARG);
	end = ft_strchr(line, '\0') - 1;
	if (extract_coord(&end, &room.y) != SUCCESS)
		return (ERR_INVALID_Y_COORD);
	--end;
	if (extract_coord(&end, &room.x) != SUCCESS)
		return (ERR_INVALID_X_COORD);
	if (!is_print_str(line, end))
		return (ERR_INVALID_ROOM_NAME);
	room.name = ft_strndup(line, end - line);
	if (!room.name)
		return (errno);
	if (is_room_duplicate(room.name, env))
		return (ft_strdel_ret(&room.name, ERR_ROOM_DUPLICATED));
	node = ft_lstnew((void *)&room, sizeof(room));
	if (!node)
		return (errno);
	ft_lstadd(&env->map, node);
	++env->nb_room;
	if (*cmd_flag & (CMD_START | CMD_END))
		return (extract_start_or_end(env->map->content, env, cmd_flag));
	return (SUCCESS);
}
