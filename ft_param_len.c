/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 19:42:34 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 19:58:35 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_uidlen(uid_t uid)
{
	if (!FL_LN)
		return (ft_strlen(getpwuid(uid)->pw_name));
	return (ft_numlen(uid, 10));
}

int		ft_gidlen(gid_t gid)
{
	if (!FL_LN)
		return (ft_strlen(getgrgid(gid)->gr_name));
	return (ft_numlen(gid, 10));
}

int		ft_namelen(char *name)
{
	int len;
	int chlen;

	len = 0;
	while (*name)
	{
		chlen = ft_charsize(*name);
		if (FL_G2 > 2)
			len++;
		if (FL_G2 == 1)
			len += (chlen == 1) && !(*name == '\"' || *name == '\\' ||
					(*name >= 0x7 && *name <= 0xD)) ? 1 : chlen * 4;
		if (FL_G2 == 2 && chlen == 1)
			len += (*name == '\"' || *name == '\\' ||
					(*name >= 0x7 && *name <= 0xD)) ? 2 : 1;
		if (FL_G2 == 2 && chlen > 1)
			len += chlen * 4;
		name += chlen;
	}
	return (len);
}
