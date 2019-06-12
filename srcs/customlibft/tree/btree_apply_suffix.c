/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:13:49 by apion             #+#    #+#             */
/*   Updated: 2019/06/10 21:03:27 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree_rb.h"

void	btree_apply_suffix(t_rb_node *root, void *data, void (*fct)())
{
	if (!root || !fct)
		return ;
	if (root->left)
		btree_apply_suffix(root->left, data, fct);
	if (root->right)
		btree_apply_suffix(root->right, data, fct);
	if (data)
		fct(root, data);
	else
		fct(root);
}
