/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:29:59 by yilin             #+#    #+#             */
/*   Updated: 2024/09/22 19:40:18 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// free strs
void	free_strs(char **strs)
{
	int	i;
	 
	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

//perror n exit
void	perror_exit(char *err_message, int err_n)
{
	perror(err_message);
	exit(err_n);
}

// /** DUP N CLOSE
//  */
// void	dup_n_close(int fd, int new_fd)
// {
// 	dup2(fd, new_fd);
// 	close(fd);
// }

//split quote? 