/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:33:38 by yilin             #+#    #+#             */
/*   Updated: 2024/09/25 17:55:18 by yilin            ###   ########.fr       */
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
			strs[i] = NULL;
		}
		i++;
	}
	free(strs);
}
// void	ft_free_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }

/** OPEN FILE
 * - O_CREAT: Create the file if it doesn't exist.
 * - O_WRONLY: Open for writing only.
 * - O_TRUNC: If the file exists, truncate it to 0 length.
 * 
*/
int	open_file(char *file, int read_write)
{
	int	fd;

	fd = 0;
	// If 'read_write' is 0, open the file in read-only mode (O_RDONLY).
	if (read_write == 0)
		fd = open(file, O_RDONLY, 0644);
	// If 'read_write' is 1, open the file in write mode. 
	else if (read_write == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// If the 'open' call fails (fd == -1), print an error message and exit the program.
	if (fd == -1)
	{
		perror("OPEN FAIL :");
		exit(EXIT_FAILURE);
	}
	// Return the file descriptor (fd), which is used for file operations.
	return (fd);
}

/**PERR_EXIT
 * 
 * */
void	perr_exit(char *err_msg, int err_n)
{
	perror(err_msg);
	exit(err_n);
}
