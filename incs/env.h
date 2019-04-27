/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:03:28 by apion             #+#    #+#             */
/*   Updated: 2019/04/27 17:30:26 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "list_line.h"
# include "room.h"

typedef struct s_env	t_env;
struct	s_env
{
	int			nb_ants;
	t_list_line	*lines;
	t_list		*map;
	t_room		**rooms_array;
	int			nb_room;
	t_room		*start;
	t_room		*end;
	int			**matrix;
};

#endif
