/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:24:39 by apion             #+#    #+#             */
/*   Updated: 2019/06/13 12:01:18 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "env.h"
# include "room.h"

typedef struct s_path	t_path;
struct	s_path
{
	t_room	*front;
	t_room	*back;
	t_room	*current;
	int		length;
	int		nb_ants_stream;
	int		path_printed;
};

int		compute_sum_path_lengths(t_room *start, t_room *current, t_env *env,
						int *lengths);
int		create_paths_array(t_env *env, int nb_path);
int		fill_paths_array(t_env *env);

#endif
