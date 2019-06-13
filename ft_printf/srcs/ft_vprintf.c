/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:27:15 by apion             #+#    #+#             */
/*   Updated: 2019/03/18 13:06:07 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "wrapper.h"

int		ft_vasprintf(char **str, const char *restrict format, va_list ap_length)
{
	va_list		ap_fill;
	int			n;

	va_copy(ap_fill, ap_length);
	n = parse_size(format, ap_length);
	if (n < 0)
		return (-1);
	*str = extract_str(format, n, ap_fill);
	va_end(ap_fill);
	return (*str ? n : -1);
}

int		ft_vdprintf(int fd, const char *restrict format, va_list ap)
{
	char	*str;
	int		size;

	str = 0;
	size = ft_vasprintf(&str, format, ap);
	if (size > 0)
		return (print_str(fd, str, size));
	return (size);
}

int		ft_vprintf(const char *restrict format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}
