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

static void	replace_substr(char *original, char *substring, char *result, char *replacement)
{
	char	*src;
	char 	*dest;
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
            strcpy(dest, replacement); // to be replaced with own function
            dest += replacement_length;
            src += substring_length;
        } else
            *dest++ = *src++;
    }
    *dest = '\0';
}

static int	calc_occurences_substr(char *original, char *substring)
{
	int 		count;
	char 		*temp;
	size_t 		substring_length;
	
	temp = original;
	substring_length = ft_strlen(substring);
	count = 0;
    while ((temp = strstr(temp, substring)) != NULL) {
        temp += substring_length;
        count++;
    }
	return (count);
}

char	*append_path(char *original, char *substring, char *replacement)
{
	int		count;
	size_t	result_length;
	char	*result;

   	count = calc_occurences_substr(original, substring);
    result_length = strlen(original) + count *
		(ft_strlen(replacement) - ft_strlen(substring)) + 1;
	result = (char *) malloc (result_length);
    if (result == NULL)
        return (NULL);
    replace_substr(original, substring, result, replacement);
    return (result);
}

int	ft_pwd(void)
{
	char	buffer[1024];
	char	*pwd;

	pwd = getcwd(buffer, sizeof(buffer));
	if (pwd == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}

char	*ft_getenv(t_list *env_list, char *var_name)
{
	t_env	*env_var;
	char	*result;
	size_t	var_name_length;
	size_t	count;
	
	result = NULL;
	var_name_length = ft_strlen(var_name);
	count = 0;
	while (env_list != NULL)
	{
		env_var = env_list->content;
		if (is_same_string(var_name, env_var->name))
		{
			while (count < var_name_length)
			{
				if (result == NULL)
					result = ft_strjoin("", env_var->value);
				else
					result = ft_strjoin(result, env_var->value);
				count += ft_strlen(env_var->name) + 1;
			}
		}
		env_list = env_list->next;
	}
	return (result);
}

int	ft_env(t_command *command, char *cmd)
{
	t_list	*env_list;
	t_env	*env_var;

	env_list = command->env;
	while (env_list != NULL)
	{
		env_var = env_list->content;
		if (is_same_string(cmd, "export"))
		{
			if (env_var->value == NULL)
				printf("declare -x %s\n", env_var->name);
			else
				printf("declare -x %s=%s\n", env_var->name, env_var->value);
		}
		else
		{
			if (env_var->value != NULL)
				printf("%s=%s\n", env_var->name, env_var->value);
		}
		env_list = env_list->next;
	}
	return (EXIT_SUCCESS);
}

int	clear(void)
{
	printf("\033[H\033[J");
	return (EXIT_SUCCESS);
}
