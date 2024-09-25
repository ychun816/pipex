/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:30:06 by thenwood          #+#    #+#             */
/*   Updated: 2024/01/12 14:02:56 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pid
{
	pid_t	pid1;
	pid_t	pid2;
}			t_pid;

int			open_file(char *file, int read_write);
char		**find_path(char **env);
char		*valid_path(char **all_paths, char *cmd);
void		ft_free_tab(char **tab);
int			error_handler(char *str);

#endif