/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:39:52 by apion             #+#    #+#             */
/*   Updated: 2019/04/26 10:20:59 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H

typedef struct s_room	t_room;
struct	s_room
{
	char	*name;
	int		x;
	int		y;
	int		is_empty;
};

#endif
