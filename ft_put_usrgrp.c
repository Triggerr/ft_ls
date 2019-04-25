/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_usrgrp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:48:14 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 19:45:01 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_put_user(t_file *file)
{
	if (FL_LG)
		return ;
	if (FL_LN)
		ft_strnum(g_lbufp, file->stats.st_uid);
	else
		ft_memcpy(g_lbufp, getpwuid(file->stats.st_uid)->pw_name, file->uidlen);
	g_lbufp += g_align.user + 2;
}

void	ft_put_group(t_file *file)
{
	if (FL_LO)
		return ;
	if (FL_LN)
		ft_strnum(g_lbufp, file->stats.st_gid);
	else
		ft_memcpy(g_lbufp, getgrgid(file->stats.st_gid)->gr_name, file->gidlen);
	g_lbufp += g_align.group;
}
