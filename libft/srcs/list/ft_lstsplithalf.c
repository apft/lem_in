/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplithalf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:22:32 by jkettani          #+#    #+#             */
/*   Updated: 2019/03/31 16:38:14 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstsplithalf(t_list *lst, t_list **front, t_list **back)
{
	t_list	*slow;
	t_list	*fast;

	if (!lst)
		return ;
	slow = lst;
	fast = lst->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = lst;
	*back = slow->next;
	slow->next = NULL;
}
