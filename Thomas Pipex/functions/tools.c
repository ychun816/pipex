/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:47:04 by thenwood          #+#    #+#             */
/*   Updated: 2024/01/17 12:22:04 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_file(char *file, int read_write)
{
	int	fd;

	fd = 0;
	if (read_write == 0)
		fd = open(file, O_RDONLY, 0644);
	else if (read_write == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Open failed :");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**find_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			return (path);
		}
		i++;
	}
	return (path);
}

char	*valid_path(char **all_paths, char *cmd)
{
	int		i;
	char	*path;
	char	**valid_cmd;
	char	*full_path;

	full_path = NULL;
	if (!*cmd)
		return (cmd);
	valid_cmd = ft_split(cmd, ' ');
	i = 0;
	while (all_paths[i])
	{
		path = ft_strjoin(all_paths[i], "/");
		full_path = ft_strjoin(path, valid_cmd[0]);
		free(path);
		if (access(full_path, X_OK | F_OK) == 0)
		{
			ft_free_tab(valid_cmd);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_tab(valid_cmd);
	return (cmd);
}
