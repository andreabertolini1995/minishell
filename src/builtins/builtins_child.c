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

int	g_exit_code;

static bool	check_new_line(char *option)
{
	size_t	i;

	i = 0;
	if (option[i] != '-' && option[i + 1] != 'n')
		return (true);
	while (option[i] != '\0')
	{
		if (option[i] == '-')
			i++;
		while (option[i] == 'n')
			i++;
	}
	if (i == ft_strlen(option))
		return (false);
	return (true);
}

void	ft_echo(t_command *command)
{
	int		i;
	bool	new_line;

	i = 0;
	new_line = check_new_line(command->args[i]);
	if (new_line == false)
		i++;
	if (is_same_string(command->args[i], "$?"))
	{
		printf("%d", g_exit_code);
		i++;
	}
	while (i < command->num_args)
	{
		printf("%s", command->args[i]);
		i++;
	}
	if (new_line == true)
		printf("\n");
	g_exit_code = EXIT_SUCCESS;
}

void	ft_pwd(void)
{
	char	buffer[1024];

	printf("%s\n", getcwd(buffer, sizeof(buffer)));
	g_exit_code = EXIT_SUCCESS;
}

void	ft_env(t_command *command, char *cmd)
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
	g_exit_code = EXIT_SUCCESS;
}

void	clear(void)
{
	printf("\033[H\033[J");
	g_exit_code = EXIT_SUCCESS;
}
