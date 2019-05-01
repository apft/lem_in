/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customlibft.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <pion@student.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 11:59:24 by apion             #+#    #+#             */
/*   Updated: 2019/05/01 10:05:21 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOMLIBFT_H
# define CUSTOMLIBFT_H

# include <unistd.h>

int		ft_nchar(char *str, char c);

typedef struct s_array_args	t_array_args;
struct	s_array_args
{
	void	*array;
	size_t	size_elmt;
	size_t	nb_elmt;
};

ssize_t	ft_bsearch_id(void *ref, t_array_args *args, int (*cmp)());

typedef struct s_queue	t_queue;
struct	s_queue
{
	t_list	*head;
	t_list	*tail;
};

void	enqueue(t_queue *queue, void *content);
void	*dequeue(t_queue *queue);

typedef struct s_bfs	t_bfs;
struct	s_bfs
{
	t_list			*list_elmt;
	t_array_args	*array_args;
	void			*source;
	void			*target;
};

#endif
