/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 17:46:31 by apion             #+#    #+#             */
/*   Updated: 2019/03/25 18:36:00 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRACTOR_H
# define EXTRACTOR_H

# include <stdarg.h>
# include "utils.h"

int		extract_int_conv(va_list ap, t_specs *specs, char *str);
int		extract_char_conv(va_list ap, t_specs *specs, char *str);
int		extract_str_conv(va_list ap, t_specs *specs, char *str);
int		extract_pointer_conv(va_list ap, t_specs *specs, char *str);
int		extract_float_conv(va_list ap, t_specs *specs, char *str);

int		clear_screen(va_list ap, t_specs *specs, char *str);
int		apply_effect(const char **effect, t_specs *specs, char *str);

#endif
