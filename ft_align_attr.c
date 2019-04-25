/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_align_attr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 14:00:41 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/20 20:46:44 by bbaelor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_align		g_align;
t_column	g_column;

void	ft_setcolumn(void)
{
	int				n;
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	if (!isatty(STDOUT_FILENO))
		ws.ws_col = 80;
	g_lbuff = malloc(sizeof(char) * g_buffsize);
	n = g_align.name + 1;
	n += FL_LS ? g_align.block : 0;
	g_column.columns = (ws.ws_col / n);
	if (g_column.columns == 0)
		g_column.columns = 1;
	g_column.pos = -1;
	g_column.optlen = n +
					(ws.ws_col - g_column.columns * n) /
					g_column.columns;
	g_buffsize = ws.ws_col + g_column.columns * (FL_UG ? 22 : 0);
}

void	ft_setattr(t_file *file, int is_arg)
{
	if (FL_UL || (FL_UH && is_arg))
		stat(file->path, &file->stats);
	else
		lstat(file->path, &file->stats);
	file->namelen = ft_namelen(file->name);
	if (FL_UF && (((file->stats.st_mode & S_IFMT) == S_IFDIR) ||
		(((file->stats.st_mode & S_IFMT) == S_IFREG) &&
		(file->stats.st_mode & S_IXUSR ||
		file->stats.st_mode & S_IXGRP ||
		file->stats.st_mode & S_IXOTH)) ||
		((file->stats.st_mode & S_IFMT) == S_IFLNK) ||
		((file->stats.st_mode & S_IFMT) == S_IFSOCK) ||
		((file->stats.st_mode & S_IFMT) == S_IFWHT) ||
		((file->stats.st_mode & S_IFMT) == S_IFIFO)))
		file->namelen++;
	if (FL_LS)
		file->blklen = ft_numlen(file->stats.st_blocks, 10);
	if (!FL_LONG)
		return ;
	file->uidlen = ft_uidlen(file->stats.st_uid);
	file->gidlen = ft_gidlen(file->stats.st_gid);
	file->linklen = ft_numlen(file->stats.st_nlink, 10);
	file->dev1len = ft_devlen(file, 1);
	file->dev2len = ft_devlen(file, 0);
	file->sizelen = ft_sizelen(file);
}

void	ft_set_alignl(t_file *file)
{
	if (file->linklen > g_align.links)
		g_align.links = file->linklen;
	if (file->uidlen > g_align.user)
		g_align.user = file->uidlen;
	if (file->gidlen > g_align.group)
		g_align.group = file->gidlen;
	if (file->sizelen > g_align.size)
		g_align.size = file->sizelen;
	if (file->dev1len > g_align.dev1)
		g_align.dev1 = file->dev1len;
	if (file->dev2len > g_align.dev2)
		g_align.dev2 = file->dev2len;
	if (!g_align.is_cb && (((file->stats.st_mode & S_IFMT) == S_IFCHR) ||
							((file->stats.st_mode & S_IFMT) == S_IFBLK)))
		g_align.is_cb++;
}

void	ft_set_align(void *data)
{
	if (((t_file *)data)->namelen > g_align.name)
		g_align.name = ((t_file *)data)->namelen;
	if (FL_LS && ((t_file *)data)->blklen > g_align.block)
		g_align.block = ((t_file *)data)->blklen;
	if (FL_LONG || FL_LS)
		g_align.blocks += ((t_file *)data)->stats.st_blocks;
	if (FL_LONG)
		ft_set_alignl((t_file *)data);
}
