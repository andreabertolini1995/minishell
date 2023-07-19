/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:07:52 by abertoli          #+#    #+#             */
/*   Updated: 2022/10/27 15:07:53 by abertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_find_size(size_t str_len, size_t len, unsigned int start)
{
	if (start > str_len)
		return (0);
	else if (str_len <= len)
		return (str_len - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	substr = (char *) malloc (sizeof(char)
			* (ft_find_size(ft_strlen(s), len, start) + 1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (start > ft_strlen(s) || s[start] == '\0')
		{
			substr[i] = '\0';
			return (substr);
		}
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
