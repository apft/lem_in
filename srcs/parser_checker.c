/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:24:44 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/25 15:28:56 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "parser.h"

static int	handle_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	if (*cmd_flag & BLK_ROOM)
	{
		*cmd_flag ^= BLK_ROOM | BLK_TUBE;
		// create sorted room array
	}
	return (SUCCESS);
}

int			handle_room_or_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	if (ft_strchr(line, '-'))
		return (handle_tube(line, env, cmd_flag));
	else
		return (handle_room(line, env, cmd_flag));
}
