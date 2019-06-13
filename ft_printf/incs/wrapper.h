/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 22:02:05 by apion             #+#    #+#             */
/*   Updated: 2019/03/18 13:09:22 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H

int				print_str(int fd, const char *str, unsigned int size);
int				parse_size(const char *f, va_list ap);
char			*extract_str(const char *f, int n, va_list ap);

#endif
