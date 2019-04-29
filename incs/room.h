/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:39:52 by apion             #+#    #+#             */
/*   Updated: 2019/04/29 16:34:09 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H

# define ROOM_NAME_ONLY		0x1
# define ROOM_NAME_IN_TUBE	0x2

typedef struct s_room	t_room;

# include "env.h"

struct	s_room
{
	char	*name;
	int		x;
	int		y;
	int		id;
	int		is_empty;
};

int		get_room_id(char *str, t_env *env, int context);

#endif
