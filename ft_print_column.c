/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_column.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 15:00:53 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/20 20:46:27 by bbaelor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int g_pos;
static int g_lines;
static int g_fcount;
static int g_curline;

void	ft_print_n(void *data)
{
	g_pos++;
	if (((g_pos - 1) % g_lines != g_curline) &&
		(g_curline != g_lines || ((g_pos - 1) % g_lines)))
		return ;
	ft_put_block((t_file *)data);
	ft_put_name((t_file *)data);
	if (g_fcount - (g_pos - 1) >= g_lines)
		g_lbufp += g_column.optlen - ((t_file *)data)->namelen;
}

int		ft_print_column(t_btree *root)
{
	g_fcount = ft_btree_count(root);
	g_lines = g_fcount / g_column.columns +
						((g_fcount % g_column.columns) ? 1 : 0);
	if (FL_LS)
		g_column.optlen -= g_align.block;
	g_curline = 1;
	while (g_curline <= g_lines)
	{
		g_lbufp = g_lbuff;
		ft_memset(g_lbuff, ' ', g_buffsize);
		g_pos = 1;
		ft_btree_infix(root, &ft_print_n);
		*g_lbufp = 0;
		ft_putstr(g_lbuff);
		ft_putchar('\n');
		g_curline++;
	}
	return (0);
}
