/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:24:39 by apion             #+#    #+#             */
/*   Updated: 2019/05/31 16:36:22 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

typedef struct s_path	t_path;
struct	s_path
{
	t_room	*front;
	t_room	*back;
	t_room	*current;
};

int		create_path_array(t_env *env, int nb_path);

#endif
