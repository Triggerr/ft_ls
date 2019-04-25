/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 14:08:18 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/20 20:46:25 by bbaelor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_handling_file(char **file, t_btree **root)
{
	if (errno == ENOENT)
	{
		ft_error_file(*file, 0);
		*file = 0;
	}
	else if (errno == ENOTDIR || FL_LD)
	{
		ft_insert_file(*file, root);
		*file = 0;
	}
	return (0);
}

int		ft_check_dirs(int ac, char **av, int count, t_btree **root)
{
	DIR		*dir;

	while (count < ac)
	{
		errno = 0;
		if (!(dir = opendir(av[count])) || FL_LD)
			ft_handling_file(av + count, root);
		if (dir)
			closedir(dir);
		count++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	int		count;
	int		files;
	t_btree	*root;

	root = 0;
	if ((count = ft_setflags(ac, av)) < 0)
		return (ERR_FLAG);
	ft_check_dirs(ac, av, count, &root);
	files = root ? 1 : 0;
	if (root || FL_LD)
		ft_print_files(root);
	else if ((count == ac || count + 1 == ac) && !files)
		if (av[count] || count == ac)
			return (ft_ls(count == ac ? "." : av[count]));
	ft_lsparam(ac, av, count, files);
	return (0);
}
