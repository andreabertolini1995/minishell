/* Simple example of a program searching for an executable in the 
	computer and execute it. */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

char	*ft_strcat(char *dest, char *src)
{
	int	dest_len;
	int	i;

	dest_len = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

int main()
{
	char *cmd;
	char *path;
	char *path_cmd;
	char *argv[2] = {"ls", `NULL};
	char *envp[2] = {"/bin", NULL};
	
	cmd = "/ls";
	path = "/bin";
	// Find a better solution to copy concatenate the two strings.
	// Current idea is to use ft_concat but need to probbaly use ft_strncpy before too
	path_cmd = (char*) malloc (sizeof(char) * (ft_strlen(path) + ft_strlen(cmd)));
	if (path_cmd == NULL)
		return (1);
	path_cmd = ft_strcat(path, cmd);
	printf("%s", path);
	if (execve(path, argv, envp) == -1)
		perror("Could not execve.");
	return (0);
}