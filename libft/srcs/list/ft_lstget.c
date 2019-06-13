/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:32:17 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/18 11:13:45 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstget(t_list *lst, void *ret, void (*f)(void *, void *))
{
	if (!lst || !ret || !f)
		return ;
	while (lst)
	{
		(*f)(lst->content, ret);
		lst = lst->next;
	}
}
