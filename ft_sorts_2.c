/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorts_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:58:20 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 19:51:48 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_sort_by_size(void *a, void *b)
{
	int	cmp;

	cmp = ((t_file *)b)->stats.st_size - ((t_file *)a)->stats.st_size;
	if (cmp)
		return (FL_LR ? -cmp : cmp);
	else
		return (g_sorts[0](a, b));
}

int		ft_sort_by_nothing(void *a, void *b)
{
	a = 0;
	b = 0;
	return (0);
}
