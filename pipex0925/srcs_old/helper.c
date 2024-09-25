/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:29:59 by yilin             #+#    #+#             */
/*   Updated: 2024/09/25 14:59:13 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** free strs
 * @note !! Remember to set NULL to pointer, Otherwise weird behavior
*/
void free_strs(char **strs)
{
    int i = 0;
    if (!strs)
        return;
    while (strs[i])
    {
        free(strs[i]);
        strs[i] = NULL;
        i++;
    }
    free(strs);
    strs = NULL;
}
// void	free_strs(char **strs)
// {
// 	int	i;
	 
// 	i = 0;
// 	if (!strs)
// 		return ;
// 	while (strs[i])
// 	{
// 		if (strs[i] == NULL)
// 		{
// 			free(strs[i]);
// 			strs[i] = NULL;
// 		}
// 		i++;
// 	}
// 	free(strs);
// }

/** perror n exit
 * 
 * */
void perror_exit(const char *msg, int exit_code)
{
    perror(msg);
    exit(exit_code);
}
// void	perror_exit(char *err_message, int err_n)
// {
// 	// perror(err_message);
// 	ft_putstr_fd(err_message, STDERR_FILENO);
// 	exit(err_n);
// }

// /** DUP N CLOSE
//  */
// void	dup_n_close(int fd, int new_fd)
// {
// 	dup2(fd, new_fd);
// 	close(fd);
// }