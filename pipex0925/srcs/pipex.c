/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:29:47 by yilin             #+#    #+#             */
/*   Updated: 2024/09/25 18:14:30 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//execute_cmd()
void	execute_cmd(char **envp, char *cmd)
{
	char	**cmd;
	char	**all_seppaths;
	char	*execute_path;
	
	// Split the command string into an array of arguments
	cmd = ft_split(cmd, ' ');
	if (!cmd)
		retur (NULL);
	// Find the paths from the environment variable "PATH"
	all_seppaths = get_all_seppaths(envp);
	// Find a valid execute path to the command, checking system paths
	execute_path = get_execute_path(;)
	// Execute the command with execve, 
	//replacing the current process image with the new one
	
		// If execve fails, print an error message to stderr

		// Free the allocated memory for the command arguments and the paths

		// Exit with failure since execve failed
				

}


//child process
void	child_process(char **av, int *end, char **envp)
{
	int file;

	// Open the input file (av[1]) in read-only mode (0)
	if (file = open(av[1], O_RDONLY) < 0)
		perr_exit("error_open");
	// Redirect the input from the file (fd) to stdin (0)
	// Redirect stdout (1) to the write end of the pipe (end[1])
	dup2(file, STDIN_FILENO);   //stdin = end[0]
	dup2(end[1], STDOUT_FILENO); //stdout = end[1]

	// Close the read end of the pipe (end[0]), as the child doesn't need it
	// Close the file descriptor for the input file
	close(end[0]);
	close(file);
	
	// Execute the second argument command (av[2]) using the previously defined function
	execute_cmd(envp, av[2]);
}

//parent process
void	parent_process(char **av, int *end, char **envp)
{
	int file;
	
	// Open the output file (av[4]) in write mode (1)
	if (file = open(av[4], O_WRONLY) < 0)
		perr_exit("error_open");

	// Redirect the output to the file by duplicating fd onto stdout (1)
	// Redirect stdin (0) to the read end of the pipe (end[0])
	dup2(file, STDOUT_FILENO); //stdout = file
	dup2(end[0], STDIN_FILENO);

	// Close the write end of the pipe (end[1]), as the parent doesn't need it
	// Close the file (file descriptor) for the output file
	close(end[1]);
	close(file);

	// Execute the third argument command (incomplete; should likely be av[3])
	execute_cmd(envp, av[3]);
}

int	main(int ac, char *av[], char *envp[])
{
	int		fd[2];
	t_pid	pipes;
	
	if (ac == 5)
	{
		if (pipe(fd) < 0)
			perr_exit("error");//error open
		pipes.pid1 = fork();
		if (pipes.pid1 < 0)
			perr_exit("error");//error fork
		if (pipes.pid1 == 0)
			child_process(av, fd, envp);
		pipes.pid2 = fork();
		if (pipes.pid2 == 0)
			parent_process(av, fd envp);
		close(fd[0]);
		close(fd[1]);
		waitpid(pipes.pid1, NULL, 0);
		waitpid(pipes.pid2, NULL, 0);
	}
	else
		perr_exit("error");//error wrong args
	return (0);
}