/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:16:03 by apion             #+#    #+#             */
/*   Updated: 2019/06/13 18:28:23 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>

# define SUCCESS	0
# define ERROR		-1

typedef struct s_error	t_error;
struct	s_error
{
	int		value;
	char	*msg;
};

enum	e_error
{
	err_invalid_option = -255,
	err_ants_begin,
	err_ants_read,
	err_ants_eol_no_newline,
	err_ants_atoi,
	err_ants_neg_nb,
	err_ants_add_line,
	err_ants_end,
	err_parser_eol_no_newline,
	err_parser_empty_line,
	err_parser_l_begin,
	err_parser_add_line,
	err_parser_eof_no_newline,
	err_room_begin,
	err_room_invalid_nb_arg,
	err_room_tree_failed,
	err_room_invalid_y_coord,
	err_room_invalid_x_coord,
	err_room_invalid_name,
	err_room_duplicated,
	err_room_start_already_defined,
	err_room_end_already_defined,
	err_room_end,
	err_env_begin,
	err_env_empty,
	err_env_empty_start,
	err_env_empty_end,
	err_env_lst_to_array,
	err_env_array_sort,
	err_env_adjacency_matrix,
	err_env_no_path_from_start_to_end,
	err_env_no_tube,
	err_env_wrong_cmd_start_or_end,
	err_env_end,
	err_tube_invalid_nb_dash,
	err_tube_room_not_found,
	err_tube_has_spaces,
	err_atoi_empty,
	err_atoi_no_digits,
	err_atoi_neg,
	err_atoi_overflow,
	err_atoi_invalid_char,
	err_null_pointer,
};

typedef struct s_env	t_env;

int		print_error_and_return(int error, t_env *env);

#endif
