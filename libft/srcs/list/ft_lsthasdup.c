/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsthasdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:04:39 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/18 16:18:52 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*elm_cpy(t_list *elm)
{
	return (ft_lstnew(elm->content, elm->content_size));
}

int				ft_lsthasdup(t_list **lst, int (*cmp)(),
					void (*del)(void *, size_t))
{
	t_list	*lst_cpy;
	t_list	*lst_cpy_head;
	int		ret;

	if (!lst || !*lst || !(*lst)->next)
		return (0);
	if (!(lst_cpy_head = ft_lstmap(*lst, &elm_cpy, del)))
		return (-1);
	ft_lstmergesort(&lst_cpy_head, cmp);
	ret = 0;
	lst_cpy = lst_cpy_head;
	while (lst_cpy->next)
	{
		if (!(*cmp)(lst_cpy->content, lst_cpy->next->content))
		{
			ret = 1;
			break ;
		}
		lst_cpy = lst_cpy->next;
	}
	ft_lstdel(&lst_cpy_head, del);
	return (ret);
}
