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

/* Function to check if the env variable name
(not value) contains invalid characters:
- digits are admitted unless it starts with a digit
*/
bool	is_valid_identifier(char *str)
{
	int	i;

	if (str == NULL)
		return (false);
	i = 0;
	if (ft_isdigit(str[i]))
		return (false);
	while (str[i] != '\0')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i])
			&& str[i] != ' ' && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	delete_env_var(t_command *command, int arg_index)
{
	t_list	*env_list;
	t_list	*prev_list;
	t_env	*env_var;

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
		}
		prev_list = env_list;
		env_list = env_list->next;
	}
}

int	ft_unset(t_command *command)
{
	int		arg_index;

	arg_index = 0;
	while (arg_index < command->num_args)
	{
		if (!is_valid_identifier(command->args[arg_index]))
		{
			printf("minishell: unset: '%s': not a valid identifier\n",
				command->args[arg_index]);
			return (EXIT_FAILURE);
		}
		else if (!is_same_string(command->args[arg_index], " ")
			&& !is_same_string(command->args[arg_index], "\t"))
			delete_env_var(command, arg_index);
		arg_index++;
	}
	return (EXIT_SUCCESS);
}
