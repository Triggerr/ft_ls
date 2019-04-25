/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_array.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:26:25 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/20 20:46:40 by bbaelor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FUNC_ARRAY_H
# define FT_FUNC_ARRAY_H

int		ft_sort_by_name(void *a, void *b);
int		ft_sort_by_time(void *a, void *b);
# ifdef _DARWIN_FEATURE_64_BIT_INODE

int		ft_sort_by_create(void *a, void *b);
# endif

int		ft_sort_by_change(void *a, void *b);
int		ft_sort_by_access(void *a, void *b);
int		ft_sort_by_size(void *a, void *b);
int		ft_sort_by_nothing(void *a, void *b);

void	ft_print_long(void *data);
void	ft_print_lines(void *data);
void	ft_print_newline(void *data);
#endif
