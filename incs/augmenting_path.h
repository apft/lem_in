/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augmenting_path.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:56:18 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 17:29:42 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUGMENTING_PATH_H
# define AUGMENTING_PATH_H

# include "env.h"

void	save_augmenting_path(t_env *env);
void	reset_to_previous_augmenting_path(t_env *env);

#endif
