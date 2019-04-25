/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:24:44 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/25 13:14:09 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

int		extract_coord(char **str_end, int *coord)
{
	while (!ft_isspace(**str_end))
		--(*str_end);
	if (atoi_pos(*str_end, coord, ATOI_NBR_IN_STR) == SUCCESS)
		return (SUCCESS);
	else
		return (ERR_ATOI);
}

int		handle_room(char *line, t_env *env, unsigned int *cmd_flag)
{
	char	*end;
	t_room	room;

	end = ft_strchr(line, '\0') - 1;
	//TODO ft_nchar --> check number of args
	if (end == line)
		return (ERR_INVALID_ROOM_NB_ARG);
	if (extract_coord(&end, &room.y) != SUCCESS)
		return (ERR_INVALID_Y_COORD);
	if (extract_coord(&end, &room.x) != SUCCESS)
		return (ERR_INVALID_X_COORD);
}

int		handle_room_or_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	if (ft_strchr(line, '-'))
		return (handle_tube(line, env, cmd_flag));
	else
		return (handle_room(line, env, cmd_flag));
}
