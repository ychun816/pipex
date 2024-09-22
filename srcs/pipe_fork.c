/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:15:37 by yilin             #+#    #+#             */
/*   Updated: 2024/09/22 19:06:36 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** DO PIPE
 * (1) Create a pipe for communication between processes, if fail => print error
 * (2) Fork a new process 
 * => if fork() fail (-1) => print error
 * => if fork() success (0) =>
 *    (a) Close the reading end of the pipe.
 *    (b) dup write end to stdout + close
 * (3) Execute the command, If fail => exit? OR print error
 * (4) Close the writing end of the pipe.
 * (5) Dup pipe's reading end to STDIN. + close
 * 
 * @note
 * In the child process: pid == 0
 * In the parent process: pid == 0

 */
void	do_pipe(char *cmd, char *envp[])
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		perror_exit(ERR_PIPE, 2); //perr_pipe(errno);
	pid = fork();
	if (fork() == -1)
		perror_exit(ERR_FORK, 4); //perr_fork(errno);
	if (pid == 0)//!pid
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);// dup_n_close(fd[1], STDOUT);
		close(fd[1]);
		if (execute_cmds(cmd, envp) < 0)
		{
			perror_exit(ERR_CMD, 6); //exit(6);// OR print error //perr_cmd(char *pathname, int err_n)
			exit(1);//error condocting cmd
		}
			
	}
	close(fd[1]);
	dup2(fd[0], STDIN);// dup_n_close(fd[0], STDIN);
	close(fd[0]);
}

/** DO FORK MAIN
 * (1) Fork the process to handle the last command. => Print Error if fork fails.
 * (2) In the child process: pid == 0
 * => > Execute the command  => Print Error if command fails.
 * (3) In the parent process:
 * => close input file descriptors + output file descriptors
 * 
 */
void	do_fork_main(char *cmd, char *envp[])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror_exit(ERR_FORK, 4); //perr_fork(errno);
	if (pid == 0)
	{
		if (execute_cmds(cmd, envp) < 0)
		{
			// exit(6); //OR print error //perr_cmd(char *pathname, int err_n)
			perror_exit(ERR_CMD, 6);
			exit(1);
		}
	}
	close (STDIN);
	close (STDOUT);
}