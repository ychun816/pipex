/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:33:38 by yilin             #+#    #+#             */
/*   Updated: 2024/09/26 19:52:52 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** FREE STRS
 * @note !! Remember to set NULL to pointer, Otherwise weird behavior
*/
void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		if (strs[i] == NULL)
		{
			free(strs[i]);
			strs[i++] = NULL;
		}
	}
	free(strs);
	strs = NULL;
}
/*
void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i++] = NULL;
	}
	free(str);
	str = NULL;
}*/

/** OPEN FILE
 * 
 * If 'read_write' is 0, open the file in read-only mode (O_RDONLY).
 * If 'read_write' is 1, open the file in write mode. 
 * If the 'open' call fails (fd == -1), print error message + exit.
 * Return the file descriptor (fd)-> for file operations.
 * 
 * - O_CREAT: Create the file if it doesn't exist.
 * - O_WRONLY: Open for writing only.
 * - O_TRUNC: If the file exists, truncate it to 0 length.
 * 
*/
int	open_file(char *file, int read0_write1)
{
	int	fd;

	fd = 0;
	if (read0_write1 == 0)
		fd = open(file, O_RDONLY, 0644);
	else if (read0_write1 == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perr_exit("OPEN FAILED ", ERRNO_OPEN);
	return (fd);
}

/**PERR_EXIT
*/
void	perr_exit(char *err_msg, int err_n)
{
	perror(err_msg);
	exit(err_n);
}

void	perr_exit_str(char *err_msg, int err_n)
{
	ft_putstr_fd(err_msg, STDERR);
	exit(err_n);
}
/* REF
int	error_handler(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	error_handler2(char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}
*/