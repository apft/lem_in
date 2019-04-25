/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 21:06:48 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/12 11:46:48 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem),
			void (*del)(void *, size_t))
{
	t_list	*lst2;
	t_list	*lst2_head;

	if (!lst || !f || !del)
		return (NULL);
	if (!(lst2 = (*f)(lst)))
		return (NULL);
	lst2_head = lst2;
	lst = lst->next;
	while (lst)
	{
		if (!(lst2->next = (*f)(lst)))
		{
			ft_lstdel(&lst2_head, del);
			return (NULL);
		}
		lst = lst->next;
		lst2 = lst2->next;
	}
	lst2->next = NULL;
	return (lst2_head);
}
