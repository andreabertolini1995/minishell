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
	char		*arg;

	command = (t_command *) malloc (sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->num_args = 1;
	command->args = (char **) malloc (sizeof(char *) * command->num_args);
	if (command->args == NULL)
		return (NULL);
	arg = ft_strjoin(var_name, "=");
	command->args[0] = ft_strjoin(arg, var_value);
	free(arg);
	command->env = cd_cmd->env;
	return (command);
}

static int	change_dir(t_command *command, char *pwd)
{
	char	buffer[1024];
	t_command	*command1;
	t_command	*command2;
	
	command1 = create_export_cmd(command, "OLDPWD",
			getcwd(buffer, sizeof(buffer)));
	ft_export(command1);
	free_str(command1->args);
	free(command1);
	chdir(pwd);
	command2 = create_export_cmd(command, "PWD",
			getcwd(buffer, sizeof(buffer)));
	ft_export(command2);
	free_str(command2->args);
	free(command2);
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
		print_error_msg(command->args[0], NO_FILE_OR_DIR);
		return (EXIT_FAILURE);
	}
}
