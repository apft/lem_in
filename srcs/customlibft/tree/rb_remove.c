/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 15:39:33 by apion             #+#    #+#             */
/*   Updated: 2019/05/15 14:24:49 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_btree_rb.h"

#define ROTATE_LEFT		0x1
#define ROTATE_RIGHT	0x2

static void	rotate(t_rb_node **root, t_rb_node *n, int rotation)
{
	t_rb_node	*tmp;

	tmp = (rotation & ROTATE_LEFT) ? n->right : n->left;
	if (!n->parent)
		*root = tmp;
	else if (n == n->parent->left)
		n->parent->left = tmp;
	else
		n->parent->right = tmp;
	tmp->parent = n->parent;
	if (rotation & ROTATE_LEFT)
	{
		*n = (t_rb_node){
			tmp, n->left, tmp->left, n->data, n->color};
		tmp->left = n;
		if (n->right)
			n->right->parent = n;
	}
	else
	{
		*n = (t_rb_node){tmp, tmp->right, n->right, n->data, n->color};
		tmp->right = n;
		if (n->left)
			n->left->parent = n;
	}
}

static void	repair_tree_end_cases(t_rb_node **root, t_rb_node *n)
{
	t_rb_node *s;

	s = (n == n->parent->left) ? n->parent->right : n->parent->left;
	if (n == n->parent->left && s->left && s->left->color == RB_RED)
	{
		s->color = RB_RED;
		s->left->color = RB_BLACK;
		rotate(root, s, ROTATE_RIGHT);
	}
	else if (n == n->parent->right && s->right && s->right->color == RB_RED)
	{
		s->color = RB_RED;
		s->right->color = RB_BLACK;
		rotate(root, s, ROTATE_LEFT);
	}
	s = (n == n->parent->left) ? n->parent->right : n->parent->left;
	s->color = n->parent->color;
	n->parent->color = RB_BLACK;
	if (n == n->parent->left)
		s->right->color = RB_BLACK;
	else
		s->left->color = RB_BLACK;
	rotate(root, n->parent, n == n->parent->left ? ROTATE_LEFT : ROTATE_RIGHT);
}

static void	repair_tree(t_rb_node **root, t_rb_node *n)
{
	t_rb_node *s;

	if (!n->parent)
		return ;
	s = (n == n->parent->left) ? n->parent->right : n->parent->left;
	if (s->color == RB_RED)
	{
		n->parent->color = RB_RED;
		s->color = RB_BLACK;
		rotate(root, n->parent,
				(n == n->parent->left) ? ROTATE_LEFT : ROTATE_RIGHT);
	}
	s = (n == n->parent->left) ? n->parent->right : n->parent->left;
	if (s->color == RB_BLACK && (!s->left || s->left->color == RB_BLACK)
			&& (!s->right || s->right->color == RB_BLACK))
	{
		s->color = RB_RED;
		if (n->parent->color == RB_BLACK)
			repair_tree(root, n->parent);
		else
			n->parent->color = RB_BLACK;
	}
	else
		repair_tree_end_cases(root, n);
}

static void	remove_node_and_repair(t_rb_node **r, t_rb_node *n)
{
	t_rb_node	*child;
	t_rb_node	*sibling;

	if ((child = (n->left ? n->left : n->right)))
		n->data = child->data;
	if (!n->parent && (*r = child))
		**r = (t_rb_node){0, child->left, child->right, child->data, RB_BLACK};
	else if (n->parent)
	{
		sibling = (n == n->parent->left) ? n->parent->right : n->parent->left;
		if (n == n->parent->left)
			n->parent->left = child;
		else
			n->parent->right = child;
		if (child)
		{
			child->parent = n->parent;
			if (n->color == RB_BLACK && child->color == RB_BLACK)
				repair_tree(r, n->parent);
			else
				child->color = RB_BLACK;
		}
		else if (n->color == RB_BLACK && !sibling)
			repair_tree(r, n->parent);
	}
}

void		rb_remove(t_rb_node **root, void *data, int (*cmpf)(void *, void*),
						void (*freef)(void *))
{
	t_rb_node	*node;
	t_rb_node	*child;
	int			result;

	if (!root || !cmpf)
		return ;
	node = *root;
	while (node && (result = cmpf(data, node->data)))
		node = result < 0 ? node->left : node->right;
	if (!node)
		return ;
	if (freef)
		freef(node->data);
	if (node->left && node->right)
	{
		child = node->right;
		while (child->left)
			child = child->left;
		node->data = child->data;
		node = child;
	}
	remove_node_and_repair(root, node);
	free(node);
}
