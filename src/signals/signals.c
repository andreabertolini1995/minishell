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

int	g_signal_num;

void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_num = SIGINT;
}

void	sigint_handler_heredoc(int signum)
{
	(void)signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_signal_num = SIGINT;
}

void sigint_blocking_cmd_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_signal_num = SIGINT;
}

void	sigquit_handler(int signum)
{
	(void)signum;
	printf("Quit (core dumped)\n");
	g_signal_num = SIGQUIT;
}
