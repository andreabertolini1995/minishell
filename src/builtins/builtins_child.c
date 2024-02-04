/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:33:54 by abertoli          #+#    #+#             */
/*   Updated: 2023/12/17 11:34:29 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static char	*update_result(char *env_var_value, char *result)
{
	char	*temp;

	temp = ft_strjoin(result, env_var_value);
	free(result);
	result = temp;
	return (result);
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
					result = ft_strdup(env_var->value);
				else
					result = update_result(env_var->value, result);
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
