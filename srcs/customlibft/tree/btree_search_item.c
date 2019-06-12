/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:49:53 by apion             #+#    #+#             */
/*   Updated: 2019/06/10 20:26:42 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree_rb.h"

void	*btree_search_item(t_rb_node *root, void *data_ref, int (*cmp)())
{
	int		result;

	if (!root || !cmp)
		return (0);
	result = cmp(data_ref, root->data);
	if (result < 0)
		return (btree_search_item(root->left, data_ref, cmp));
	else if (result > 0)
		return (btree_search_item(root->right, data_ref, cmp));
	else
		return (root->data);
}
