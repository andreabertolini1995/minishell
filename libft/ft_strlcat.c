/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:38:21 by abertoli          #+#    #+#             */
/*   Updated: 2022/10/18 10:38:23 by abertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;
	size_t	n;

	i = 0;
	dest_len = ft_strlen(dest);
	n = ft_min(dest_len, size);
	if (size > 0)
	{
		if (size > dest_len)
		{
			while (dest_len + i < (size - 1) && src[i] != '\0')
			{
				dest[dest_len + i] = src[i];
				i++;
			}
		}
		dest[dest_len + i] = '\0';
		i++;
	}
	return (ft_strlen(src) + n);
}
