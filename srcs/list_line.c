/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:15:58 by apion             #+#    #+#             */
/*   Updated: 2019/06/06 16:43:41 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list_line.h"
#include "ft_printf.h"
#include "error.h"

static t_list_line	*create_list_line(char *line)
{
	t_list_line	*node;

	node = (t_list_line *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->line = line;
	node->next = 0;
	return (node);
}

int					list_line_add_first(t_list_line **head, char *line)
{
	t_list_line	*node;

	if (!head)
		return (err_null_pointer);
	node = create_list_line(line);
	if (!node)
		return (errno);
	node->next = *head;
	*head = node;
	return (SUCCESS);
}

void				reverse_list_line(t_list_line **head)
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

void				print_lines(t_list_line *head)
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

int					list_line_del_all(t_list_line **head)
{
	t_list_line	*tmp;

	if (!head)
		return (err_null_pointer);
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->line);
		free(tmp);
	}
	return (SUCCESS);
}
