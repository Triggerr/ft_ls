/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:26:37 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 19:59:48 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_lines(void *data)
{
	static int spaces = 0;

	if (g_column.pos && g_column.pos != -1)
		g_lbufp += spaces;
	if (!g_column.pos)
	{
		*g_lbufp = 0;
		ft_putstr(g_lbuff);
		ft_putchar('\n');
		g_lbufp = g_lbuff;
		ft_memset(g_lbuff, ' ', g_buffsize);
	}
	if (g_column.pos == -1)
		g_column.pos = 0;
	ft_put_block((t_file *)data);
	ft_put_name((t_file *)data);
	if (g_column.pos == (g_column.columns - 1))
		g_column.pos = 0;
	else
	{
		spaces = g_column.optlen - ((t_file *)data)->namelen;
		if (FL_LS)
			spaces -= g_align.block;
		g_column.pos++;
	}
}
