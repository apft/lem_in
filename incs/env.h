/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:03:28 by apion             #+#    #+#             */
/*   Updated: 2019/06/06 14:33:48 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "list_line.h"
# include "room.h"
# include "path.h"

typedef unsigned int	t_uint;

typedef struct s_env	t_env;
struct	s_env
{
	t_uint		options;
	int			nb_ants;
	t_list_line	*lines;
	t_list		*map;
	t_room		**rooms_array;
	int			nb_rooms;
	t_room		*start;
	t_room		*end;
	int			**matrix;
	int			nb_paths;
	int			flow;
	t_path		**paths_array;
};

#endif
