/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customlibft.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <pion@student.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 11:59:24 by apion             #+#    #+#             */
/*   Updated: 2019/04/28 12:10:50 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOMLIBFT_H
# define CUSTOMLIBFT_H

# include <unistd.h>

typedef struct s_array_args	t_array_args;
struct	s_array_args
{
	void	*array;
	size_t	size_elmt;
	size_t	nb_elmt;
};

int		ft_nchar(char *str, char c);
ssize_t	ft_bsearch_id(void *ref, t_array_args *args, int (*cmp)());

#endif
