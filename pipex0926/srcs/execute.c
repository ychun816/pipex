/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:34:46 by yilin             #+#    #+#             */
/*   Updated: 2024/09/26 15:55:16 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** GET ALL SEP PATHS : find "PATH="", then seperate into each single path
 *
 * @note use strcmp() is better than strnstr():
 * - strnstr() might search through more of the string than necessary,
 *   since it checks for a substring anywhere.
 * - strncmp() stops comparing after the first 5 characters,
 *   so it’s potentially more efficient in this specific case.
 *
 * @return sep_paths
 */
char	**get_all_seppaths(char *envp[])
{
	int		i;
	char	**sep_paths;

	i = 0;
	sep_paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			sep_paths = ft_split(envp[i] + 5, ':');
			return (sep_paths);
		}
		i++;
	}
	return (NULL);
}

/** GET EXECUTE PATH
 * (1) If command empty, return command itself
 * (2) Split command into tokens (assuming the first token is executable name)
 * (3) Loop (all_seeppaths) to find a valid executable
 * (4) Strjoin all_seppaths[i] with '/' => create a directory string
 * (5) Strjoin first part of the command (valid_cmd[0]) => form execute_path
 * (6) Free tmp path as it's no longer needed.
 * (7) Check if the execute_path exists and executable
 * (8) Free char** / char * if no needed anymore
 * 
 * @note if (access(execute_path, X_OK | F_OK) == 0)
 * -> found an executable file at the given path
 * @note execute_path = NULL;
 * -> Defensive programming practice that helps to prevent errors
 * 
 * @return the original command if no valid executable was found
 */
char	*get_execute_path(char **all_seppaths, char *cmd)
{
	int		i;
	char	*execute_path;
	char	*tmp_append;
	char	**valid_cmd;

	i = 0;
	execute_path = NULL;
	if (!*cmd)
		return (cmd);
	valid_cmd = ft_split(cmd, ' ');
	while (all_seppaths[i])
	{
		tmp_append = ft_strjoin(all_seppaths[i], "/");
		execute_path = ft_strjoin(tmp_append, valid_cmd[0]);
		free(tmp_append);
		if (access(execute_path, X_OK | F_OK) == 0)
		{
			free_strs(valid_cmd);
			return (execute_path);
		}
		free(execute_path);
		i++;
	}
	free_strs(valid_cmd);
	return (cmd);
}

/** EXECUTE CMD
 * @param **cmd : array of arrays to store cmds:
 * cmd[0] = "ls"
 * cmd[1] = "-l"
 * cmd[2] = NULL
 *
 * Execute the command with execve,
 * replacing the current process image with the new one
 *
 * If execve fails, print an error message to stderr
 * Free the allocated memory for the command arguments and the paths
 * Exit with failure since execve failed
 *
 * @note
 * execve() :
 * If execve() succeeds: It replaces the current process image with a new one.
 *
 */
void	execute_cmd(char *envp[], char *cmd)
{
	char	**all_seppaths;
	char	**valid_cmd;
	char	*execute_path;

	valid_cmd = ft_split(cmd, ' ');
	all_seppaths = get_all_seppaths(envp);
	execute_path = get_execute_path(all_seppaths, cmd);
	if (execve(execute_path, valid_cmd, envp) == -1)
	{
		ft_putstr_fd("COMMAND NOT FOUND : ", STDERR);
		ft_putendl_fd(valid_cmd[0], STDERR);
		free_strs(valid_cmd);
		free_strs(all_seppaths);
		exit(EXIT_FAILURE);
	}
}
