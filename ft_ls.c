/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 16:11:00 by bwerewol          #+#    #+#             */
/*   Updated: 2018/12/26 20:12:03 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

uint64_t	g_flags = 0;
char		*g_lbuff;
char		*g_lbufp;
int			g_buffsize;
int			g_sort;

int		ft_skip_file(char *name)
{
	if (*name != '.')
		return (0);
	else if (FL_UA && (ft_strequ(name, ".") || ft_strequ(name, "..")))
		return (1);
	else if (!(FL_LA || FL_LF || FL_UA))
		return (1);
	return (0);
}

int		ft_read_dir(char *path, t_btree **root)
{
	int				count;
	DIR				*direct;
	struct dirent	*data;
	t_file			*file;

	if (!(direct = opendir(path)))
		return (ft_error_file(path, -ERR_FILE));
	count = 0;
	while ((data = readdir(direct)))
	{
		if (ft_skip_file(data->d_name))
			continue ;
		if (!(file = ft_memalloc(sizeof(t_file))))
			exit(ERR_MALLOC);
		ft_strcpy(file->name, data->d_name);
		file->path = ft_pathadd(path, file->name);
		ft_setattr(file, 0);
		if (!(ft_btree_ins(root, file, g_sorts[g_sort])))
			exit(ERR_MALLOC);
		count++;
	}
	closedir(direct);
	return (count);
}

void	ft_rec_print(void *data)
{
	if (((((t_file *)data)->stats.st_mode & S_IFMT) != S_IFDIR) ||
		(ft_strequ(((t_file *)data)->name, ".")) ||
		(ft_strequ(((t_file *)data)->name, "..")))
		return ;
	ft_putchar('\n');
	ft_putstr(((t_file *)data)->path);
	ft_putstr(":\n");
	ft_ls(((t_file *)data)->path);
}

void	ft_init_prints(t_btree *root, int arg)
{
	ft_bzero(&g_align, sizeof(g_align));
	ft_btree_infix(root, &ft_set_align);
	if (FL_LONG && g_align.is_cb)
		g_align.size = (g_align.size < (g_align.dev1 + g_align.dev2 + 3)) ?
						(g_align.dev1 + g_align.dev2 + 3) : g_align.size;
	if ((FL_LONG || FL_LS) && root && !arg)
		ft_print_blocks();
	if (FL_G0 == 1 || FL_G0 == 3)
		ft_setcolumn();
	if (!FL_LONG && FL_G0 != 4)
		return ;
	if (FL_G0 == 4)
		g_buffsize = (FL_LS ? g_align.block + 1 : 0) +
			g_align.name + (FL_UF ? 2 : 1) + (FL_UG ? 22 : 0);
	else
		g_buffsize = ((FL_LS ? g_align.block + 1 : 0) + (12) +
				g_align.links + 1 + (FL_LG ? 0 : g_align.user + 2) +
				(FL_LO ? 0 : g_align.group) + g_align.size + 3 +
				(FL_UT ? 21 : 13) + (g_align.name * 4) +
				(FL_UF ? 2 : 1) + (FL_UG ? 22 : 0));
}

int		ft_ls(char *path)
{
	t_btree *root;

	root = 0;
	if (ft_read_dir(path, &root) < 0)
		return (ERR_FILE);
	ft_init_prints(root, 0);
	g_lbuff = malloc(sizeof(char) * g_buffsize);
	g_lbufp = g_lbuff;
	ft_memset(g_lbuff, ' ', g_buffsize);
	if (FL_G0 != 1)
		ft_btree_infix(root, g_print[FL_G0]);
	else
		ft_print_column(root);
	free(g_lbuff);
	if (FL_UR && !FL_LD)
		ft_btree_infix(root, &ft_rec_print);
	ft_btree_del(&root, &ft_free_elem);
	return (0);
}
