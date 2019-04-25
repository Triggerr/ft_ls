/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_newline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 20:20:24 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 20:06:56 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_newline(void *data)
{
	g_lbufp = g_lbuff;
	ft_memset(g_lbuff, ' ', g_buffsize);
	ft_put_block((t_file *)data);
	ft_put_name((t_file *)data);
	*g_lbufp = 0;
	ft_putstr(g_lbuff);
	ft_putchar('\n');
}
