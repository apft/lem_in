/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_end.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:38:30 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 16:34:59 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEAD_END_H
# define DEAD_END_H

# include "env.h"
# include "customlibft.h"

int		search_for_dead_end(t_room *current, t_room *neighbour,
				t_env *env, t_queue *queue);

#endif
