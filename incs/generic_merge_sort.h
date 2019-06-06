/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_merge_sort.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:13:51 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/06 13:24:48 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERIC_MERGE_SORT_H
# define GENERIC_MERGE_SORT_H

# include "stdlib.h"

typedef struct s_array_args	t_array_args;
struct	s_array_args
{
	void	*arr;
	size_t	elmt_size;
	size_t	nb_elmt;
	int		(*cmp)();
};

typedef struct s_pos		t_pos;
struct	s_pos
{
	int	cur;
	int	left;
	int right;
};

int							array_merge_sort(t_array_args *args);

#endif
