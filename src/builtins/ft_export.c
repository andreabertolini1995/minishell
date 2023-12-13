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

bool	is_env_var(t_list *env_list, char *var_name)
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

static void	replace_env_var(t_list *env_list, char *var_name, char *var_value)
{
	t_env	*env_var;

	while (env_list != NULL)
	{
		env_var = env_list->content;
		if (is_same_string(env_var->name, var_name))
		{
			env_var->value = var_value;
			return ;
		}
		env_list = env_list->next;
	}
}

static char	*remove_double_quotes_from_str(char *str)
{
	char	*str_without_quotes;
	int		i;
	int		j;

	i = 0;
	if (str[i] == '"' && is_there_second_double_quote(str))
	{
		i++;
		str_without_quotes = (char *) malloc (sizeof(char)
				* (ft_strlen(str) - 2));
		if (str_without_quotes == NULL)
			return (NULL);
		j = 0;
		while (str[i] != '"')
		{
			str_without_quotes[j] = str[i];
			i++;
			j++;
		}
		return (str_without_quotes);
	}
	else
		return (str);
}

static int	add_env_var(t_command *command, int arg_index)
{
	char	**input_var;
	t_list	*env_list;

	env_list = command->env;
	input_var = ft_split(command->args[arg_index], '=');
	if (is_env_var(env_list, input_var[0]))
		replace_env_var(env_list, input_var[0], input_var[1]);
	else if (!is_valid_identifier(input_var[0]))
	{
		print_error_msg(command->args[arg_index], NOT_VALID_IDENTIFIER);
		free_str(input_var);
		return (EXIT_FAILURE);
	}
	else
	{
		if (input_var[0] != NULL && input_var[1] != NULL)
			ft_lstadd_back(&env_list,
				ft_lstnew(create_env_var(input_var[0],
						remove_double_quotes_from_str(input_var[1]))));
	}
	free_str(input_var);
	return (EXIT_SUCCESS);
}

int	ft_export(t_command *command)
{
	int		arg_index;

	if (command->num_args == 0)
		ft_env(command, "export");
	else
	{
		arg_index = 0;
		while (arg_index < command->num_args)
		{
			if (!is_same_string(command->args[arg_index], " ")
				&& !is_same_string(command->args[arg_index], "\t"))
				if (add_env_var(command, arg_index) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			arg_index++;
		}
	}
	return (EXIT_SUCCESS);
}
