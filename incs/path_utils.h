/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:11:31 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/07 12:36:09 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_UTILS_H
# define PATH_UTILS_H

# include "env.h"

# define NO_UPDATE_LINKS	0
# define UPDATE_LINKS		1

int			fill_paths_array(t_env *env, int update_links);

#endif
