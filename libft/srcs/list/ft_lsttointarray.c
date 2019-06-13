/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttointarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:18:21 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/17 16:44:52 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lsttointarray(t_list *lst, int **array, int (*f)())
{
	int		array_size;
	int		i;

	if (!lst || !array || !f)
		return (-1);
	array_size = ft_lstsize(lst);
	if (!(*array = (int *)ft_memalloc(sizeof(**array) * array_size)))
		return (-1);
	i = 0;
	while (lst)
	{
		(*array)[i++] = (*f)(lst);
		lst = lst->next;
	}
	return (i);
}
