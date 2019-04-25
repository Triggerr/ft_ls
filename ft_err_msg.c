/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:27:18 by bwerewol          #+#    #+#             */
/*   Updated: 2019/02/20 20:54:57 by bbaelor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_error_flag(char err_fl, int code)
{
	ft_putstr_fd(FT_NAME, 2);
	ft_putstr_fd(ERR_FLAG_MSG, 2);
	ft_putchar_fd(err_fl, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(FT_NAME, 2);
	ft_putstr_fd(" [-", 2);
	ft_putstr_fd(AVAL_FLAGS, 2);
	ft_putstr_fd("] [file ...]", 2);
	ft_putchar_fd('\n', 2);
	return (code);
}

int	ft_error_file(char *path, int code)
{
	ft_putstr_fd(FT_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(path, 2);
	if (errno == ENOENT)
		ft_putstr_fd(ERR_NO_FILE, 2);
	else if (errno == EACCES)
		ft_putstr_fd(ERR_NO_ACCES, 2);
	else if (errno == EBADF)
		ft_putstr_fd(ERR_BAD_FILE, 2);
	else if (errno == ENAMETOOLONG)
		ft_putstr_fd(ERR_LONG_NAME, 2);
	else
	{
		ft_putstr_fd(ERR_ERR, 2);
		ft_putnbr(errno);
	}
	ft_putchar_fd('\n', 2);
	return (code);
}
