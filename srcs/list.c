/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:15:58 by apion             #+#    #+#             */
/*   Updated: 2019/04/24 16:11:10 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "ft_printf.h"

static t_list	*create_list(const char *value)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(*node));
	if (!node)
		return (0);
	node->value = value;
	node->next = 0;
	return (node);
}

int				list_add_first(t_list **head, const char *value)
{
	t_list	*node;

	if (!head)
		return (0);
	node = create_list(value);
	if (!node)
		return (0);
	node->next = *head;
	*head = node;
	return (1);
}

void			list_reverse(t_list **head)
{
	t_list	*tmp;
	t_list	*prev;

	if (!head || !*head)
		return ;
	prev = 0;
	while ((*head)->next)
	{
		tmp = (*head)->next;
		(*head)->next = prev;
		prev = (*head);
		*head = tmp;
	}
	(*head)->next = prev;
}

void			list_print(t_list *head)
{
	t_list	*node;

	list_reverse(&head);
	node = head;
	while (node)
	{
		ft_printf("%s\n", node->value);
		node = node->next;
	}
	list_reverse(&head);
}

int				list_del_all(t_list **head)
{
	t_list	*tmp;

	if (!head)
		return (0);
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->value);
		free(tmp);
	}
	return (1);
}
