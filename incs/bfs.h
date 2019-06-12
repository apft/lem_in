/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:20:53 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 16:20:08 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BFS_H
# define BFS_H

# include "env.h"
# include "customlibft.h"

int		bfs(t_env *env);
void	bfs_remove_dead_end_path(t_env *env);
void	bfs_max_flow(t_env *env, t_queue *queue);

#endif
