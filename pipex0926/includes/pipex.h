/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:46:47 by yilin             #+#    #+#             */
/*   Updated: 2024/09/26 15:53:30 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
/*file manipulation like open(), creat(), fcntl(), file descriptors(fd)*/
# include <fcntl.h>
/*wait() and waitpid() functions*/
# include <sys/wait.h>
/*Defines macros for reporting and retrieving error conditions*/
# include <errno.h> 

/*Provides minimum and maximum values for various data types*/
# include <limits.h>
/*Provides types like int8_t, uint32_t, etc.*/
# include <stdint.h> 
# define STDOUT STDOUT_FILENO
# define STDIN STDIN_FILENO
# define STDERR STDERR_FILENO

# define ERR_AC "ERROR: WRONG NUMBER OF ARGS\n"
// # define ERR_CMD "ERROR: COMMAND NOT FOUND : \n"

# define ERRNO_AC 1
# define ERRNO_PIPE 2
# define ERRNO_FORK 3
# define ERRNO_OPEN 4
# define ERRNO_CMD 5
// # define ERRNO_WR 5

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

typedef enum e_error
{
	TRUE = 0,
	FALSE = 1,
}	t_error;

typedef struct s_pid
{
	pid_t	pid1;
	pid_t	pid2;
}			t_pid;

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

/*pipex*/
void	child_process(char **av, int *end, char **envp);
void	parent_process(char **av, int *end, char **envp);

/*execute*/
char	**get_all_seppaths(char *envp[]);
char	*get_execute_path(char **all_seppaths, char *cmd);
void	execute_cmd(char *envp[], char *cmd);

/*helper*/
void	free_strs(char **strs);
int		open_file(char *file, int read0_write1);
void	perr_exit(char *err_msg, int err_n);
void	perr_exit_str(char *err_msg, int err_n);

#endif