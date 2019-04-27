/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:57:48 by apion             #+#    #+#             */
/*   Updated: 2019/04/26 21:19:25 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parser.h"
#include "env.h"
#include "atoi_pos.h"
#include "get_next_line.h"
#include "error.h"

static int	get_cmd(char *line)
{
	if (ft_strequ(line, "start"))
		return (CMD_START);
	else if (ft_strequ(line, "end"))
		return (CMD_END);
	else
		return (CMD_UNDEF);
}

static int	get_number_ants(t_env *env)
{
	char	*line;
	int		len;
	int		eol_had_newline;
	int		status;

	len = get_next_line(STDIN_FILENO, &line, &eol_had_newline);
	if (len == GNL_ERROR)
		return (ERR_READ);
	status = atoi_pos(line, &(env->nb_ants), ATOI_NBR_AND_SPACES_ONLY);
	if (status == SUCCESS)
		if (list_line_add_first(&env->lines, line))
			return (errno);
	return (status);
}

static int	handle_room_or_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	int		status;

	if (ft_strchr(line, '-'))
	{
		if ((*cmd_flag & BLK_ROOM)
				&& (status = bake_environment(env, cmd_flag)) != SUCCESS)
			return (status);
		return (handle_tube(line, env, cmd_flag));
	}
	else
		return (handle_room(line, env, cmd_flag));
}

int			parser(t_env *env)
{
	char			*line;
	int				len;
	int				eol_had_newline;
	int				status;
	unsigned int	cmd_flag;

	cmd_flag = CMD_UNDEF;
	cmd_flag |= BLK_ROOM;
	if ((status = get_number_ants(env)) != SUCCESS)
		return (status);
	while ((len = get_next_line(STDIN_FILENO, &line, &eol_had_newline)) >= 0)
	{
		if (!*line)
			return (ERR_EMPTY_LINE);
		if (line[0] == 'L')
			return (ERR_L_BEGIN);
		if (line[0] == '#' && line[1] == '#')
			cmd_flag |= get_cmd(line + 2);
		else if (line[0] != '#')
			handle_room_or_tube(line, env, &cmd_flag);
		list_line_add_first(&env->lines, line);
	}
	if (!eol_had_newline)
		return (ERR_EOF_NO_NEWLINE);
	if (len == GNL_ERROR)
		return (errno);
	return (SUCCESS);
}
