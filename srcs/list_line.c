/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:15:58 by apion             #+#    #+#             */
/*   Updated: 2019/04/24 17:38:48 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"
#include "ft_printf.h"

static t_list_line	*create_list_line(const char *line)
{
	t_list_line	*node;

	node = (t_list_line *)malloc(sizeof(*node));
	if (!node)
		return (0);
	node->line = line;
	node->next = 0;
	return (node);
}

int				list_line_add_first(t_list_line **head, const char *line)
{
	t_list_line	*node;

	if (!head)
		return (0);
	node = create_line(line);
	if (!node)
		return (0);
	node->next = *head;
	*head = node;
	return (1);
}

void			reverse_list_line(t_list_line **head)
{
	t_list_line	*tmp;
	t_list_line	*prev;

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

void			print_lines(t_list_line *head)
{
	t_list_line	*node;

	reverse_list_line(&head);
	node = head;
	while (node)
	{
		ft_printf("%s\n", node->line);
		node = node->next;
	}
	reverse_list_line(&head);
}

int				list_line_del_all(t_list_line **head)
{
	t_list_line	*tmp;

	if (!head)
		return (0);
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->line);
		free(tmp);
	}
	return (1);
}
