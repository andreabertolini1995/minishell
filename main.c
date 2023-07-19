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

t_token *create_token(char *str, int type)
{
    t_token *token;

    token = (t_token *) malloc (sizeof(t_token));
    if (token == NULL)
        return (NULL);
    token->content = str;
    token->type = type;
    // printf("Token content: %s\n", token->content);
    // printf("Token type: %d\n", token->type);
    return (token);
}

int    check_for_operators(char *cmd, int i, t_list **tokens_list)
{
    if ( cmd[i] == '|')
    {
        ft_lstadd_back(tokens_list, ft_lstnew(create_token("|", PIPE)));
        i++;
    }
    else if (cmd[i] == '>')
    {
        if (cmd[i + 1] == '>')
        {
            ft_lstadd_back(tokens_list, ft_lstnew(create_token(">>", R_D_RDIR)));
            i++;
        }
        else
            ft_lstadd_back(tokens_list, ft_lstnew(create_token(">", R_S_RDIR)));
        i++;
    }  
    else if (cmd[i] == '<')
    {
        if (cmd[i + 1] == '<')
        {
            ft_lstadd_back(tokens_list, ft_lstnew(create_token("<<", L_D_RDIR)));
            i++;
        }
        else
            ft_lstadd_back(tokens_list, ft_lstnew(create_token("<", L_S_RDIR)));
        i++;
    }
    return (i);
}

char *create_word(char *cmd, int length, int i)
{
    char       *word;
    int     j;

    word = (char*) malloc (sizeof(char) * length);
    if (word == NULL)
        return (NULL);
    j = 0;
    while (length > 0)
    {
        word[j] = cmd[i - length];
        length--;
        j++;
    }
    return (word);
}

void    print_token(void *content)
{
    t_token *token;

    token = (t_token*) content;
    printf("Content: %s\n", token->content);
    printf("Type: %d\n", token->type);
    printf("\n");
}

int main()
{
    char* cmd;
    size_t     i;
    int     length;
    t_list  *tokens_list;
    char    *word;

    init_shell();
    while (42)
    {
        cmd = readline("*** ");
        i = 0;
        tokens_list = NULL;
        while (cmd[i] != '\0')
        {
            i = check_for_operators(cmd, i, &tokens_list);
            length = 0;
            while (cmd[i] != '|' && cmd[i] != '>' && cmd[i] != '<'
                && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '\0')
            {
                length++;
                i++;
            }
            if (length > 0)
            {
                word = create_word(cmd, length, i);
                ft_lstadd_back(&tokens_list, ft_lstnew(create_token(word, WORD)));
            }
            while (cmd[i] == ' ' || cmd[i] == '\t')
                i++;
        }
        // Test
        ft_lstiter(tokens_list, print_token);
    }
}
