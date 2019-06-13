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
	ERR_INVALID_OPTION = -255,
	ERR_ANTS_BEGIN,
	ERR_ANTS_READ,
	ERR_ANTS_EOL_NO_NEWLINE,
	ERR_ANTS_ATOI,
	ERR_ANTS_NEG_NB,
	ERR_ANTS_ADD_LINE,
	ERR_ANTS_END,
	ERR_PARSER_EOL_NO_NEWLINE,
	ERR_PARSER_EMPTY_LINE,
	ERR_PARSER_L_BEGIN,
	ERR_PARSER_ADD_LINE,
	ERR_PARSER_EOF_NO_NEWLINE,
	ERR_ROOM_BEGIN,
	ERR_ROOM_INVALID_NB_ARG,
	ERR_ROOM_TREE_FAILED,
	ERR_ROOM_INVALID_Y_COORD,
	ERR_ROOM_INVALID_X_COORD,
	ERR_ROOM_INVALID_NAME,
	ERR_ROOM_DUPLICATED,
	ERR_ROOM_START_ALREADY_DEFINED,
	ERR_ROOM_END_ALREADY_DEFINED,
	ERR_ROOM_END,
	ERR_ENV_BEGIN,
	ERR_ENV_EMPTY,
	ERR_ENV_EMPTY_START,
	ERR_ENV_EMPTY_END,
	ERR_ENV_LST_TO_ARRAY,
	ERR_ENV_ARRAY_SORT,
	ERR_ENV_ADJACENCY_MATRIX,
	ERR_ENV_NO_PATH_FROM_START_TO_END,
	ERR_ENV_NO_TUBE,
	ERR_ENV_WRONG_CMD_START_OR_END,
	ERR_ENV_END,
	ERR_TUBE_INVALID_NB_DASH,
	ERR_TUBE_ROOM_NOT_FOUND,
	ERR_TUBE_HAS_SPACES,
	ERR_ATOI_EMPTY,
	ERR_ATOI_NO_DIGITS,
	ERR_ATOI_NEG,
	ERR_ATOI_OVERFLOW,
	ERR_ATOI_INVALID_CHAR,
	ERR_NULL_POINTER,
};

typedef struct s_env	t_env;

int		print_error_and_return(int error, t_env *env);

#endif
