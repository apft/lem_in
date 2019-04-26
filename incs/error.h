/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:16:03 by apion             #+#    #+#             */
/*   Updated: 2019/04/26 10:35:37 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>

# define SUCCESS	0

enum	e_error
{
	ERR_READ = -1000,
	ERR_ATOI,
	ERR_ATOI_EMPTY,
	ERR_ATOI_NO_DIGITS,
	ERR_ATOI_NEG,
	ERR_ATOI_OVERFLOW,
	ERR_ATOI_INVALID_CHAR,
	ERR_EOF_NO_NEWLINE,
	ERR_EMPTY_LINE,
	ERR_L_BEGIN,
	ERR_INVALID_ROOM_NB_ARG,
	ERR_INVALID_Y_COORD,
	ERR_INVALID_X_COORD,
	ERR_INVALID_ROOM_NAME,
	ERR_INVALID_TUBE,
	ERR_NULL_POINTER,
	ERR_LST_TO_ARRAY_FAILED,
	ERR_ROOM_DUPLICATED,
	ERR_ANTS
};

#endif
