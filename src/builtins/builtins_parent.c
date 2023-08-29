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

static bool	is_env_var(t_list *env_list, char *var_name)
{
	t_env	*env_var;

	while (env_list != NULL)
	{
		env_var = env_list->content;
		if (is_same_string(env_var->name, var_name))
			return (true);
		env_list = env_list->next;
	}
	return (false);
}

void	ft_export(t_command *command)
{
	t_list	*env_list;
	t_env	*env_var;
	char	**input_var;
	int		arg_index;
	
	if (command->num_args == 0)
		ft_env(command, "export");
	else
	{
		arg_index = 0;
		while (arg_index < command->num_args)
		{
			env_list = command->env;
			if (!is_same_string(command->args[arg_index], " "))
			{
				input_var = ft_split(command->args[arg_index], '=');
				if (is_env_var(env_list, input_var[0]))
				{
					while (env_list != NULL)
					{
						env_var = env_list->content;
						if (is_same_string(env_var->name, input_var[0]))
						{
							env_var->value = input_var[1];
							return ;
						}
						env_list = env_list->next;
					}
				}
				else
					ft_lstadd_back(&env_list, ft_lstnew(create_env_var(input_var[0], input_var[1])));
			}
			arg_index++;
		}
	}
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

void	ft_unset(t_command *command)
{
	t_list	*env_list;
	t_env	*env_var;
	t_list	*prev_list;
	int		arg_index;

	arg_index = 0;
	while (arg_index < command->num_args)
	{
		if (!is_same_string(command->args[arg_index], " "))
		{
			env_list = command->env;
			prev_list = NULL;
			while (env_list != NULL)
			{
				env_var = env_list->content;
				if (is_same_string(env_var->name, command->args[arg_index]))
				{
					if (prev_list == NULL)
						prev_list = env_list->next;
					else
						prev_list->next = env_list->next;
					free(env_var);
					free(env_list);
				}
				prev_list = env_list;
				env_list = env_list->next;
			}
		}
		arg_index++;
	}
}
