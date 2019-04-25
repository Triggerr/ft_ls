/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerewol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:51:45 by bwerewol          #+#    #+#             */
/*   Updated: 2018/11/20 17:51:46 by bwerewol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (dest[i])
		i++;
	while (*src && n)
	{
		n--;
		dest[i++] = *src++;
	}
	dest[i] = 0;
	return (dest);
}
