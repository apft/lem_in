/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_spec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:38:00 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/19 15:41:03 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim_spec(char const *s, char *spec)
{
	unsigned int	start;
	unsigned int	end;

	if (s == NULL)
		return (NULL);
	if (*s == 0)
		return (ft_strdup(s));
	start = 0;
	while (s[start] && ft_instr(s[start], spec))
		start++;
	end = (unsigned int)(ft_strlen(s) - 1);
	while (end > start && ft_instr(s[end], spec))
		end--;
	return (ft_strsub(s, start, end - start + 1));
}
