/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:24:39 by apion             #+#    #+#             */
/*   Updated: 2019/06/06 12:40:29 by jkettani         ###   ########.fr       */
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

int		create_paths_array(t_env *env, int nb_path);

#endif