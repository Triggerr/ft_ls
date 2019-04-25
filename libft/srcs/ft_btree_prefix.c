/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_prefix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 18:54:44 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/09 19:01:36 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_prefix(t_btree *root, void (*f)(void *data))
{
	if (!root)
		return ;
	(*f)(root->data);
	if (root->left)
		ft_btree_prefix(root->left, f);
	if (root->right)
		ft_btree_prefix(root->right, f);
}
