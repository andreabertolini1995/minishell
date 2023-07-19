/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:18:22 by abertoli          #+#    #+#             */
/*   Updated: 2022/10/19 17:18:23 by abertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t n)
{
	size_t	j;
	size_t	i;
	size_t	small_length;

	small_length = ft_strlen(small);
	if (small_length == 0)
		return ((char *)(big));
	if (ft_strlen(big) == 0)
		return (0);
	i = 0;
	j = 0;
	while (small[j] != '\0' && big[i] != '\0' && i < n)
	{
		if (big[i] == small[j])
			j++;
		i++;
		if (j == small_length)
			return ((char *)(&big[i - j]));
		if (big[i] != small[j] && j > 0)
		{
			i = i - j + 1;
			j = 0;
		}
	}
	return (0);
}
