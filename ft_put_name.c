/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 19:49:14 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 19:50:18 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_put_fsuffix(t_file *file)
{
	if (((file->stats.st_mode & S_IFMT) == S_IFDIR))
		*g_lbufp++ = '/';
	if (((file->stats.st_mode & S_IFMT) == S_IFREG) &&
		(file->stats.st_mode & S_IXUSR ||
		file->stats.st_mode & S_IXGRP ||
		file->stats.st_mode & S_IXOTH))
		*g_lbufp++ = '*';
	if (((file->stats.st_mode & S_IFMT) == S_IFLNK))
		*g_lbufp++ = '@';
	if (((file->stats.st_mode & S_IFMT) == S_IFSOCK))
		*g_lbufp++ = '=';
	if (((file->stats.st_mode & S_IFMT) == S_IFWHT))
		*g_lbufp++ = '%';
	if (((file->stats.st_mode & S_IFMT) == S_IFIFO))
		*g_lbufp++ = '|';
}

static int	ft_put_nograph(unsigned char c)
{
	char	*esc;

	esc = "abtnvfr";
	if (FL_G2 == 3)
	{
		*g_lbufp++ = '?';
		return (ft_charsize(c));
	}
	*g_lbufp++ = '\\';
	if (FL_G2 == 2 && ((c >= 0x7 && c <= 0xD) || c == '\\' || c == '\"'))
		*g_lbufp++ = ((c == '\\' || c == '\"') ? c : esc[c - 0x7]);
	else if (FL_G2 == 1 || FL_G2 == 2)
	{
		ft_strnum_base(g_lbufp, (int)c, 8);
		g_lbufp += ft_numlen((int)c, 8);
	}
	return (1);
}

int			ft_force_name(t_file *file)
{
	char	*name;

	name = file->name;
	if (FL_G2 == 4 || !FL_G2)
	{
		g_lbufp += ft_strcpy(g_lbufp, name);
	}
	else
		while (*name)
		{
			if (ft_isgraph(*name) && ((*name != '\\' && *name != '\"') ||
										FL_G2 == 3))
				*g_lbufp++ = *name++;
			else
				name += ft_put_nograph(*(unsigned char *)name);
		}
	if (FL_UG)
		ft_strcolor((g_lbufp += 11) - 11, 0, 0, 0);
	if (FL_UF)
		ft_put_fsuffix(file);
	return (0);
}

static void	ft_set_other_color(t_file *file, mode_t mode)
{
	if ((mode == S_IFREG) &&
			(file->stats.st_mode & S_ISUID) &&
			(file->stats.st_mode & S_IXUSR ||
			file->stats.st_mode & S_IXGRP ||
			file->stats.st_mode & S_IXOTH))
		ft_strcolor((g_lbufp += 11) - 11, COLOR_BLACK, BACKG_RED, 0);
	else if ((mode == S_IFREG) &&
			(file->stats.st_mode & S_ISGID) &&
			(file->stats.st_mode & S_IXUSR ||
			file->stats.st_mode & S_IXGRP ||
			file->stats.st_mode & S_IXOTH))
		ft_strcolor((g_lbufp += 11) - 11, COLOR_BLACK, BACKG_CYAN, 0);
	else if ((mode == S_IFREG) &&
			(file->stats.st_mode & S_IXUSR ||
			file->stats.st_mode & S_IXGRP ||
			file->stats.st_mode & S_IXOTH))
		ft_strcolor((g_lbufp += 11) - 11, COLOR_RED, 0, 0);
	else if (mode == S_IFBLK)
		ft_strcolor((g_lbufp += 11) - 11, COLOR_BLUE, BACKG_CYAN, 0);
	else if (mode == S_IFCHR)
		ft_strcolor((g_lbufp += 11) - 11, COLOR_BLUE, BACKG_YELLOW, 0);
}

int			ft_put_name(t_file *file)
{
	mode_t	mode;

	mode = file->stats.st_mode & S_IFMT;
	if (!FL_UG)
		return (ft_force_name(file));
	if (mode == S_IFDIR && (file->stats.st_mode & S_IWOTH) &&
							(file->stats.st_mode & S_ISVTX))
		ft_strcolor((g_lbufp += 11) - 11, COLOR_BLACK, BACKG_GREEN, 0);
	else if (mode == S_IFDIR && (file->stats.st_mode & S_IWOTH))
		ft_strcolor((g_lbufp += 11) - 11, COLOR_BLACK, BACKG_YELLOW, 0);
	else if (mode == S_IFDIR)
		ft_strcolor((g_lbufp += 11) - 11, COLOR_CYAN, STYLE_BOLD, 0);
	else if (mode == S_IFLNK)
		ft_strcolor((g_lbufp += 11) - 11, COLOR_MAGENTA, 0, 0);
	else if (mode == S_IFSOCK)
		ft_strcolor((g_lbufp += 11) - 11, COLOR_GREEN, 0, 0);
	else if (mode == S_IFIFO)
		ft_strcolor((g_lbufp += 11) - 11, COLOR_YELLOW, 0, 0);
	else
		ft_set_other_color(file, mode);
	ft_force_name(file);
	return (0);
}
