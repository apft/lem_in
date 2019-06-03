/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_merge_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:06:34 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/03 17:15:03 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_merge_sort.h"
#include <stdlib.h>
#include "libft.h"
#include "error.h"

typedef struct s_pos t_pos;
struct	s_pos
{
	int	cur;
	int	left;
	int right;
};

static void	assign(void *dst, void *src, t_array_args *args)
{
	ft_memcpy(dst, src, args->elmt_size);
}

static int	merge(t_array_args *args, int left, int mid, int right)
{
	void	*tmp_arr;
	size_t	scale;
	t_pos	p;

	scale = args->elmt_size;
	p = (t_pos){0, left, mid + 1};
	if (!(tmp_arr = (void *)ft_memalloc(args->elmt_size * (right - left + 1))))
		return (errno);
	while (p.left <= mid && p.right <= right)
	{
		if ((*(args->cmp))(args->arr + p.left * scale,
					args->arr + p.right * scale) < 0)
			assign(tmp_arr + p.cur++ * scale, args->arr + p.left++ * scale, args);
		else
			assign(tmp_arr + p.cur++ * scale, args->arr + p.right++ * scale, args);
	}
	while (p.left <= mid)
		assign(tmp_arr + (p.cur++ * scale), args->arr + (p.left++ * scale), args);
	while (p.right <= right)
		assign(tmp_arr + p.cur++ * scale, args->arr + p.right++ * scale, args);
	while (p.cur--)
		assign(args->arr + (left + p.cur) * scale, tmp_arr + p.cur * scale, args);
	free((void *)tmp_arr);
	return (SUCCESS);
}

static int	merge_sort(t_array_args *args, int left, int right)
{
	int		mid;

	if (!args || !args->arr || (left >= right))
		return (SUCCESS);
	mid = (left + right) / 2;
	return (merge_sort(args, left, mid) != SUCCESS
			|| merge_sort(args, mid + 1, right) != SUCCESS
			|| merge(args, left, mid, right) != SUCCESS);
}

int			array_merge_sort(t_array_args *args)
{
	if (merge_sort(args, 0, args->nb_elmt - 1) != SUCCESS)
		return (errno);
	return (SUCCESS);
}
