/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfindlast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:57:47 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/09 12:17:51 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstfindlast(t_list *lst, void *data_ref, int (*cmp)())
{
	t_list	*last;

	last = NULL;
	while (lst)
	{
		if (!(*cmp)(lst->content, data_ref))
			last = lst;
		lst = lst->next;
	}
	return (last);
}
