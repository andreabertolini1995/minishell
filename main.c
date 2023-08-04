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

#include "minishell.h"

void init_shell()
{
    printf("\n           _       _     _          _ _");
    printf("\n _ __ ___ (_)_ __ (_) __| |_    ___| | |");
    printf("\n|  _   _ \\| |  _ \\| / __|  _ \\ / _ \\ | |");
    printf("\n| | | | | | | | | | \\__ \\ | | |  __/ | |");
    printf("\n|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|");
    printf("\n\n");
    printf("         by abertoli & shurlebu\n\n");
    sleep(1);
    printf("\033[H\033[J");
}

int main()
{
    char* cmd;
    t_list  *tokens_list;
    t_list  *commands_list;
    int     status_code;

    init_shell();
    status_code = 0;
    while (42)
    {
        cmd = readline("minishell: ");
        add_history(cmd);
        tokens_list = lexer(cmd);
        commands_list = parser(tokens_list, status_code);
        status_code = executor(commands_list);
        // Lexer test
        // ft_lstiter(tokens_list, print_token);
        // Parser test
        // ft_lstiter(commands_list, print_command);
    }
}
