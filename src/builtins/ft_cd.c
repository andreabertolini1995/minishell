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

static char	*get_old_pwd(t_command *command)
{
	t_list	*env_list;
	t_env	*env_var;

	env_list = command->env;
	while (env_list != NULL)
	{
		env_var = env_list->content;
		if (is_same_string(env_var->name, "OLDPWD"))
			return (env_var->value);
		env_list = env_list->next;
	}
	return (NULL);
}

static char	*get_home_dir(t_command *command)
{
	t_list	*env_list;
	t_env	*env_var;

	env_list = command->env;
	while (env_list != NULL)
	{
		env_var = env_list->content;
		if (is_same_string(env_var->name, "HOME"))
			return (env_var->value);
		env_list = env_list->next;
	}
	return (NULL);
}

static	t_command	*create_export_cmd(t_command *cd_cmd,
						char *var_name, char *var_value)
{
	t_command	*command;

	command = (t_command *) malloc (sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->num_args = 1;
	command->args = (char **) malloc (sizeof(char *) * command->num_args);
	if (command->args == NULL)
		return (NULL);
	command->args[0] = ft_strjoin(var_name, "=");
	command->args[0] = ft_strjoin(command->args[0], var_value);
	command->env = cd_cmd->env;
	return (command);
}

static int	change_dir(t_command *command, char *pwd)
{
	char	buffer[1024];

	ft_export(create_export_cmd(command, "OLDPWD",
			getcwd(buffer, sizeof(buffer))));
	chdir(pwd);
	ft_export(create_export_cmd(command, "PWD",
			getcwd(buffer, sizeof(buffer))));
	return (EXIT_SUCCESS);
}

int	ft_cd(t_command *command)
{
	if (command->num_args == 0
		|| (command->num_args == 1
			&& is_same_string(command->args[0], "~")))
		return (change_dir(command, get_home_dir(command)));
	else if (command->num_args == 1
		&& is_same_string(command->args[0], "-"))
		return (change_dir(command, get_old_pwd(command)));
	else if (is_file(command->args[0]))
		return (change_dir(command, command->args[0]));
	else
	{
		printf("minishell: cd: %s: No such file or directory\n",
			command->args[0]);
		return (EXIT_FAILURE);
	}
}
