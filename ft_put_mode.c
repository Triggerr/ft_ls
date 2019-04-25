/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 19:54:40 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 19:54:42 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_get_perm(mode_t st_mode, t_file *file)
{
	g_lbufp[1] = (st_mode & S_IRUSR) ? 'r' : '-';
	g_lbufp[2] = (st_mode & S_IWUSR) ? 'w' : '-';
	g_lbufp[3] = (st_mode & S_IXUSR) ? 'x' : '-';
	if (st_mode & S_ISUID)
		g_lbufp[3] = (st_mode & S_IXUSR) ? 's' : 'S';
	g_lbufp[4] = (st_mode & S_IRGRP) ? 'r' : '-';
	g_lbufp[5] = (st_mode & S_IWGRP) ? 'w' : '-';
	g_lbufp[6] = (st_mode & S_IXGRP) ? 'x' : '-';
	if (st_mode & S_ISGID)
		g_lbufp[6] = (st_mode & S_IXGRP) ? 's' : 'S';
	g_lbufp[7] = (st_mode & S_IROTH) ? 'r' : '-';
	g_lbufp[8] = (st_mode & S_IWOTH) ? 'w' : '-';
	g_lbufp[9] = (st_mode & S_IXOTH) ? 'x' : '-';
	if (st_mode & S_ISVTX)
		g_lbufp[9] = (st_mode & S_ISVTX) ? 't' : 'T';
	g_lbufp[10] = listxattr(file->path, 0, 0, XATTR_NOFOLLOW) > 0 ? '@' : ' ';
	g_lbufp[10] = listxattr(file->path, 0, 0, XATTR_NOFOLLOW) > 0 ? '@' : ' ';
}

int		ft_put_mode(t_file *file)
{
	mode_t	mode;

	mode = file->stats.st_mode & S_IFMT;
	if (mode == S_IFREG)
		g_lbufp[0] = '-';
	else if (mode == S_IFDIR)
		g_lbufp[0] = 'd';
	else if (mode == S_IFLNK)
		g_lbufp[0] = 'l';
	else if (mode == S_IFCHR)
		g_lbufp[0] = 'c';
	else if (mode == S_IFBLK)
		g_lbufp[0] = 'b';
	else if (mode == S_IFSOCK)
		g_lbufp[0] = 's';
	else if (mode == S_IFWHT)
		g_lbufp[0] = 's';
	else
		g_lbufp[0] = '-';
	ft_get_perm(file->stats.st_mode, file);
	g_lbufp += 12;
	return (g_lbufp[-2] == '@' ? '@' : 0);
}
