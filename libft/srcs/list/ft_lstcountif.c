/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcountif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:05:41 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/18 18:04:25 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstcountif(t_list *lst, void *data_ref, int (*cmp)())
{
	int		ret;

	if (!data_ref || !cmp)
		return (-1);
	ret = 0;
	while (lst)
	{
		if (!(*cmp)(lst->content, data_ref))
			++ret;
		lst = lst->next;
	}
	return (ret);
}
