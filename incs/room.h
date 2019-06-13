/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:39:52 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 17:34:33 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H

# include <limits.h>

# include "error.h"

# define ROOM_NAME_ONLY		    0x1
# define ROOM_NAME_IN_TUBE	    0x2

# define VISITED_EMPTY			0x2
# define VISITED_AS_NEIGHBOUR	0x1
# define VISITED_AS_CURRENT		0x0

# define COST_INF	            (INT_MAX - 1)

# define FL_CLOSE_PATH		    0x1
# define FL_DIRECT_TO_END       0x2

/*
**cost[0]: external cost, cost[1]: internal cost
*/
typedef struct s_room	t_room;
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
	int			cost[2];
	int			flag;
	int			dst;
	int			ant;
};

enum	e_loop_foreach
{
	LOOP_BREAK = -2,
	LOOP_CONTINUE = -1,
	LOOP_SUCCESS = SUCCESS,
};

typedef struct s_env	t_env;

t_room	*create_empty_room(void);
int		external_cost(t_room *room);
int		internal_cost(t_room *room);
int		get_room_id_by_name(char *str, t_env *env, int (*cmp)());
int		cmp_room_name(void *room1, void *room2);

int		is_junction(t_room *room);
int		is_closed_path(t_room *room);
int		is_linked_on_same_path(t_room *room_a, t_room *room_b);
int		is_closed_room_as_junction(t_room *current);

int		apply_foreach_room_linked_to_ref(t_room *ref, t_env *env, void *data,
			int (*fct)());

#endif
