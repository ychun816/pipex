/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:04:35 by thenwood          #+#    #+#             */
/*   Updated: 2024/01/12 14:05:30 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
