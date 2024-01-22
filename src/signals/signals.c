/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <eltongid@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:19:57 by eltongid          #+#    #+#             */
/*   Updated: 2023/12/17 11:37:58 by eltongid         ###   ########.fr       */
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
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_signal_num = SIGINT;
}

void	sigint_handler_heredoc1(int signum) //second function for heredoc
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	g_signal_num = SIGINT;
}

void	sigint_blocking_cmd_handler(int signum)
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
