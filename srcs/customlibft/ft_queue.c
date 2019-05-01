/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 21:36:32 by apion             #+#    #+#             */
/*   Updated: 2019/05/01 08:40:49 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "customlibft.h"

/*
** Not using ft_lstnew because I only need a queue of pointer, no need to memcpy
*/

void	enqueue(t_queue *queue, void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return ;
	node->content = content;
	node->content_size = 0;
	node->next = 0;
	if (!queue->head)
		queue->head = node;
	if (queue->tail)
		queue->tail->next = node;
	queue->tail = node;
}

void	*dequeue(t_queue *queue)
{
	t_list	*node;
	void	*content;

	if (!queue || !queue->head)
		return (0);
	node = queue->head;
	queue->head = queue->head->next;
	if (!queue->head)
		queue->tail = 0;
	content = node->content;
	free(node);
	return (content);
}
