/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 17:38:22 by apion             #+#    #+#             */
/*   Updated: 2019/03/15 21:13:58 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTER_H
# define FILTER_H

# include "utils.h"

void	print_specs(t_specs *specs);
void	clear_flags(t_specs *specs, int flags);
void	filter_specs(t_specs *specs);

#endif
