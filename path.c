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

char	*combine_path_cmd(char *cmd)
{
	char *path;
	char *path_cmd;

	path = "/bin/";
	path_cmd = (char*) malloc (sizeof(char) * (ft_strlen(path) + ft_strlen(cmd)));
	if (path_cmd == NULL)
		return (NULL);
	path_cmd = ft_strncpy(path_cmd, path, ft_strlen(path));
	path_cmd = ft_strcat(path_cmd, cmd);
	return (path_cmd);
}