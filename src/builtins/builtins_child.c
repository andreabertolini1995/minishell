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
	size_t i;

	i = 0;

	if (option[i] != '-' && option[i + 1] != 'n')
		return (true);
	while (option[i] != '\0')
	{
		if (option[i] == '-')
			i++;
		while(option[i] == 'n')
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
}

void	ft_pwd(void)
{
	char	buffer[1024];

	printf("%s\n", getcwd(buffer, sizeof(buffer)));
}

void	ft_env(t_command *command, char *cmd)
{
	char	**env;
	int		i;

	env = command->env->envp;
	i = 0;
	while (env[i] != NULL)
	{
		if (is_same_string(cmd, "export"))
			printf("declare -x %s\n", env[i]);
		else
			printf("%s\n", env[i]);
		i++;
	}
}

void	clear(void)
{
	printf("\033[H\033[J");
}
