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

static int	ft_is_in_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_calc_trim_size(char const *s1, char const *set)
{
	int	i;
	int	chars_front;
	int	chars_back;

	chars_front = 0;
	chars_back = 0;
	i = 0;
	while (ft_is_in_set(set, s1[i]))
	{	
		chars_front++;
		i++;
	}
	i = ft_strlen(s1) - 1;
	while (ft_is_in_set(set, s1[i]))
	{
		chars_back++;
		i--;
	}
	if (((int) ft_strlen(s1) - chars_front - chars_back) < 0)
		return (0);
	return (ft_strlen(s1) - chars_front - chars_back);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimstr;
	int		i;
	int		j;
	int		k;

	trimstr = (char *) malloc (sizeof(char) * (ft_calc_trim_size(s1, set) + 1));
	if (trimstr == NULL)
		return (NULL);
	i = 0;
	while (ft_is_in_set(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	while (ft_is_in_set(set, s1[j - 1]))
		j--;
	k = 0;
	while (i < j)
	{
		trimstr[k] = s1[i];
		i++;
		k++;
	}
	trimstr[k] = '\0';
	return (trimstr);
}
