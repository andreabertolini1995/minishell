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

void	init_shell(void)
{
	printf("\n           _       _     _          _ _");
	printf("\n _ __ ___ (_)_ __ (_) __| |_    ___| | |");
	printf("\n|  _   _ \\| |  _ \\| / __|  _ \\ / _ \\ | |");
	printf("\n| | | | | | | | | | \\__ \\ | | |  __/ | |");
	printf("\n|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|");
	printf("\n\n");
	printf("         by abertoli & shurlebu\n\n");
	sleep(1);
	clear();
}

static t_env	*store_env(char **envp)
{
	t_env	*env;

	env = (t_env *) malloc (sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->envp = envp;
	return (env);
}

void	minishell(t_env *env)
{
	char	*cmd;
	t_list	*tokens_list;
	t_list	*commands_list;

	while (42)
	{
		cmd = readline("***: ");
		if (cmd == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(cmd);
		tokens_list = lexer(cmd, env);
		commands_list = parser(tokens_list, env);
		free_tokens(tokens_list);
		executor(commands_list);
		free_commands(commands_list);
		// Lexer test
		// ft_lstiter(tokens_list, print_token);
		// Parser test
		// ft_lstiter(commands_list, print_command);
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		// rl_replace_line("", 0);
		printf("\n***: ");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = store_env(envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	init_shell();
	minishell(env);
	// free_env(env);
}
