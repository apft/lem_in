/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 18:55:48 by apion             #+#    #+#             */
/*   Updated: 2019/02/20 12:48:26 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int		ft_printf(const char *restrict f, ...);
int		ft_dprintf(int fd, const char *restrict f, ...);
int		ft_asprintf(char **str, const char *restrict f, ...);

#endif
