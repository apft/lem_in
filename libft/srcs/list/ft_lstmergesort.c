/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmergesort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:01:09 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/12 12:58:23 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*sorted_merge(t_list *front, t_list *back, int (*cmp)())
{
	t_list		*res;

	if (!front)
		return (back);
	if (!back)
		return (front);
	if ((*cmp)(front->content, back->content) <= 0)
	{
		res = front;
		res->next = sorted_merge(front->next, back, cmp);
	}
	else
	{
		res = back;
		res->next = sorted_merge(front, back->next, cmp);
	}
	return (res);
}

t_list			*ft_lstmergesort(t_list **lst, int (*cmp)())
{
	t_list		*front;
	t_list		*back;

	if (!cmp || !lst || !*lst || !(*lst)->next)
		return (NULL);
	ft_lstsplithalf(*lst, &front, &back);
	ft_lstmergesort(&front, cmp);
	ft_lstmergesort(&back, cmp);
	*lst = sorted_merge(front, back, cmp);
	return (*lst);
}
