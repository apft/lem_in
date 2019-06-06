/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:09:34 by apion             #+#    #+#             */
/*   Updated: 2019/06/06 14:58:33 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "env.h"
#include "ft_printf.h"
# include "options.h"
#include <unistd.h>
#include <string.h>

#define OPTION_ERROR	1

t_error		g_error[] =
{
	{ERR_INVALID_OPTION, "[options] invalid option"},
	{ERR_READ, "[read]"},
	{ERR_ATOI, "[atoi]"},
	{ERR_ATOI_EMPTY, "[atoi] no input"},
	{ERR_ATOI_NO_DIGITS, "[atoi] no digit"},
	{ERR_ATOI_NEG, "[atoi] can not be < 0"},
	{ERR_ATOI_OVERFLOW, "[atoi] input too large (overflow)"},
	{ERR_ATOI_INVALID_CHAR, "[atoi] invalid char"},
	{ERR_EOF_NO_NEWLINE, "[read] no newline at end of file"},
	{ERR_NEG_NB_ANTS, "[ants] negative number of ants"},
	{ERR_EMPTY_LINE, "[read] empty line"},
	{ERR_L_BEGIN, "line start with 'L'"},
	{ERR_INVALID_ROOM_NB_ARG, "[room] invalid number of arguments (room x y)"},
	{ERR_INVALID_Y_COORD, "[room] invalid Y coord"},
	{ERR_INVALID_X_COORD, "[room] invalid X coord"},
	{ERR_INVALID_ROOM_NAME, "[room] invalid room name"},
	{ERR_INVALID_TUBE, "[tube] invalid tube format"},
	{ERR_NULL_POINTER, "null pointer"},
	{ERR_LST_TO_ARRAY_FAILED, "failed to create array based on list"},
	{ERR_ROOM_DUPLICATED, "[room] name already exists"},
	{ERR_ROOM_START_ALREADY_DEFINED, "[room] start already defined"},
	{ERR_ROOM_END_ALREADY_DEFINED, "[room] end already defined"},
	{ERR_EMPTY_MAP, "empty map"},
	{ERR_EMPTY_START, "empty start"},
	{ERR_EMPTY_END, "empty end"},
	{ERR_INVALID_TUBE_DEFINITION, "[tube] too many dash"},
	{ERR_ROOM_DOES_NOT_EXIST, "[tube] room name does not exist"},
	{ERR_ANTS, "invalid number of ants"},
	{ERR_NO_PATH_FROM_START_TO_END, "no path start-end"}
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

void		print_error(int error, t_env *env)
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
	return (-1);
}
