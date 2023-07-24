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

int takeInput()
{
    char* cmd;
    char *path_cmd;
    char *argv[2];
	char *envp[2];

    cmd = readline(">>> ");
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
