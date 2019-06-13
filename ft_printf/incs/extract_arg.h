/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:15:49 by apion             #+#    #+#             */
/*   Updated: 2019/03/18 15:08:52 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRACT_ARG_H
# define EXTRACT_ARG_H

# include "utils.h"
# include "float_pf.h"

void	extract_arg_integer(va_list ap, union u_value *value, int flag);
void	extract_arg_uinteger(va_list ap, union u_value *value, int flag);
char	*extract_arg_str(va_list ap);
void	extract_arg_double(va_list ap, union u_double *value, int flag);

#endif
