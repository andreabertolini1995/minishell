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

int	ft_atoi(const char *str)
{
	int	sign;
	int	final_number;
	int	i;

	sign = 1;
	final_number = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
			i++;
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				sign = -1;
			i++;
		}
		while ((str[i] >= '0') && (str[i] <= '9'))
		{
			final_number = final_number * 10 + (str[i] - 48);
			i++;
		}
		return (final_number * sign);
	}
	return (final_number * sign);
}
