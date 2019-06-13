/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 21:36:32 by apion             #+#    #+#             */
/*   Updated: 2019/06/13 18:29:01 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "customlibft.h"
#include "error.h"

static void	*create_node(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return ((void *)0);
	node->content = content;
	node->content_size = 0;
	node->next = 0;
	return (node);
}

int			prequeue(t_queue *queue, void *content)
{
	t_list *node;

	node = create_node(content);
	if (!node)
		return (errno);
	node->next = queue->head;
	queue->head = node;
	if (!queue->tail)
		queue->tail = node;
	return (SUCCESS);
}

int			enqueue(t_queue *queue, void *content)
{
	t_list	*node;

	node = create_node(content);
	if (!node)
		return (errno);
	if (!queue->head)
		queue->head = node;
	if (queue->tail)
		queue->tail->next = node;
	queue->tail = node;
	return (SUCCESS);
}

void		*dequeue(t_queue *queue)
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
