/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_rb.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:26:28 by apion             #+#    #+#             */
/*   Updated: 2019/06/13 12:32:17 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_RB_H
# define FT_BTREE_RB_H

enum	e_rb_color
{
	RB_BLACK,
	RB_RED
};

typedef struct s_rb_node	t_rb_node;
struct	s_rb_node
{
	t_rb_node		*parent;
	t_rb_node		*left;
	t_rb_node		*right;
	void			*data;
	enum e_rb_color	color;
};

void	rb_insert(t_rb_node **root, void *data, int (*cmp)(void *, void *));
void	btree_apply_infix(t_rb_node *root, void *data, void (*fct)());
void	btree_apply_suffix(t_rb_node *root, void *data, void (*fct)());
void	*btree_search_item(t_rb_node *root, void *data_ref, int (*cmp)());

#endif
