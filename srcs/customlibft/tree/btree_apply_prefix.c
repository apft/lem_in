/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:03:22 by apion             #+#    #+#             */
/*   Updated: 2019/05/02 16:46:47 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	btree_apply_prefix(t_btree *root, void (*fct)(void *))
{
	if (!root || !fct)
		return ;
	if (root->item)
		fct(root->item);
	if (root->left)
		btree_apply_prefix(root->left, fct);
	if (root->right)
		btree_apply_prefix(root->right, fct);
}
