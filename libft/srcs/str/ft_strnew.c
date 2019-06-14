/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:28:40 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/14 11:46:51 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

char	*ft_strnew(size_t size)
{
	char	*str;

	if (size == ULLONG_MAX
		|| !(str = (char *)malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}
