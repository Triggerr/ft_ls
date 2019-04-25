/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_attr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 22:09:52 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 19:37:23 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_put_block(t_file *file)
{
	if (!FL_LS)
		return ;
	g_lbufp += g_align.block - file->blklen;
	ft_strnum(g_lbufp, file->stats.st_blocks);
	g_lbufp += file->blklen + 1;
}

void	ft_put_time(t_file *file)
{
	int		len;
	time_t	usetime;
	time_t	curtime;

	len = (FL_UT) ? 21 : 13;
	if (!FL_G1)
		usetime = file->stats.st_mtimespec.tv_sec;
	else if (FL_G1 == 1)
		usetime = file->stats.st_birthtimespec.tv_sec;
	else if (FL_G1 == 2)
		usetime = file->stats.st_ctimespec.tv_sec;
	else if (FL_G1 == 3)
		usetime = file->stats.st_atimespec.tv_sec;
	curtime = time(0);
	if (!FL_UT && (curtime >= usetime) && (curtime - usetime < 15778800))
		ft_memcpy(g_lbufp, ctime(&usetime) + 4, 12);
	else if (!FL_UT)
	{
		ft_memcpy(g_lbufp, ctime(&usetime) + 4, 6);
		ft_memcpy(g_lbufp + 8, ctime(&usetime) + 20, 4);
	}
	else
		ft_memcpy(g_lbufp, ctime(&usetime) + 4, 20);
	g_lbufp += len;
}

void	ft_put_xattr(char *path)
{
	ssize_t	sizelist;
	ssize_t	sizeattr;
	ssize_t	i;
	char	buff[256];

	if (!(sizelist = listxattr(path, buff, 256, XATTR_NOFOLLOW)))
		return ;
	i = 0;
	while (i < sizelist)
	{
		sizeattr = getxattr(path, buff + i, 0, 0, 0, XATTR_NOFOLLOW);
		write(1, "\n\t", 2);
		ft_putstr(buff + i);
		write(1, "\t  ", 3);
		ft_putnbr(sizeattr);
		i += ft_strlen(buff) + 1;
	}
}
