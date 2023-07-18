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

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	int	i;
	int	nb;

	nb = n;
	i = 0;
	while (i < nb && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < nb)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

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

int main()
{
    char *path_cmd;
    char *argv[2];
	char *envp[2];

    argv[0] = "ls";
    argv[1] = NULL;
    envp[0] = "/bin";
    envp[1] = NULL;
    path_cmd = combine_path_cmd("ls");
    printf("Path cmd: %s\n", path_cmd);
    if (execve(path_cmd, argv, envp) == -1)
        perror("Could not execve.");   
}
