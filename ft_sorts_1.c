/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorts_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:22:51 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/20 20:46:26 by bbaelor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** name		--	standart sort
** time		-t	sort by time modified (most recently modified first)
** create	-U	use time of file creation
** change	-c	use time when file status was last changed
** access	-u	use time of last access
*/

int	ft_sort_by_name(void *a, void *b)
{
	return (FL_LR ? -ft_strcmp(((t_file *)a)->name, ((t_file *)b)->name) :
						ft_strcmp(((t_file *)a)->name, ((t_file *)b)->name));
}

int	ft_sort_by_time(void *a, void *b)
{
	int	cmp;

	cmp = ((t_file *)b)->stats.st_mtimespec.tv_sec -
			((t_file *)a)->stats.st_mtimespec.tv_sec;
	if (cmp)
		return (FL_LR ? -cmp : cmp);
	else
		return (g_sorts[0](a, b));
}

#ifdef _DARWIN_FEATURE_64_BIT_INODE

int	ft_sort_by_create(void *a, void *b)
{
	int	cmp;

	cmp = ((t_file *)b)->stats.st_birthtimespec.tv_sec -
			((t_file *)a)->stats.st_birthtimespec.tv_sec;
	if (cmp)
		return (FL_LR ? -cmp : cmp);
	else
		return (g_sorts[0](a, b));
}

#endif

int	ft_sort_by_change(void *a, void *b)
{
	int	cmp;

	cmp = ((t_file *)b)->stats.st_ctimespec.tv_sec -
			((t_file *)a)->stats.st_ctimespec.tv_sec;
	if (cmp)
		return (FL_LR ? -cmp : cmp);
	else
		return (g_sorts[0](a, b));
}

int	ft_sort_by_access(void *a, void *b)
{
	int	cmp;

	cmp = ((t_file *)b)->stats.st_atimespec.tv_sec -
			((t_file *)a)->stats.st_atimespec.tv_sec;
	if (cmp)
		return (FL_LR ? -cmp : cmp);
	else
		return (g_sorts[0](a, b));
}
