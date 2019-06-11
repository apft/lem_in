/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:03:18 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/11 11:48:59 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "env.h"

int			check_map(t_env *env);
void		matrix_filter(t_env *env);
int			start_directly_linked_to_end(t_env *env);

#endif
