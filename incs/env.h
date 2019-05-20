/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:03:28 by apion             #+#    #+#             */
/*   Updated: 2019/05/20 15:33:16 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "list_line.h"

typedef struct s_env	t_env;

# include "room.h"

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

void	matrix_filter(t_env *env);
int		check_map(t_env *env);
int		solver(t_env *env);

#endif
