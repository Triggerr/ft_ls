/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_suffix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:33:57 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/09 19:36:26 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_suffix(t_btree *root, void (*f)(void *data))
{
	if (!root)
		return ;
	if (root->left)
		ft_btree_suffix(root->left, f);
	if (root->right)
		ft_btree_suffix(root->right, f);
	(*f)(root->data);
}
