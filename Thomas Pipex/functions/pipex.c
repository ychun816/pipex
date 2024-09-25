/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:29:50 by thenwood          #+#    #+#             */
/*   Updated: 2024/09/25 16:07:32 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_cmd(char **env, char *cmd)
{
	char	*path;
	char	**valid_cmd;
	char	**find_the_path;

	valid_cmd = ft_split(cmd, ' ');
	find_the_path = find_path(env);
	path = valid_path(find_the_path, cmd);
	if (execve(path, valid_cmd, env) == -1)
	{
		ft_putstr_fd("Command not found : ", 2);
		ft_putendl_fd(valid_cmd[0], 2);
		ft_free_tab(valid_cmd);
		ft_free_tab(find_the_path);
		exit(EXIT_FAILURE);
	}
}

void	child_process(char **av, int *end, char **env)
{
	int	fd;

	fd = open_file(av[1], 0);
	dup2(fd, 0);
	dup2(end[1], 1);
	close(end[0]);
	close(fd);
	execute_cmd(env, av[2]);
}

void	parent_process(char **av, int *end, char **env)
{
	int	fd;

	fd = open_file(av[4], 1);
	dup2(fd, 1);
	dup2(end[0], 0);
	close(end[1]);
	close(fd);
	execute_cmd(env, av[3]);
}

int	main(int ac, char **av, char **env)
{
	t_pid	pipex;
	int		tube[2];

	if (ac == 5)
	{
		if (pipe(tube) < 0)
			error_handler("PIPE :");
		pipex.pid1 = fork();
		if (pipex.pid1 < 0)
			error_handler("FORK :");
		if (!pipex.pid1)
			child_process(av, tube, env);
		pipex.pid2 = fork();
		if (pipex.pid2 < 0)
			error_handler("FORK :");
		if (!pipex.pid2)
			parent_process(av, tube, env);
		close(tube[0]);
		close(tube[1]);
		waitpid(pipex.pid1, NULL, 0);
		waitpid(pipex.pid2, NULL, 0);
	}
	else
		error_handler("Invalid argument(s) !");
	exit(EXIT_SUCCESS);
}
