/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmedian.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:29:02 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/18 14:12:26 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			ft_lstmedian(t_list *lst, int (*f)(), int *median)
{
	int		*array;
	int		size;

	if (!lst || !median || (size = ft_lstsize(lst)) < 0)
		return (-1);
	if (ft_lsttointarray(lst, &array, f) < 0)
		return (-1);
	ft_arraymergesort(array, size);
	*median = array[size / 2];
	ft_memdel((void **)&array);
	return (0);
}
