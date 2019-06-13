/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttostrarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:40:15 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/25 15:49:20 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lsttostrarray(t_list *lst, char ***array, char *(*f)())
{
	int		array_size;
	int		i;

	if (!lst || !array || !f)
		return (-1);
	array_size = ft_lstsize(lst);
	if (!(*array = (char **)ft_memalloc(sizeof(**array) * array_size)))
		return (-1);
	i = 0;
	while (lst)
	{
		(*array)[i++] = (*f)(lst);
		lst = lst->next;
	}
	return (i);
}
