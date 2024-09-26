/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:29:47 by yilin             #+#    #+#             */
/*   Updated: 2024/09/26 15:31:06 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** CHILD PROCESS
 * Open the input file (av[1]) in read-only mode (0)
 * Redirect the input from the file (fd) to stdin (0)
 * Redirect stdout (1) to the write end of the pipe (end[1])
 * Close the read end of the pipe (end[0]), as the child doesn't need it
 * Close the file descriptor for the input file
 * Execute the second argument command (av[2])
 * 
 * @note stdin = end[0]
 * @note stdout = end[1]
*/
void	child_process(char **av, int *end, char *envp[])
{
	int	file;

	file = open_file(av[1], O_RDONLY);
	dup2(file, STDIN);
	dup2(end[1], STDOUT);
	close(end[0]);
	close(file);
	execute_cmd(envp, av[2]);
}

/** PARENT PROCESS
 * Open the output file (av[4]) in write mode (1)
 * Redirect the output to the file by duplicating fd onto stdout (1)
 * Redirect stdin (0) to the read end of the pipe (end[0])
 * Close the write end of the pipe (end[1]), as the parent doesn't need it
 * Close the file (file descriptor) for the output file
 * Execute the third argument command (incomplete; should likely be av[3])
 * */
void	parent_process(char **av, int *end, char *envp[])
{
	int	file;

	file = open_file(av[4], O_WRONLY);
	dup2(file, STDOUT);
	dup2(end[0], STDIN);
	close(end[1]);
	close(file);
	execute_cmd(envp, av[3]);
}

int	main(int ac, char *av[], char *envp[])
{
	int		fd[2];
	t_pid	pipes;

	if (ac == 5)
	{
		if (pipe(fd) < 0)
			perr_exit("PIPE : ", ERRNO_PIPE);
		pipes.pid1 = fork();
		if (pipes.pid1 < 0)
			perr_exit("FORK : ", ERRNO_FORK);
		if (pipes.pid1 == 0)
			child_process(av, fd, envp);
		pipes.pid2 = fork();
		if (pipes.pid2 < 0)
			perr_exit("FORK : ", ERRNO_FORK);
		if (pipes.pid2 == 0)
			parent_process(av, fd, envp);
		close(fd[0]);
		close(fd[1]);
		waitpid(pipes.pid1, NULL, 0);
		waitpid(pipes.pid2, NULL, 0);
	}
	else
		perr_exit_str(ERR_AC, ERRNO_AC);
	return (EXIT_SUCCESS);
}
