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

void	ft_cd(t_command *command)
{
	if (is_file(command->args[0]))
		chdir(command->args[0]);
	else
		printf("minishell: cd: %s: No such file or directory\n",
			command->args[0]);
}

char	**fill_new_env(t_command *command, char **env)
{
	char	**new_env;
	int		length;
	int		i;

	length = 0;
	while (env[length] != NULL)
		length++;
	new_env = (char **) malloc (sizeof(char *) * (length + 2));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = command->args[0];
	new_env[i + 1] = NULL;
	return (new_env);
}

void	*ft_export(t_command *command)
{
	char	**env;
	char	**new_env;
	int		i;

	if (command->num_args == 0)
		ft_env(command, "export");
	env = command->env->envp;
	new_env = fill_new_env(command, env);
	i = 0;
	while (new_env[i] != NULL)
	{
		command->env->envp[i] = ft_strdup(new_env[i]);
		i++;
	}
	command->env->envp[i] = NULL;
	free(new_env);
	return (NULL);
}

char	*next_env_var(char **env, int i, int j)
{
	char	*var_tmp;
	int		length;

	length = 0;
	while (env[i][length] != '=')
		length++;
	var_tmp = (char *) malloc (sizeof(char) * length);
	if (var_tmp == NULL)
		return (NULL);
	while (env[i][j] != '=')
	{
		var_tmp[j] = env[i][j];
		j++;
	}
	return (var_tmp);
}

void	*ft_unset(t_command *command)
{
	char	**env;
	char	*var_name;
	char	*var_tmp;
	int		i;
	int		j;

	var_name = command->args[0];
	env = command->env->envp;
	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\n')
		{
			var_tmp = next_env_var(env, i, j);
			if (is_same_string(var_tmp, var_name))
			{
				free(env[i]);
				env[i] = NULL;
				free(var_tmp);
				return (NULL);
			}
			else
			{
				// free(var_tmp);
				break ;
			}
		}
		i++;
	}
	free(var_tmp);
	command->env->envp = env;
	return (NULL);
}
