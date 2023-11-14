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

int g_signal_num;

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		// rl_replace_line("", 0); // necessary?
		g_signal_num = SIGINT;
		if (g_blocking_command == true)
		{
			printf("\n");
			g_blocking_command = false;
		}
		else
			printf("\n***: ");
	}
}

void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		if (g_blocking_command == true)
		{
			printf("Quit (core dumped)\n");
			g_blocking_command = false;
			g_signal_num = SIGQUIT;
		}
		else
			signal(SIGQUIT, SIG_IGN);
	}
}
