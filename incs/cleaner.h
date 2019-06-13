/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <pion@student.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:49:03 by apion             #+#    #+#             */
/*   Updated: 2019/06/12 17:52:50 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANER_H
# define CLEANER_H

# include "env.h"

int		free_room_and_return(void *room, int status);
void	free_ptr_array_to_index(void ***array, int last_index);
int		free_mem(t_env *env);

#endif
