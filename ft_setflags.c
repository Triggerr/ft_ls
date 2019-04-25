/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 21:04:46 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 20:18:14 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static uint64_t	ft_flag_index(char ch)
{
	uint64_t	i;

	i = 0;
	while (FLAG_GROUP_0[i])
		if (FLAG_GROUP_0[i++] == ch)
			return ((g_flags & FLG0M) | i);
	i = 0;
	while (FLAG_GROUP_1[i])
		if (FLAG_GROUP_1[i++] == ch)
			return ((g_flags & FLG1M) | (i << 4));
	i = 0;
	while (FLAG_GROUP_2[i])
		if (FLAG_GROUP_2[i++] == ch)
			return ((g_flags & FLG2M) | (i << 8));
	i = 0;
	while (FLAG_GROUP_3[i])
		if (FLAG_GROUP_3[i++] == ch)
			return ((g_flags & FLG3M) | (i << 12));
	i = 0;
	while (FLAG_OTH[i])
		if (FLAG_OTH[i++] == ch)
			return (g_flags | (1L << (15 + i)));
	return (0);
}

int				ft_getsort(void)
{
	if (FL_LF)
		return (6);
	if (FL_US)
		return (5);
	if (FL_LT)
		return (FL_G1 + 1);
	return (0);
}

int				ft_setflags(int ac, char **av)
{
	int		i;

	g_flags = isatty(STDOUT_FILENO) ? (g_flags & FLG0M) | 1 :
										(g_flags & FLG0M) | 4;
	g_flags = (g_flags & FLG2M) | (3 << 8);
	i = 1;
	while (i < ac && *av[i] == '-' && *(av[i] + 1))
	{
		av[i]++;
		while (*av[i])
		{
			if (!(g_flags = ft_flag_index(*av[i])))
				return (ft_error_flag(*av[i], -1));
			av[i]++;
		}
		i++;
	}
	if (!isatty(STDOUT_FILENO))
		g_flags = g_flags & (~(1L << (15 + 3)));
	g_sort = ft_getsort();
	return (i);
}
