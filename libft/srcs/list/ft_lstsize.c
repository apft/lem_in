/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:20:04 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/17 16:27:07 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cmp(void *content, void *data_ref)
{
	(void)content;
	(void)data_ref;
	return (0);
}

int			ft_lstsize(t_list *lst)
{
	int		ret;

	ret = ft_lstcountif(lst, "", &cmp);
	return (ret);
}
