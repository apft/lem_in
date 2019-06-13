/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:12:19 by apion             #+#    #+#             */
/*   Updated: 2019/06/11 17:49:55 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "env.h"

void	print_output(t_env *env);
void	print_paths(t_env *env);
void	print_matrix(t_env *env);
void	print_room(t_room *room, char *after);

#endif
