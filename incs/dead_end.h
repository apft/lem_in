/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_end.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:38:30 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 12:39:01 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEAD_END_H
# define DEAD_END_H

int		is_dead_end(t_env *env, int index, int index_parent);
void	remove_dead_end_path(t_room *dead_end, t_env *env);

#endif
