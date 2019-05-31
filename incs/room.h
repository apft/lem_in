/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:39:52 by apion             #+#    #+#             */
/*   Updated: 2019/05/31 12:56:45 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H

# define ROOM_UNDEF_VALUE	-1

# define ROOM_NAME_ONLY		0x1
# define ROOM_NAME_IN_TUBE	0x2

# define VISITED_EMPTY			0x2
# define VISITED_AS_NEIGHBOUR	0x1
# define VISITED_AS_CURRENT		0x0

# define COST_INF		INT_MAX - 1

# define FL_CLOSE_PATH		0x1

typedef struct s_room	t_room;

# include <limits.h>
# include "env.h"

struct	s_room
{
	char		*name;
	int			x;
	int			y;
	int			id;
	t_room		*from;
	t_room		*from_junction;
	t_room		*next;
	int			visited;
	int			cost[2]; // [0]: external cost, [1]: internal cost
	int			flag;
	int			dst;
};


int		external_cost(t_room *room);
int		internal_cost(t_room *room);
int		is_junction(t_room *room);
int		is_closed_path(t_room *room);
int		is_linked_on_same_path(t_room *room_a, t_room *room_b);

int		get_room_id_by_name(char *str, t_env *env, int context);

void	apply_foreach_room_linked_to_ref(t_room *ref, t_env *env, void *data,
			void (*fct)());

void	print_room(t_room *room, char *after);

#endif
