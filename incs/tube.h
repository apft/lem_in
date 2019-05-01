/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:16:28 by apion             #+#    #+#             */
/*   Updated: 2019/05/01 12:03:41 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUBE_H
# define TUBE_H

int		is_dead_end(t_env *env, int index, int index_parent);
void	remove_oriented_tube_between_rooms(t_env *env,
				t_room *room_a, t_room *room_b);
void	remove_tube_between_rooms(t_env *env, t_room *room_a, t_room *room_b);
void	remove_oriented_tubes_back_to_start_or_from_end(t_env *env);
void	remove_dead_end_path(t_room *dead_end, t_env *env);

#endif
