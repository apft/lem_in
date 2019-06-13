/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:20:57 by apion             #+#    #+#             */
/*   Updated: 2019/06/13 09:32:47 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env.h"
#include "atoi_pos.h"
#include "cleaner.h"
#include "error.h"
#include "customlibft.h"
#include <limits.h>

static int	is_room_duplicate(char *name, t_env *env)
{
	static t_room	ref;

	ref.name = name;
	if (btree_search_item(env->rooms_tree, &ref, &cmp_room_name))
		return (1);
	return (0);
}

static int	extract_coord(char **str_end, int *coord)
{
	int		status;

	while (!ft_isspace(**str_end))
		--(*str_end);
	if ((status = atoi_pos(*str_end, coord, ATOI_NBR_IN_STR)) != SUCCESS)
		return (status);
	else
		return (SUCCESS);
}

static int	extract_start_or_end(t_room *room, t_env *env,
				unsigned int *cmd_flag)
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

static int	extract_room_info(char *line, t_room *room, t_env *env)
{
	char	*end;

	end = ft_strchr(line, '\0') - 1;
	if (extract_coord(&end, &room->y) != SUCCESS)
		return (ERR_ROOM_INVALID_Y_COORD);
	--end;
	if (extract_coord(&end, &room->x) != SUCCESS)
		return (ERR_ROOM_INVALID_X_COORD);
	if (!ft_is_print_str(line, end))
		return (ERR_ROOM_INVALID_NAME);
	room->name = ft_strndup(line, end - line);
	if (!room->name)
		return (errno);
	if (ft_strchr(room->name, '-'))
		return (free_room_and_return((void *)room, ERR_ROOM_INVALID_NAME));
	if (is_room_duplicate(room->name, env))
		return (free_room_and_return((void *)room, ERR_ROOM_DUPLICATED));
	return (SUCCESS);
}

int			handle_room(char *line, t_env *env, unsigned int *cmd_flag)
{
	int			status;
	t_room		*room;

	if (*cmd_flag & BLK_TUBE)
		return (ERR_TUBE_HAS_SPACES);
	if (ft_nchar(line, ' ') != 2)
		return (ERR_ROOM_INVALID_NB_ARG);
	room = create_empty_room();
	if (!room)
		return (errno);
	if ((status = extract_room_info(line, room, env)) != SUCCESS)
		return (status);
	rb_insert(&env->rooms_tree, (void *)room, &cmp_room_name);
	++env->nb_rooms;
	if (*cmd_flag & (CMD_START | CMD_END))
	{
		status = extract_start_or_end(room, env, cmd_flag);
		if (status != SUCCESS)
			return (status);
	}
	return (SUCCESS);
}
