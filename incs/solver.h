/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:15:52 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/11 17:03:47 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

# include "env.h"
# include "customlibft.h"

int		search_for_valid_neighbour(t_room *current, t_room *neighbour,
				t_env *env, t_queue *queue);
int		solver(t_env *env);

#endif
