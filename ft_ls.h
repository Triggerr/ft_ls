/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:52:17 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/20 20:54:17 by bbaelor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <sys/acl.h>
# include <stdlib.h>
# include <dirent.h>
# include <pwd.h>
# include <stdint.h>
# include <time.h>
# include <grp.h>
# include <unistd.h>
# include <errno.h>

/*
** Flag override groups and other flags
**
** FLGxM is group mask (0000 << (GROUP_NUM * 4))
** Group flags are store as a number
** Number begin at 1
**
** FLAG_x is array of valid flags
*/
# define FNAME			g_flags

# define FLAG_GROUP_0	"Clx1g"
# define FLG0M			18446744073709551600LU
# define FLAG_GROUP_1	"Ucu"
# define FLG1M			18446744073709551375LU
# define FLAG_GROUP_2	"Bbqw"
# define FLG2M			18446744073709547775LU
# define FLAG_GROUP_3	"HLP"
# define FLG3M			18446744073709490175LU
# define FLAG_OTH		"AFGRSTadfhnorst@"

/*
**	Flags constant
*/

# define FL_G0			(FNAME & 15LU)
# define FL_LL			(FL_G0 == 2)
# define FL_LG			(FL_G0 == 5)
# define FL_LONG		(FL_G0 == 2 || FL_G0 == 5)

# define FL_G1			((FNAME & 240LU) >> 4)

# define FL_G2			((FNAME & 3840LU) >> 8)
# define FL_UB			(FL_G2 == 1)
# define FL_LB			(FL_G2 == 2)

# define FL_G3			((FNAME & 61440LU) >> 12)
# define FL_UH			(FL_G3 == 1)
# define FL_UL			(FL_G3 == 2)
# define FL_UP			(FL_G3 == 3)

# define FL_UA			(FNAME & 65536LU)
# define FL_UF			(FNAME & 131072LU)
# define FL_UG			(FNAME & 262144LU)
# define FL_UR			(FNAME & 524288LU )
# define FL_US			(FNAME & 1048576LU)
# define FL_UT			(FNAME & 2097152LU)
# define FL_LA			(FNAME & 4194304LU)
# define FL_LD			(FNAME & 8388608LU)
# define FL_LF			(FNAME & 16777216LU)
# define FL_LH			(FNAME & 33554432LU)
# define FL_LN			(FNAME & 67108864LU)
# define FL_LO			(FNAME & 134217728LU)
# define FL_LR			(FNAME & 268435456LU)
# define FL_LS			(FNAME & 536870912LU)
# define FL_LT			(FNAME & 1073741824LU)
# define FL_DOG			(FNAME & 2147483648LU)

# define FT_NAME		"ft_ls"
# define ERR_FLAG_MSG	": illegal option -- "
# define ERR_ERR		": Error "
# define ERR_NO_FILE	": No such file or directory"
# define ERR_NO_ACCES	": Permission denied"
# define ERR_BAD_FILE	": Directory causes a cycle"
# define ERR_LONG_NAME	": File name too long"
# define AVAL_FLAGS		"ABCFGHLPRSTUabcdfghlnoqrstuwx1@"

# define ERR_FLAG		1
# define ERR_FILE		2
# define ERR_MALLOC		10

typedef struct			s_align
{
	int					block;
	int					name;
	int					links;
	int					user;
	int					group;
	int					size;
	int					dev1;
	int					dev2;
	int					is_cb;
	blkcnt_t			blocks;
}						t_align;

typedef struct			s_file
{
	char				name[1024];
	char				*path;
	struct stat			stats;
	int					namelen;
	int					linklen;
	int					uidlen;
	int					gidlen;
	int					sizelen;
	int					dev1len;
	int					dev2len;
	int					blklen;
}						t_file;

typedef struct			s_column
{
	int					columns;
	int					pos;
	int					optlen;
}						t_column;

extern uint64_t			g_flags;
extern t_align			g_align;
extern t_column			g_column;
extern char				*g_lbuff;
extern char				*g_lbufp;
extern int				g_buffsize;
extern int				g_sort;
extern int				(*g_sorts[5])(void *, void *);
extern void				(*g_print[4])(void *);

void					ft_set_align(void *data);
void					ft_init_prints(t_btree *root, int arg);
void					ft_setattr(t_file *file, int is_arg);
void					ft_setcolumn(void);
int						ft_ls(char *path);
void					ft_print_xattr(char *path);
void					ft_print_blocks();
int						ft_insert_file(char *name, t_btree **root);
t_btree					*ft_btree_iname(t_btree **begin, void *data,
										int (*cmp)(void *, void *));
int						ft_put_name(t_file *file);
int						ft_put_mode(t_file *file);
void					ft_put_user(t_file *file);
void					ft_put_group(t_file *file);
void					ft_put_size(t_file *file);
void					ft_put_block(t_file *file);
void					ft_put_time(t_file *file);
void					ft_put_xattr(char *path);
int						ft_namelen(char *name);
int						ft_print_column(t_btree *root);
int						ft_uidlen(uid_t uid);
int						ft_gidlen(gid_t gid);
int						ft_sizelen(t_file *file);
int						ft_devlen(t_file *file, int is_first);
int						ft_error_flag(char err_fl, int code);
int						ft_error_file(char *path, int code);
int						ft_setflags(int ac, char **av);
int						ft_insert_file(char *name, t_btree **root);
void					ft_free_elem(void *data);
int						ft_lsparam(int ac, char **av, int pos, int files);
int						ft_print_files(t_btree *root);

#endif
