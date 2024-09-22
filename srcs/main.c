/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:13:25 by yilin             #+#    #+#             */
/*   Updated: 2024/09/22 19:41:55 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** HANDLE FALSE FD
 * 
 * @param fd[2] => 
 * - fd[0]: ALWAYS READ!! => The READ end of the pipe.
 * - fd[1]: ALWAYS WRITE!! => The WRITE end of the pipe.
 * 
 * (1) Creates a pipe with 2 file descriptors. | [fd] === [fd]
 * (2) fd == -1 (FAIL) / fd == 0 (FAIL)
 * 
 * @note 
 * In read mode (mode == 0), you are only reading from the pipe using fd[0]. 
 * The write end (fd[1]) is unnecessary and should be closed to:
    1. Signal to the reader that no more data is coming.
    2. Free up system resources.
    3. Ensure proper behavior of the pipe.
 *  
 *  index = index + 1 :
 *  Indicates that it has completed setting up the pipe for the current operation,
 *  and is ready to move on to the next one.
 */
void	handle_false_fd(int *index, int pipe_mode)
{
	int	fd[2];

	if (pipe(fd) == -1) //create pipe => if fail => perr_pipe()
		perror_exit(ERR_PIPE, 2); //perr_pipe(errno);
	if (pipe_mode == 0)//mode == 0 -> READ
	{
		dup2(fd[0], STDIN); //dup_n_close(fd[0], STDIN);
		close(fd[0]);
		close(fd[1]); // Close the write end of the pipe.
		index = index + 1;
	}
	else if (pipe_mode == 1)//mode == 1 -> WRITE
	{
		dup2(fd[1], STDOUT); //dup_n_close(fd[1], STDOUT);
		close(fd[1]);
		close(fd[0]); // Close the read end of the pipe.
		index = index + 1;
	}
}

/** INIT HEREDOC
 * (1) Open the file for writing (truncating if it exists), returns -1 if it fails.
 * (2) Create the limiter string, which is the delimiter (eof) followed by a newline.
 * (3) Read input lines from standard input using get_next_line.
 * (4) loop-> while (input_line)
 * => (a) If the line matches the limiter, stop reading input + free the current line. (use break)
 * => (b) Write the line to the file, if the write fails (< 0) => perr_write()
 * 
 * @return open(file, O_RDONLY)
 * Return the file descriptor for reading from the file (reopen in read-only mode).
 * 
 */
int init_heredoc(char *file, char *eof)
{
	int	fd;
	char	*limiter;
	char	*input_line;
	
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	limiter = ft_strjoin(eof, "\n");
	input_line = get_next_line(STDIN);
	while (input_line)
	{
		if (ft_strcmp(input_line, limiter) == 0)
		{
			free(input_line);
			break ;
		}
		if (write(fd, input_line, ft_strlen(input_line)) < 0)
			perror_exit(ERR_WRITE, 5); //perr_write(errno, file, input_line);
		free(input_line);
		input_line = get_next_line(STDIN); //stdin = 0
	} 
	free(limiter);
	close (fd);
	return (open(file, O_RDONLY));
}

/** INIT_FDS
 * 
 * (1) check if is here_doc => is here_doc
 * // av[1] is "here_doc", and av[2] is the delimiter (EOF marker).
 * // av[ac -1] => last arg-> outfile
 * // Open the output file in append mode since "here_doc" is used.
 * // Commands start at index 3.
 * //av[0] is the program name | av[1] is "here_doc" | av[2] is the delimiter for the heredoc
 * (2) not here_doc, regular files
 * // For regular files, open input in read-only / output in write/truncate mode.
 * //av[0] is the program name | av[1] is input file
 * //av[0] is the program name | av[1] is input file
 * (3) Check if file opening fail: in_fd / out_fd / 

 * @note FLAGS
 * O_WRONLY : writing only
 * O_CREAT : If the specified file (i.e., av[ac - 1]) does not exist, 
 * 			this flag instructs the system to create the file
 * O_APPEND : Ensures that new data is added to the end of the file (appended) 
 * 0644 : 
 * - 0: The first digit (most significant) is always 0
 * - 6 (owner permission): 
 * 		The owner of the file can read (4) and write (2) to the file. 
 * 		6 = 4 + 2 (read + write permissions for the owner).
 * - 4 (group permission): 
 * 		Members of the file’s group can only read the file (no write permission).
 * - 4 (others permission): All other users can only read the file.
 * 
 */
int	init_fds(int *in_fd, int *out_fd, int ac, char *av[])
{
	int	i;
	
	i = 0;
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		*in_fd = init_heredoc(av[1], av[2]);
		*out_fd = open(av[ac -1], O_WRONLY | O_CREAT | O_APPEND, 0644); 
		i = 3;
	}
	else
	{
		*in_fd = open(av[1], O_RDONLY);
		*out_fd = open(av[ac - 1], O_CREAT | O_TRUNC, 0644);
		i = 2;
	}
	if (*in_fd == -1)
		perror_exit(ERR_OPEN, 3); //perr_open(errno, av[1]);
	if (*out_fd == -1)
		perror_exit(ERR_OPEN, 3); //perr_open(errno, av[ac -1]);
	return (i);
}

/** MAIN
 * @param int in_fd : pipe[1]
 * @param int out_fd : pipe[2]
 * @param int i : Counter for processing arguments
 * @param int j : Another counter for waiting on child processes
 * 
 * (1) Check argument count: at least 5 args required, or 6 if 'here_doc' is first argument
 * (2) Initialize file descriptors for input and output, setting 'i' based on here_doc
 * -> Returns the starting index for commands.
 * (3) Check if file descriptors are valid and set 'i' and 'j' for iteration
 * -> Verifies if the file descriptors are valid and sets start/repetition indexes.
 * (4) Loop through arguments (likely commands), do_pipe(): creating pipes and executing commands
 * (5) If output file descriptor is valid, execute the final command
 * (6) Special handling for the last command. => fork()
 * (7) 	Wait for all child processes to finish
 * (8) 	If here_doc was used, unlink (remove) the file
 * 
 * @note 
 */
int	main (int ac, char *av[], char *envp[])
{
	int in_fd;
	int out_fd;
	int i;
	int j;

	if (ac < 5 || (ft_strcmp(av[1], "here_doc") == 0 && ac < 6))
		perror_exit(ERR_AC, 1); //perr_ac(ac);///
	i = init_fds(&in_fd, &out_fd, ac, av);
	check_n_dupclose_fd(in_fd, out_fd, &i, &j);
	while (i < ac - 2)
	{
		do_pipe(av[i], envp);
		i++;
	}
	if (out_fd != -1)
		do_fork_main(av[i], envp);
	while(j < ac - 1)
	{
		wait(NULL);
		j++;
	}
	if (ft_strcmp(av[1], "here_doc") == 0) 
		unlink(av[1]);
	return (0);
}

