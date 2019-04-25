/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:20:57 by apion             #+#    #+#             */
/*   Updated: 2019/04/25 15:22:01 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

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

int			handle_room(char *line, t_env *env, unsigned int *cmd_flag)
{
	int		i;
	char	*end;
	t_room	room;
	t_list	*node;

	if (*cmd_flag & BLK_TUBE)
		return (ERR_INVALID_TUBE);
	if (ft_nchar(line, ' ') < 2)
		return (ERR_INVALID_ROOM_NB_ARG);
	end = ft_strchr(line, '\0') - 1;
	if (extract_coord(&end, &room.y) != SUCCESS)
		return (ERR_INVALID_Y_COORD);
	if (extract_coord(&end, &room.x) != SUCCESS)
		return (ERR_INVALID_X_COORD);
	i = 0;
	while (line[i] != end)
		if (!ft_isprint(line[i]))
			return (ERR_INVALID_ROOM_NAME);
	room.name = ft_strndup(line, i);
	if (is_room_duplicate(room.name, env))
		return (ft_strdel_ret(&room.name, ERR_ROOM_DUPLICATED));
	if (!room.name)
		return (errno);
	node = ft_lstnew((void *)room, sizeof(room));
	if (!node)
		return (errno);
	ft_lstadd(&env->map, node);
	++env->nb_room;
	return (SUCCESS);
}

