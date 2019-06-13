/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:09:34 by apion             #+#    #+#             */
/*   Updated: 2019/06/13 18:12:41 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "env.h"
#include "ft_printf.h"
#include "options.h"
#include <unistd.h>

t_error		g_error[] =
{
	{ERR_INVALID_OPTION, "[options] invalid option"},
	{ERR_ANTS_READ, "[ants] could not read file"},
	{ERR_ANTS_EOL_NO_NEWLINE, "[ants] no newline at end of line"},
	{ERR_ANTS_ATOI, "[ants] invalid number of ants"},
	{ERR_ANTS_NEG_NB, "[ants] negative number of ants"},
	{ERR_ANTS_ADD_LINE, "[ants] could not add line"},
	{ERR_PARSER_EOL_NO_NEWLINE, "[parser] no newline at end of line"},
	{ERR_PARSER_EMPTY_LINE, "[parser] empty line"},
	{ERR_PARSER_L_BEGIN, "[parser] line start with 'L'"},
	{ERR_PARSER_ADD_LINE, "[parser] could not add line"},
	{ERR_PARSER_EOF_NO_NEWLINE, "[parser] no newline at end of file"},
	{ERR_ROOM_INVALID_NB_ARG, "[room] invalid number of arguments (room x y)"},
	{ERR_ROOM_TREE_FAILED, "[room] could not create tree"},
	{ERR_ROOM_INVALID_Y_COORD, "[room] invalid Y coord"},
	{ERR_ROOM_INVALID_X_COORD, "[room] invalid X coord"},
	{ERR_ROOM_INVALID_NAME, "[room] invalid room name"},
	{ERR_ROOM_DUPLICATED, "[room] name already exists"},
	{ERR_ROOM_START_ALREADY_DEFINED, "[room] start already defined"},
	{ERR_ROOM_END_ALREADY_DEFINED, "[room] end already defined"},
	{ERR_ENV_EMPTY, "[env] empty"},
	{ERR_ENV_EMPTY_START, "[env] no start defined"},
	{ERR_ENV_EMPTY_END, "[env] no end defined"},
	{ERR_ENV_LST_TO_ARRAY, "[env] list to array failed"},
	{ERR_ENV_ARRAY_SORT, "[env] sorting array failed"},
	{ERR_ENV_ADJACENCY_MATRIX, "[env] creating adjacency matrix failed"},
	{ERR_ENV_NO_TUBE, "[env] no tubes defined"},
	{ERR_ENV_WRONG_CMD_START_OR_END, "[env] wrong command start or end"},
	{ERR_ENV_NO_PATH_FROM_START_TO_END, "[env] no path start-end"},
	{ERR_TUBE_INVALID_NB_DASH, "[tube] invalid number of '-' in tube"},
	{ERR_TUBE_ROOM_NOT_FOUND, "[tube] room does not exist"},
	{ERR_TUBE_HAS_SPACES, "[tube] tube definition has spaces"},
	{ERR_ATOI_EMPTY, "[atoi] no input"},
	{ERR_ATOI_NO_DIGITS, "[atoi] no digit"},
	{ERR_ATOI_NEG, "[atoi] can not be < 0"},
	{ERR_ATOI_OVERFLOW, "[atoi] input too large (overflow)"},
	{ERR_ATOI_INVALID_CHAR, "[atoi] invalid char"},
	{ERR_NULL_POINTER, "null pointer"}
};

static void	custom_print_error(int error, char *error_msg, t_env *env)
{
	ft_dprintf(STDERR_FILENO, "ERROR");
	if (env->options & OP_ERR)
		ft_dprintf(STDERR_FILENO, ": (%d) %s", error, error_msg);
	ft_dprintf(STDERR_FILENO, "\n");
}

static char	*custom_strerror(int error)
{
	int		size;

	size = sizeof(g_error) / sizeof(t_error);
	while (size--)
		if (g_error[size].value == error)
			return (g_error[size].msg);
	return ("error message not defined...");
}

static void	print_error(int error, t_env *env)
{
	char	*error_msg;

	if (error > 0)
		error_msg = strerror(error);
	else
		error_msg = custom_strerror(error);
	custom_print_error(error, error_msg, env);
}

int			print_error_and_return(int error, t_env *env)
{
	print_error(error, env);
	return (ERROR);
}
