/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:46:18 by apion             #+#    #+#             */
/*   Updated: 2019/02/20 12:47:47 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VPRINTF_H
# define FT_VPRINTF_H

int		ft_vprintf(const char *restrict format, va_list ap);
int		ft_vdprintf(int fd, const char *restrict format, va_list ap);
int		ft_vasprintf(char **str, const char *restrict format, va_list ap);

#endif
