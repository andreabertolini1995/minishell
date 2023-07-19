/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:42:12 by abertoli          #+#    #+#             */
/*   Updated: 2022/10/20 14:42:16 by abertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iterative_itoa(int n, char *str, int k)
{
	if (n >= 0 && n < 10)
	{
		str[k] = n + 48;
		k++;
	}
	else if (n >= 10 && n <= 99)
	{
		str[k] = (n / 10) + 48;
		k++;
		str[k] = (n % 10) + 48;
		k++;
	}
	return (k);
}

static int	ft_recursive_itoa(int n, char *str, int k)
{
	k = ft_iterative_itoa(n, str, k);
	if (n >= 100)
	{
		k = ft_recursive_itoa(n / 10, str, k);
		str[k] = (n % 10) + 48;
		k++;
	}
	else if (n < 0)
	{
		str[k] = '-';
		k++;
		if (n == -2147483648)
		{
			str[k] = '2';
			k++;
			k = ft_recursive_itoa(147483648, str, k);
		}
		else
			k = ft_recursive_itoa(-n, str, k);
	}
	return (k);
}

static int	ft_calc_size(int n)
{
	int	i;
	int	size;

	i = 1000000000;
	size = 12;
	if (n == -2147483648)
		return (size);
	if (n == 0)
		return (2);
	if (n > 0)
		size = size - 1;
	else
		n = -n;
	while (i > 0)
	{
		if (n / i > 0)
			return (size);
		size = size - 1;
		i = i / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		k;
	int		size;

	size = ft_calc_size(n);
	str = (char *) malloc (sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	k = 0;
	k = ft_recursive_itoa(n, str, k);
	str[k] = '\0';
	return (str);
}
