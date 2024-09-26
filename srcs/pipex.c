/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:29:47 by yilin             #+#    #+#             */
/*   Updated: 2024/09/26 19:51:01 by yilin            ###   ########.fr       */
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
void	child1_process(char **av, int *end, char *envp[])
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		close(end[0]);
		close(end[1]);
		perr_exit("Error in opening", ERRNO_OPEN);
	}
	dup2(fd, STDIN);
	close(fd);
	close(end[0]);
	dup2(end[1], STDOUT);
	close(end[1]);
	execute_cmd(envp, av[2]);//execute(argv[2], env);
}

/** PARENT PROCESS
 * Open the output file (av[4]) in write mode (1)
 * Redirect the output to the file by duplicating fd onto stdout (1)
 * Redirect stdin (0) to the read end of the pipe (end[0])
 * Close the write end of the pipe (end[1]), as the parent doesn't need it
 * Close the file (file descriptor) for the output file
 * Execute the third argument command (incomplete; should likely be av[3])
 * */
void	child2_process(char **av, int *end, char *envp[])
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(end[0]);
		close(end[1]);
		perr_exit("Error in opening", ERRNO_OPEN);
	}
	dup2(fd, STDOUT);
	close(fd);
	close(end[1]);
	dup2(end[0], STDIN);
	close(end[0]);
	execute_cmd(envp, av[3]);//execute(argv[3], env);
}

int	main(int ac, char *av[], char *envp[])
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int	status;

	if (ac != 5)
		perr_exit_str(ERR_AC, ERRNO_AC);
	if (pipe(fd) == -1)
		perr_exit("PIPE : ", ERRNO_PIPE);
	pid1 = fork();
	if (pid1 == -1)
		perr_exit("FORK : ", ERRNO_FORK);//Error in fork process 1
	if (pid1 == 0)
		child1_process(av, fd, envp);
	pid2 = fork();
	if (pid2 == -1)
		perr_exit("FORK : ", ERRNO_FORK);//Error in fork process 2
	if (pid2 == 0)
		child2_process(av, fd, envp);
	close(fd[0]);
	close(fd[1]);
	status = 0;
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (EXIT_SUCCESS);
}

/* OTHER STRUCTURE
int exec()//1 cmd
{
	int	fd[2];
	t_pid	pid;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		//child
		close(fd[0]);
		dup2(fd[1], STDOUT);
		close(fd[1]);
		// redirection, close fds....
		
	}
	wait(NULL);
	close(fd[1]);
	dup2(fd[0], STDIN);
	close(fd[0]);
	// redirection
}
*/
