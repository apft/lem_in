/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_merge_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:06:34 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/14 11:11:13 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_merge_sort.h"
#include <stdlib.h>
#include "libft.h"
#include "error.h"

static void		assign(void *dst, void *src, t_array_args *a)
{
	ft_memcpy(dst, src, a->elmt_size);
}

static int		merge(t_array_args *a, int left, int mid, int right)
{
	void	*tmp_arr;
	size_t	scale;
	t_pos	p;

	scale = a->elmt_size;
	p = (t_pos){0, left, mid + 1};
	if (!(tmp_arr = (void *)ft_memalloc(a->elmt_size * (right - left + 1))))
		return (errno);
	while (p.left <= mid && p.right <= right)
	{
		if ((*(a->cmp))(a->arr + p.left * scale,
				a->arr + p.right * scale) < 0)
			assign(tmp_arr + p.cur++ * scale, a->arr + p.left++ * scale, a);
		else
			assign(tmp_arr + p.cur++ * scale, a->arr + p.right++ * scale, a);
	}
	while (p.left <= mid)
		assign(tmp_arr + (p.cur++ * scale), a->arr + (p.left++ * scale), a);
	while (p.right <= right)
		assign(tmp_arr + p.cur++ * scale, a->arr + p.right++ * scale, a);
	while (p.cur--)
		assign(a->arr + (left + p.cur) * scale, tmp_arr + p.cur * scale, a);
	free((void *)tmp_arr);
	return (SUCCESS);
}

static int		merge_sort(t_array_args *a, int left, int right)
{
	int		mid;

	if (!a || !a->arr || (left >= right))
		return (SUCCESS);
	mid = (left + right) / 2;
	return (merge_sort(a, left, mid) != SUCCESS
		|| merge_sort(a, mid + 1, right) != SUCCESS
		|| merge(a, left, mid, right) != SUCCESS);
}

int				array_merge_sort(t_array_args *a)
{
	if (merge_sort(a, 0, a->nb_elmt - 1) != SUCCESS)
		return (errno);
	return (SUCCESS);
}
