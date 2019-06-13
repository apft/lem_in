/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:16:28 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 12:42:04 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUBE_H
# define TUBE_H

# include "env.h"

int		has_oriented_tube_between_rooms_by_id(int id_room_a, int id_room_b,
			t_env *env);
int		has_oriented_tube_between_rooms(t_room *room_a, t_room *room_b,
			t_env *env);
void	remove_oriented_tube_between_rooms(t_env *env,
				t_room *room_a, t_room *room_b);
void	remove_tube_between_rooms(t_env *env, t_room *room_a, t_room *room_b);
void	remove_oriented_tubes_back_to_start_or_from_end(t_env *env);

#endif
