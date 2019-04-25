/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 10:58:25 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/20 20:44:49 by bbaelor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

# define STYLE_DEF		0
# define STYLE_BOLD		1
# define STYLE_UNDER	4
# define STYLE_BLINK	5
# define STYLE_INV		7
# define STYLE_INVIS	8

# define COLOR_BLACK	30
# define COLOR_RED		31
# define COLOR_GREEN	32
# define COLOR_YELLOW	33
# define COLOR_BLUE		34
# define COLOR_MAGENTA	35
# define COLOR_CYAN		36
# define COLOR_WHITE	37

# define BACKG_BLACK	40
# define BACKG_RED		41
# define BACKG_GREEN	42
# define BACKG_YELLOW	43
# define BACKG_BLUE		44
# define BACKG_MAGENTA	45
# define BACKG_CYAN		46
# define BACKG_WHITE	47

/*
** Get Next Line
*/

# define BUFF_SIZE 256

typedef struct		s_line
{
	char			*data;
	size_t			pos;
	long int		end;
	int				fd;
	struct s_line	*next;
}					t_line;
int					get_next_line(const int fd, char **line);

/*
** Lists
*/

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

t_list				*ft_listnew(void *data);
t_list				*ft_push(t_list **begin, void *data);
t_list				*ft_pop(t_list **begin);
t_list				*ft_push_back(t_list **begin, void *data);
t_list				*ft_listlast(t_list *begin);

/*
** Binary tree
*/

typedef struct		s_btree
{
	void			*data;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

t_btree				*ft_btree_new(void *data);
t_btree				*ft_btree_ins(t_btree **root, void *data,
									int (*cmp)(void *, void *));
void				ft_btree_prefix(t_btree *root, void (*f)(void *data));
void				ft_btree_infix(t_btree *root, void (*f)(void *data));
void				ft_btree_suffix(t_btree *root, void (*f)(void *data));
t_btree				*ft_btree_search(t_btree *root, void *data,
									int (*cmp)(void *, void *));
int					ft_btree_count(t_btree *root);
void				ft_btree_del(t_btree **root, void (*f)(void *data));

char				*ft_itoa_base(long int num, int base);
char				*ft_strrev(char *s);
int					ft_isblank(int c);
int					ft_iscntrl(int c);
int					ft_isgraph(int c);
int					ft_islower(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
int					ft_isxdigit(int c);
int					ft_isnumber(int c);
int					ft_str_is_alpha(char *s);
int					ft_str_is_lowercase(char *s);
int					ft_str_is_numeric(char *s);
int					ft_str_is_printable(char *s);
int					ft_str_is_uppercase(char *s);
char				*ft_strupcase(char *s);
char				*ft_strlowcase(char *s);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
size_t				ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
								size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *nptr);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2, int free_s);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_err_msg(char *msg, int errn);
int					ft_numlen(int64_t num, int base);
char				*ft_stradd(char *dest, char *src);
void				*ft_memdup(void *data, size_t size);
void				ft_putnchr(char ch, int n);
void				ft_strcolor(char *str, int x1, int x2, int x3);
int					ft_charsize(unsigned char c);
int					ft_strnum_base(char *str, long int num, int base);
int					ft_strnum(char *str, long int num);
char				*ft_pathadd(char *path, char *name);

#endif
