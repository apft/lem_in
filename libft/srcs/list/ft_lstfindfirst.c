/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfindfirst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:43:27 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/09 11:48:58 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstfindfirst(t_list *lst, void *data_ref, int (*cmp)())
{
	while (lst)
	{
		if (!(*cmp)(lst->content, data_ref))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
