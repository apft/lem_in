/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:58:24 by apion             #+#    #+#             */
/*   Updated: 2019/04/24 16:12:11 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_list	t_list;

struct	s_list
{
	char	*value;
	t_list	*next;
};

void	list_print(t_list *head);

int		list_add_first(t_list **head, const char *value);
int		list_del_all(t_list **head);
void	list_reverse(t_list **head);

#endif
