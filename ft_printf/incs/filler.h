/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 17:30:15 by apion             #+#    #+#             */
/*   Updated: 2019/03/20 20:49:04 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define FILL_START -1

# include "utils.h"

int		fill_char(char *str, char c, int length);
int		filler(char *str, t_specs *specs, int is_start);

#endif
