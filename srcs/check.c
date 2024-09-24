/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:24:49 by yilin             #+#    #+#             */
/*   Updated: 2024/09/24 16:53:20 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** IS PATH ABSOLUTE
 * (1) Loop through each character of the string path
 * (2) Check if the current character is a forward slash ('/') 
 * 		=> return (1) if found ; return (0) if not found
 */
int is_path_absolute(char *path)
{
	while (*path)
	{
		if (*path == '/') 
			return (1);
		path++;
	}
	return (0);
}

/** CHECK N CLOSE
 * (1) Check if the in_fd valid
 * - invalid => handle false fd
 * - valid => duplicate and close input fd
 * (2) Sets the repeat index to start from the same point.
 * (3) Check if the out_fd valid
 * - invalid => handle false fd
 * - valid => duplicate and close input fd
 */
void check_n_dupclose_fd(int in_fd, int out_fd, int *start, int *out_start)
{
	if (in_fd == -1)
		handle_false_fd(start, 0);
	else
	{
		// dup_n_close(in_fd, STDIN);
		dup2(in_fd, STDIN);//stdin = 0
		close(in_fd);
	}
	*out_start = *start;
	if (out_fd == -1)
		handle_false_fd(out_start, 1);
	else
	{
		// dup_n_close(out_fd, STDOUT); 
		dup2(out_fd, STDOUT);//stdout = 1
		close(out_fd);
	}
}

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
		*index = *index + 1;
	}
	else // if (pipe_mode == 1)//mode == 1 -> WRITE
	{
		dup2(fd[1], STDOUT); //dup_n_close(fd[1], STDOUT);
		close(fd[1]);
		close(fd[0]); // Close the read end of the pipe.
		*index = *index + 1;
	}
}