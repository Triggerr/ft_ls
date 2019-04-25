/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:26:19 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 19:56:26 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_func_array.h"

/*
** --	0
** -t	1
** -U	2
** -c	3
** -u	4
*/

int		(*g_sorts[7])(void *, void *) = {
	&ft_sort_by_name,
	&ft_sort_by_time,
#ifdef _DARWIN_FEATURE_64_BIT_INODE

	&ft_sort_by_create,
#endif
#ifndef _DARWIN_FEATURE_64_BIT_INODE

	&ft_sort_by_time,
#endif

	&ft_sort_by_change,
	&ft_sort_by_access,
	&ft_sort_by_size,
	&ft_sort_by_nothing
};

void		(*g_print[6])(void *) = {
	&ft_print_newline,
	&ft_print_newline,
	&ft_print_long,
	&ft_print_lines,
	&ft_print_newline,
	&ft_print_long,
};
