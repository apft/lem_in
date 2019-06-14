/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:57:48 by apion             #+#    #+#             */
/*   Updated: 2019/06/14 11:06:29 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env.h"
#include "atoi_pos.h"
#include "get_next_line.h"
#include "error.h"
#include "ft_printf.h"
#include <unistd.h>

static int	get_cmd(char *line)
{
	if (ft_strequ(line, "start"))
		return (CMD_START);
	else if (ft_strequ(line, "end"))
		return (CMD_END);
	else
		return (CMD_UNDEF);
}

static int	get_number_ants(char *line, t_env *env, unsigned int *cmd_flag)
{
	int		status;

	*cmd_flag ^= BLK_ANTS | BLK_ROOM;
	status = atoi_pos(line, &(env->nb_ants), ATOI_NBR_AND_SPACES_ONLY);
	if (status != SUCCESS)
		return (ERR_ANTS_ATOI);
	if (env->nb_ants < 0)
		return (ERR_ANTS_NEG_NB);
	return (SUCCESS);
}

static int	handle_room_or_tube(char *line, t_env *env, unsigned int *cmd_flag)
{
	int		status;

	if (ft_strchr(line, ' '))
		return (handle_room(line, env, cmd_flag));
	else
	{
		if ((*cmd_flag & BLK_ROOM)
			&& (status = bake_environment(env, cmd_flag)) != SUCCESS)
			return (status);
		return (handle_tube(line, env, cmd_flag));
	}
}

int			parse_and_save_line(char *line, t_env *env, unsigned int *cmd_flag)
{
	int		status;

	if (!*line)
		return (ERR_PARSER_EMPTY_LINE);
	if (line[0] == 'L')
		return (ERR_PARSER_L_BEGIN);
	if (line[0] == '#' && line[1] == '#')
	{
		if (*cmd_flag & (CMD_START | CMD_END))
			return (ERR_ENV_WRONG_CMD_START_OR_END);
		*cmd_flag |= get_cmd(line + 2);
	}
	if (line[0] != '#')
	{
		if (*cmd_flag & BLK_ANTS)
			status = get_number_ants(line, env, cmd_flag);
		else
			status = handle_room_or_tube(line, env, cmd_flag);
		if (status != SUCCESS)
			return (status);
	}
	if ((status = list_line_add_first(&env->lines, line)) != SUCCESS)
		return (ERR_PARSER_ADD_LINE);
	return (SUCCESS);
}

int			parser(t_env *env)
{
	char			*line;
	int				len;
	int				eol_had_newline;
	int				status;
	unsigned int	cmd_flag;

	cmd_flag = CMD_UNDEF | BLK_ANTS;
	line = NULL;
	eol_had_newline = 0;
	while ((len = get_next_line(STDIN_FILENO, &line, &eol_had_newline)) >= 0)
	{
		if (!eol_had_newline)
			return (ft_strdel_ret(&line, ERR_PARSER_EOL_NO_NEWLINE));
		if ((status = parse_and_save_line(line, env, &cmd_flag)) != SUCCESS)
			return (ft_strdel_ret(&line, status));
	}
	if (len == GNL_ERROR)
		return (errno);
	if (!eol_had_newline)
		return (ERR_PARSER_EOF_NO_NEWLINE);
	if (!(cmd_flag & BLK_TUBE))
		return (ERR_ENV_NO_TUBE);
	return (SUCCESS);
}
