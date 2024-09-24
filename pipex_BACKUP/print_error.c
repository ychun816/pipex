/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:15:32 by yilin             #+#    #+#             */
/*   Updated: 2024/09/24 16:33:50 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//perror_ac
void	perr_ac(int ac)
{
	dup2(STDERR, STDOUT);
	ft_printf("%s: NOT ENOUGH ARGS! ONLY %d ARGS GIVEN.\n", "pipex", ac - 1);
	exit(1);		
}
// void	perr_ac(int ac)
// {
// 	// dup2(STDERR, STDOUT);
// 	ft_putstr_fd("Wrong Number of Args\n", STDERR_FILENO);
// 	exit(1);		
// }
//perror_pipe
void	perr_pipe(int err_n)
{
	dup2(STDERR, STDOUT);
	ft_printf("%s: %s\n", "pipex", strerror(err_n)); //strerror
	exit(2);
}
//perror_open
void	perr_open(int err_n, char *filename)
{
	dup2(STDERR, STDOUT);
	ft_printf("%s: %s: %s\n", "pipex", strerror(err_n), filename);
	exit(3);
}
//perror_fork
void	perr_fork(int err_n)
{
	dup2(STDERR, STDOUT);
	ft_printf("%s: %s\n", "pipex", strerror(err_n));
	exit(4);
}
//perror_write
void	perr_write(int err_n, char *filename, char *line)
{
	if (line)
		free (line);
	dup2(STDERR, STDOUT);
	ft_printf("%s: %s: %s\n", "pipex", strerror(err_n), filename);
	exit(5);
}

//perror_cmd
void perr_cmd(char *pathname, int err_n)
{
	dup2(STDERR, STDOUT);
	if (is_path_absolute(pathname) == 1)
		ft_printf("%s: %s: %s\n", "pipex", strerror(err_n), pathname);
	else
		ft_printf("%s: command not found: %s\n", "pipex", strerror(err_n), pathname);
	exit(6);
}
