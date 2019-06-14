/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:09:34 by apion             #+#    #+#             */
/*   Updated: 2019/06/14 11:08:50 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "env.h"
#include "ft_printf.h"
#include "options.h"
#include <unistd.h>

t_error		g_error[] =
{
	{err_invalid_option, "[options] invalid option"},
	{err_ants_read, "[ants] could not read file"},
	{err_ants_eol_no_newline, "[ants] no newline at end of line"},
	{err_ants_atoi, "[ants] invalid number of ants"},
	{err_ants_neg_nb, "[ants] negative number of ants"},
	{err_ants_add_line, "[ants] could not add line"},
	{err_parser_eol_no_newline, "[parser] no newline at end of line"},
	{err_parser_empty_line, "[parser] empty line"},
	{err_parser_l_begin, "[parser] line start with 'L'"},
	{err_parser_add_line, "[parser] could not add line"},
	{err_parser_eof_no_newline, "[parser] no newline at end of file"},
	{err_room_invalid_nb_arg, "[room] invalid number of arguments (room x y)"},
	{err_room_tree_failed, "[room] could not create tree"},
	{err_room_invalid_y_coord, "[room] invalid Y coord"},
	{err_room_invalid_x_coord, "[room] invalid X coord"},
	{err_room_invalid_name, "[room] invalid room name"},
	{err_room_duplicated, "[room] name already exists"},
	{err_room_start_already_defined, "[room] start already defined"},
	{err_room_end_already_defined, "[room] end already defined"},
	{err_env_empty, "[env] empty"},
	{err_env_empty_start, "[env] no start defined"},
	{err_env_empty_end, "[env] no end defined"},
	{err_env_lst_to_array, "[env] list to array failed"},
	{err_env_array_sort, "[env] sorting array failed"},
	{err_env_adjacency_matrix, "[env] creating adjacency matrix failed"},
	{err_env_no_tube, "[env] no tubes defined"},
	{err_env_wrong_cmd_start_or_end, "[env] wrong command start or end"},
	{err_env_no_path_from_start_to_end, "[env] no path start-end"},
	{err_tube_invalid_nb_dash, "[tube] invalid number of '-' in tube"},
	{err_tube_room_not_found, "[tube] room does not exist"},
	{err_tube_has_spaces, "[tube] tube definition has spaces"},
	{err_atoi_empty, "[atoi] no input"},
	{err_atoi_no_digits, "[atoi] no digit"},
	{err_atoi_neg, "[atoi] can not be < 0"},
	{err_atoi_overflow, "[atoi] input too large (overflow)"},
	{err_atoi_invalid_char, "[atoi] invalid char"},
	{err_null_pointer, "null pointer"}
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
