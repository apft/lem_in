/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:06:34 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/26 22:10:26 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "room.h"
#include "error.h"
#include "libft.h"

static int	cmp_room_name(t_room *room1, t_room *room2)
{
	return (ft_strcmp(room1->name, room2->name));
}

static int	merge(t_room **array, int left, int mid, int right)
{
	t_room	**tmp_array;
	int		pos;
	int		lpos;
	int		rpos;

	pos = 0;
	lpos = left;
	rpos = mid + 1;
	tmp_array = (t_room **)malloc(sizeof(t_room *) * (right - left + 1));
	if (!tmp_array)
		return (errno);
	while (lpos <= mid && rpos <= right)
	{
		if (cmp_room_name(array[lpos], array[rpos]) < 0)
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
	return (merge_sort(array, 0, array_size - 1));
}
