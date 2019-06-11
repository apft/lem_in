/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:06:34 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/11 18:08:23 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "room.h"
#include "error.h"
#include "libft.h"

static int	merge(t_room **array, int left, int mid, int right)
{
	t_room	**tmp_array;
	int		pos;
	int		lpos;
	int		rpos;

	pos = 0;
	lpos = left;
	rpos = mid + 1;
	if (!(tmp_array = (t_room **)malloc(sizeof(t_room *) * (right - left + 1))))
		return (errno);
	while (lpos <= mid && rpos <= right)
	{
		if (is_room_name_equal(array[lpos], array[rpos]) < 0)
			tmp_array[pos++] = array[lpos++];
		else
			tmp_array[pos++] = array[rpos++];
	}
	while (lpos <= mid)
		tmp_array[pos++] = array[lpos++];
	while (rpos <= right)
		tmp_array[pos++] = array[rpos++];
	while (pos--)
		array[left + pos] = tmp_array[pos];
	free((void **)tmp_array);
	return (SUCCESS);
}

static int	merge_sort(t_room **array, int left, int right)
{
	int		mid;

	if (!array || (left >= right))
		return (SUCCESS);
	mid = (left + right) / 2;
	return (merge_sort(array, left, mid) != SUCCESS
			|| merge_sort(array, mid + 1, right) != SUCCESS
			|| merge(array, left, mid, right) != SUCCESS);
}

int			array_room_merge_sort(t_room **array, size_t array_size)
{
	if (merge_sort(array, 0, array_size - 1) != SUCCESS)
		return (errno);
	while (array_size--)
		array[array_size]->id = array_size;
	return (SUCCESS);
}
