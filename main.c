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

void clear()
{
    // Clearing the shell using escape sequences
    printf("\033[H\033[J");
}
  
void init_shell()
{
    printf("\n\n\n\n******************"
        "************************");
    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\n\n*******************"
        "***********************");
    // char* username = getenv("USER");
    // printf("\n\n\nUSER is: @%s", username);
    printf("\n");
    sleep(3);
    clear();
}
  
int takeInput()
{
    char* cmd;
    char *path_cmd;
    char *argv[2];
	char *envp[2];

    cmd = readline("!!!! ");
    printf("Prompt: %s\n", cmd);
    argv[0] = cmd;
    argv[1] = NULL;
    envp[0] = "/bin";
    envp[1] = NULL;
    if (ft_strlen(cmd) != 0)
    {
        add_history(cmd);
        path_cmd = combine_path_cmd(cmd);
        if (execve(path_cmd, argv, envp) == -1)
            perror("Could not execve.");
        return 0;
    } else {
        return 1;
    }
}

int main()
{
    // init_shell();

    // while (42) {
    //     // Reading input continously from the shell
    //     if (takeInput())
    //         continue;
    // }
    char *tokens[5] = {"ls", "-al", "|", "grep", "me"};
    t_command   *cmd_list;

    cmd_list = parser(tokens);
    while (cmd_list != NULL)
    {
        printf("Command: %s\n", cmd_list->cmd);
        printf("Arguments: %s\n", cmd_list->arg);
        printf("Operator: %s\n", cmd_list->operator);
        printf("\n");
        cmd_list = cmd_list->next;
    }
}
