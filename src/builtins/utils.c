/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:33:54 by abertoli          #+#    #+#             */
/*   Updated: 2022/10/21 18:29:38 by abertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	replace_substr(char *original, char *substring,
				char *result, char *replacement)
{
	char	*src;
	char	*dest;
	size_t	substring_length;
	size_t	replacement_length;

	src = original;
	dest = result;
	substring_length = ft_strlen(substring);
	replacement_length = ft_strlen(replacement);
	while (*src)
	{
		if (strstr(src, substring) == src)
		{
			ft_strcpy(dest, replacement);
			dest += replacement_length;
			src += substring_length;
		}
		else
			*dest++ = *src++;
	}
	*dest = '\0';
}

static int	calc_occurences_substr(char *original, char *substring)
{
	int			count;
	char		*temp;
	size_t		substring_length;

	temp = original;
	substring_length = ft_strlen(substring);
	count = 0;
	temp = ft_strnstr(temp, substring, ft_strlen(temp));
	while (temp != NULL)
	{
		temp += substring_length;
		count++;
		temp = ft_strnstr(temp, substring, ft_strlen(temp));
	}
	return (count);
}

char	*append_path(char *original, char *substring, char *replacement)
{
	int		count;
	size_t	result_length;
	char	*result;

	count = calc_occurences_substr(original, substring);
	result_length = strlen(original) + count
		* (ft_strlen(replacement) - ft_strlen(substring)) + 1;
	result = (char *) malloc (result_length);
	if (result == NULL)
		return (NULL);
	replace_substr(original, substring, result, replacement);
	return (result);
}

void	print_error_msg(char *str, int msg_type)
{
	if (msg_type == CMD_NOT_FOUND)
		printf("minishell: %s: command not found\n", str);
	else if (msg_type == NO_FILE_OR_DIR)
		printf("minishell: %s: No such file or directory\n", str);
	else if (msg_type == NUM_ARG_REQUIRED)
		printf("minishell: exit: %s: numeric argument required\n", str);
	else if (msg_type == TOO_MANY_ARGS)
		printf("minishell: exit: too many arguments\n");
	else if (msg_type == NOT_VALID_IDENTIFIER)
		printf("minishell: export: '%s': not a valid identifier\n", str);
}
