/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 12:11:55 by apion             #+#    #+#             */
/*   Updated: 2019/06/14 11:22:59 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_btree_rb.h"
#include "error.h"

#define ROTATE_LEFT		0x1
#define ROTATE_RIGHT	0x2

static void		rotate(t_rb_node **root, t_rb_node *n, int rotation)
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
		*n = (t_rb_node){tmp, n->left, tmp->left, n->data, n->color};
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

static void		repair_tree_red_parent_black_uncle(t_rb_node **root,
						t_rb_node *node)
{
	t_rb_node	*parent;

	parent = node->parent;
	if (node == node->parent->right && parent == parent->parent->left)
	{
		rotate(root, parent, ROTATE_LEFT);
		node = node->left;
	}
	else if (node == node->parent->left && parent == parent->parent->right)
	{
		rotate(root, parent, ROTATE_RIGHT);
		node = node->right;
	}
	parent = node->parent;
	parent->color = rb_black;
	parent->parent->color = rb_red;
	if (node == parent->left)
		rotate(root, parent->parent, ROTATE_RIGHT);
	else
		rotate(root, parent->parent, ROTATE_LEFT);
}

static void		repair_tree(t_rb_node **root, t_rb_node *node)
{
	t_rb_node	*p;
	t_rb_node	*u;

	if (!(p = node->parent))
		node->color = rb_black;
	else if (p->color == rb_black)
		return ;
	else if ((u = (p == p->parent->left) ? p->parent->right : p->parent->left)
		&& u->color == rb_red)
	{
		p->color = rb_black;
		u->color = rb_black;
		p->parent->color = rb_red;
		repair_tree(root, p->parent);
	}
	else
		repair_tree_red_parent_black_uncle(root, node);
}

static void		insert_tree(t_rb_node *tree, t_rb_node *node,
						int (*cmp)(void *, void *))
{
	while (tree)
	{
		if (cmp(node->data, tree->data) < 0)
		{
			if (!tree->left)
			{
				tree->left = node;
				break ;
			}
			tree = tree->left;
		}
		else
		{
			if (!tree->right)
			{
				tree->right = node;
				break ;
			}
			tree = tree->right;
		}
	}
	node->parent = tree;
}

int				rb_insert(t_rb_node **root, void *data,
						int (*cmp)(void *, void *))
{
	t_rb_node	*node;

	if (!root || !cmp)
		return (err_null_pointer);
	node = (t_rb_node *)malloc(sizeof(*node));
	if (!node)
		return (errno);
	*node = (t_rb_node){0, 0, 0, data, rb_red};
	if (!*root)
		*root = node;
	else
		insert_tree(*root, node, cmp);
	repair_tree(root, node);
	return (SUCCESS);
}
