/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_hexa.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 19:47:49 by apion             #+#    #+#             */
/*   Updated: 2019/03/25 13:43:01 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_HEXA_H
# define FLOAT_HEXA_H

# include "float_pf.h"

unsigned int	float_hexa_extract_byte(unsigned long n, int byte_index);
int				float_hexa_round(t_field *fields, char *base, char *str,
								int precision);

#endif
