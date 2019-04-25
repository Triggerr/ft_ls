/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 20:11:53 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 20:18:47 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free_elem(void *data)
{
	free(((t_file *)data)->path);
	free(data);
}

int		ft_insert_file(char *name, t_btree **root)
{
	t_file			*file;

	if (!(file = ft_memalloc(sizeof(t_file))))
		exit(ERR_MALLOC);
	file->path = ft_strdup(name);
	ft_strcpy(file->name, name);
	ft_setattr(file, 1);
	if (!(ft_btree_ins(root, file, g_sorts[g_sort])))
		exit(ERR_MALLOC);
	return (0);
}

int		ft_lsparam(int ac, char **av, int pos, int files)
{
	int i;

	while (!av[pos] && pos < ac)
		pos++;
	i = -1;
	while (i++ + pos < ac)
	{
		if (!av[pos + i])
			continue ;
		if (i || files)
			ft_putchar('\n');
		ft_putstr(av[pos + i]);
		ft_putstr(":\n");
		ft_ls(av[pos + i]);
	}
	return (0);
}

int		ft_print_files(t_btree *root)
{
	if (!root)
		ft_insert_file(".", &root);
	ft_init_prints(root, 1);
	g_lbuff = malloc(sizeof(char) * g_buffsize);
	g_lbufp = g_lbuff;
	ft_memset(g_lbuff, ' ', g_buffsize);
	if (FL_G0 != 1)
		ft_btree_infix(root, g_print[FL_G0]);
	else
		ft_print_column(root);
	free(g_lbuff);
	return (0);
}
