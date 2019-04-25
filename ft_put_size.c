/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 15:18:06 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/20 20:46:27 by bbaelor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_sizelen(t_file *file)
{
	long	delim;

	if (!FL_LH)
		return (ft_numlen(file->stats.st_size, 10));
	delim = 1099511627776L;
	while (!(file->stats.st_size / delim) && (delim /= 1024))
		;
	if (!delim)
		return (ft_numlen(file->stats.st_size, 10) + 1);
	return (ft_numlen(file->stats.st_size / delim, 10) +
						((file->stats.st_size / delim) < 10 ? 3 : 1));
}

int		ft_devlen(t_file *file, int is_major)
{
	if ((file->stats.st_mode & S_IFMT) == S_IFCHR ||
		(file->stats.st_mode & S_IFMT) == S_IFBLK)
	{
		if (is_major)
			return (ft_numlen(major(file->stats.st_rdev), 10));
		else
			return (ft_numlen(minor(file->stats.st_rdev), 10));
	}
	return (0);
}

void	ft_format_size(t_file *file)
{
	int		n;
	int		len;
	long	delim;
	char	*suffix;

	suffix = "BKMGT";
	delim = 1099511627776L;
	n = 4;
	g_lbufp += g_align.size - file->sizelen + (FL_LH && !g_align.is_cb ? 3 : 2);
	while (!(file->stats.st_size / delim) && (delim /= 1024))
		n--;
	len = file->sizelen -
			((delim && (file->stats.st_size / delim) < 10) ? 3 : 1);
	ft_strnum(g_lbufp, delim ? (file->stats.st_size / delim) :
								file->stats.st_size);
	g_lbufp += len;
	if (delim && (file->stats.st_size / delim) < 10)
	{
		*g_lbufp++ = '.';
		ft_strnum(g_lbufp, (((file->stats.st_size * 10) / delim) % 10) +
					((((file->stats.st_size * 100) / delim) % 10) < 5 ? 0 : 1));
		g_lbufp++;
	}
	*g_lbufp++ = suffix[n];
	g_lbufp++;
}

void	ft_put_devices(t_file *file)
{
	g_lbufp += g_align.dev1 - file->dev1len + 3;
	ft_strnum(g_lbufp, major(file->stats.st_rdev));
	g_lbufp += file->dev1len;
	*g_lbufp = ',';
	g_lbufp += g_align.dev2 - file->dev2len + 2;
	ft_strnum(g_lbufp, minor(file->stats.st_rdev));
	g_lbufp += file->dev2len + 1;
}

void	ft_put_size(t_file *file)
{
	if ((file->stats.st_mode & S_IFMT) == S_IFCHR ||
		(file->stats.st_mode & S_IFMT) == S_IFBLK)
		ft_put_devices(file);
	else if (FL_LH)
		ft_format_size(file);
	else
	{
		g_lbufp += g_align.size - file->sizelen + (FL_LH ? 3 : 2);
		ft_strnum(g_lbufp, file->stats.st_size);
		g_lbufp += file->sizelen + 1;
	}
}
