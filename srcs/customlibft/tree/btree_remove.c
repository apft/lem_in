/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:15:06 by apion             #+#    #+#             */
/*   Updated: 2019/05/13 12:27:54 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_btree.h"

static void	remove_node_two_children(t_btree **root, t_btree **node)
{
	t_btree	*inorder_successor;

	inorder_successor = (*node)->right;
	while (inorder_successor->left)
		inorder_successor = inorder_successor->left;
	(*node)->item = inorder_successor->item;
	*node = inorder_successor;
}

static void	remove_leaf(t_btree **root, t_btree *node)
{
	if (!node->parent)
		*root = 0;
	else
	{
		if (node == node->parent->left)
			node->parent->left = 0;
		else
			node->parent->right = 0;
	}
}

static void	remove_node_one_child(t_btree **root, t_btree *node)
{
	t_btree	*child;

	child = node->left ? node->left : node->right;
	node->item = child->item;
	if (node == node->parent->left)
		node->parent->left = child;
	else
		node->parent->right = child;
}

void		btree_remove(t_btree **root, void *item,
				int (*cmpf)(void *, void *), void (*freef)(void *))
{
	t_btree	*node;
	int		result;

	if (!root || !cmpf)
		return ;
	node = *root;
	while (node && (result = cmpf(item, node->item)))
		node = result < 0 ? node->left : node->right;
	if (!node)
		return ;
	if (freef)
		freef(node->item);
	if (node->left && node->right)
		remove_node_two_children(root, *node);
	if (!node->left && !node->right)
		remove_leaf(root, node);
	else
		remove_node_one_child(root, node);
	free(node);
}
