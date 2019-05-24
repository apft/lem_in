/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:39:52 by apion             #+#    #+#             */
/*   Updated: 2019/05/24 11:42:19 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H

# define ROOM_UNDEF_VALUE	-1

# define ROOM_NAME_ONLY		0x1
# define ROOM_NAME_IN_TUBE	0x2

# define FL_CLOSE_PATH		0x1

typedef struct s_room	t_room;

# include "env.h"

struct	s_room
{
	char			*name;
	int				x;
	int				y;
	int				id;
	int				visited;
	int				nb_neighbour;
	int				dst;
	t_room			*from;
	t_room			*from_junction;
	t_room			*next;
	unsigned int	flag;
};

int		get_room_id_by_name(char *str, t_env *env, int context);

#endif
