/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 22:00:15 by apion             #+#    #+#             */
/*   Updated: 2019/03/18 13:00:12 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "parser.h"

int				print_str(int fd, const char *str, unsigned int size)
{
	int	ret;

	ret = write(fd, str, size);
	free((void *)str);
	return (ret);
}

int				parse_size(const char *f, va_list ap)
{
	t_specs		specs;
	int			n;

	n = 0;
	while (*f)
	{
		specs = (t_specs){0, 0, 0, 0, 0, 0, 0, 0, 0};
		if (*f == '%' && parse_specs(&f, &specs, ap, 0))
			n += specs.width;
		else
			++n;
		if (*f)
			++f;
	}
	return (n);
}

char			*extract_str(const char *f, int n, va_list ap)
{
	char		*str;
	int			i;
	t_specs		specs;

	str = (char *)malloc(sizeof(*str) * (n + 1));
	if (!str)
		return (0);
	i = 0;
	while (*f)
	{
		specs = (t_specs){0, 0, 0, 0, 0, 0, 0, 0, 0};
		if (*f == '%' && parse_specs(&f, &specs, ap, str + i))
			i += specs.width;
		else
			*(str + i++) = *f;
		if (*f)
			++f;
	}
	*(str + n) = 0;
	return (str);
}
