/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:15:37 by yilin             #+#    #+#             */
/*   Updated: 2024/09/24 15:07:55 by yilin            ###   ########.fr       */
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
	if (pid == -1)
		perror_exit(ERR_FORK, 4); //perr_fork(errno);
	if (pid == 0)//!pid //child process
	{
		close(fd[0]);// Close the read end of the pipe in the child
		dup2(fd[1], STDOUT);// Redirect STDOUT to the write end of the pipe
		close(fd[1]);// Close the write end after redirect
		if (execute_cmds(cmd, envp) < 0)
			perror_exit(ERR_CMD, 6); //exit(6);// OR print error //perr_cmd(char *pathname, int err_n)
<<<<<<< HEAD
	}
	else // Parent process
	{
		close(fd[1]);// Close the write end of the pipe in the parent
		dup2(fd[0], STDIN);// Redirect STDIN to the read end of the pipe		
		close(fd[0]);// Close the read end after redirect
		waitpid(pid, NULL, 0);// Wait for the child process to finish
	}	
=======
			exit(1);//error condocting cmd
		}
	}
	else// Parent process
	{
		//parent process
		close(fd[1]);// Close the write end of the pipe in the parent
		dup2(fd[0], STDIN);// Redirect STDIN to the read end of the pipe
		close(fd[0]);// Close the read end after redirect

		waitpid(pid, NULL, 0);// Wait for the child process to finish
	}
>>>>>>> cb3bbf04db4635dee31c3e2718d5f992fb9eaab8
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
	if (pid == 0)// Child process
	{
		if (execute_cmds(cmd, envp) < 0)
			perror_exit(ERR_CMD, 6);
	}
<<<<<<< HEAD
	else //parent process
	{
		close (STDIN);// Close the parent's STDIN
		close (STDOUT);// Close the parent's STDOUT
		waitpid(pid, NULL, 0);//Optionally wait for the child to finish
=======
	else// Parent process
	{
		waitpid(pid, NULL, 0);// Wait for the child process to finish
		close (STDIN);// Close the parent's STDIN
		close (STDOUT);// Close the parent's STDOUT
>>>>>>> cb3bbf04db4635dee31c3e2718d5f992fb9eaab8
	}
}
