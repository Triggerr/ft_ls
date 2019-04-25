/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 19:30:31 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/20 20:46:28 by bbaelor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_put_laddr(t_file *file)
{
	char buff[1000];

	write(1, " -> ", 4);
	write(1, buff, readlink(file->path, buff, 1000));
}

void	ft_print_blocks(void)
{
	ft_putstr("total ");
	ft_putnbr(g_align.blocks);
	ft_putchar('\n');
}

void	ft_put_hlink(t_file *file)
{
	g_lbufp += g_align.links - file->linklen;
	ft_strnum(g_lbufp, file->stats.st_nlink);
	g_lbufp += file->linklen + 1;
}

void	ft_print_long(void *data)
{
	int	attr;

	g_lbufp = g_lbuff;
	ft_memset(g_lbuff, ' ', g_buffsize);
	ft_put_block((t_file *)data);
	attr = ft_put_mode((t_file *)data);
	ft_put_hlink((t_file *)data);
	ft_put_user((t_file *)data);
	ft_put_group((t_file *)data);
	ft_put_size((t_file *)data);
	ft_put_time((t_file *)data);
	ft_put_name((t_file *)data);
	*g_lbufp = 0;
	ft_putstr(g_lbuff);
	if (S_ISLNK(((t_file *)data)->stats.st_mode))
		ft_put_laddr((t_file *)data);
	if (attr == '@' && FL_DOG)
		ft_put_xattr(((t_file *)data)->path);
	ft_putchar('\n');
}
