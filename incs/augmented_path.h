/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augmented_path.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:56:18 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 13:56:52 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUGMENTED_PATH_H
# define AUGMENTED_PATH_H

# include "env.h"

void	save_augmented_path(t_env *env);
void	reset_to_previous_augmented_path(t_env *env);

#endif
