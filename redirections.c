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

// bool    to_redirect(t_list *commands_list)
// {
//     t_command   *command;

//     while (commands_list != NULL)
//     {
//         command = commands_list->content;
//         if (command->operator != NULL)
//         {
//             // Assuming there is only one redirection at the end 
//             if (!ft_strncmp(command->operator, ">", ft_strlen(command->operator)))
//                 return (true);
//         }
//         commands_list = commands_list->next;
//     }
//     return (false);
// }

char *get_name_outfile(t_list *commands_list)
{
    t_command   *command;
    t_command   *next_command;

    while (commands_list != NULL)
    {
        command = commands_list->content;
        if (command->operator != NULL)
        {
            // Assuming there is only one redirection at the end 
            if (!ft_strncmp(command->operator, ">", ft_strlen(command->operator)))
            {
                next_command = commands_list->next->content;
                return (next_command->cmd);
            }
        }
        commands_list = commands_list->next;
    }
    return (NULL);
}

int    redirect_output(char *file_name)
{
    int file;
    int file2;
    
    file = open(file_name, O_WRONLY | O_CREAT, 0777); // change the name of the file accordingly
    file2 = dup2(file, STDOUT_FILENO);
    close(file);
    return (file2);
}