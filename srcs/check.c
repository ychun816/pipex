/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:24:49 by yilin             #+#    #+#             */
/*   Updated: 2024/09/22 17:30:35 by yilin            ###   ########.fr       */
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