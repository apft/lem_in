/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstissorted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:18:18 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/02 14:25:49 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstissorted(t_list *lst, int (*f)())
{
	if (!lst || !lst->next)
		return (1);
	while (lst->next)
	{
		if (!(*f)(lst->content, lst->next->content))
			return (0);
		lst = lst->next;
	}
	return (1);
}
