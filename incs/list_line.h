/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:58:24 by apion             #+#    #+#             */
/*   Updated: 2019/04/24 17:41:42 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_list_line	t_list_line;

struct	s_list_line
{
	char		*line;
	t_list_line	*next;
};

void	print_lines(t_list_line *head);

int		list_line_add_first(t_list_line **head, const char *line);
int		list_line_del_all(t_list_line **head);
void	reverse_list_line(t_list_line **head);

#endif
