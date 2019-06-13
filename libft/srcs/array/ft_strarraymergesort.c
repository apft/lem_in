/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarraymergesort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:00:19 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/25 16:15:06 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	merge(char **array, int left, int mid, int right)
{
	char	**tmp_array;
	int		pos;
	int		lpos;
	int		rpos;

	pos = 0;
	lpos = left;
	rpos = mid + 1;
	tmp_array = (char **)ft_memalloc(sizeof(char *) * (right - left + 1));
	if (!tmp_array)
		return ;
	while (lpos <= mid && rpos <= right)
	{
		if (ft_strcmp(array[lpos], array[rpos]) < 0)
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
	ft_memdel((void **)&tmp_array);
}

void		merge_sort(char **array, int left, int right)
{
	int		mid;

	if (!array || (left >= right))
		return ;
	mid = (left + right) / 2;
	merge_sort(array, left, mid);
	merge_sort(array, mid + 1, right);
	merge(array, left, mid, right);
}

void		ft_strarraymergesort(char **array, size_t array_size)
{
	merge_sort(array, 0, array_size - 1);
}
