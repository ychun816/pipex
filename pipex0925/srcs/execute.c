/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:34:46 by yilin             #+#    #+#             */
/*   Updated: 2024/09/25 19:57:27 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// get seppath
char	**get_all_seppath(char **env)
{
	
}

// get execute path
char *get_execute_path( , )
{
	
}

// execute cmd
void	execute_cmd(char **env, char *cmd)
{
	
}



#include "pipex.h"

/** GET ALL SEP PATHS : find "PATH="", then seperate into each single path
 * @param *envp[]
 * @param sep_paths seperated paths
 * (1) loop envp[i] -> find matching shell commands in envp
 * (2) if cmd found (use strnstr or strcmp) => seperate paths(ft_split)
 * (3) 
 * 
 * @return sep_paths
 */
char	**get_all_seppaths(char *envp[])
{
	int	i;
	char	**sep_paths;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	sep_paths = ft_split(envp[i] + 5, ':');
	if (!sep_paths)
		return (NULL);
	return (sep_paths);
}

/** GET EXECUTE PATH : append '/' to the cmmnd path
 * @param all_paths 
 * @param valid_path
 * @param execute_path
 * (1) if !envp || is absolute path (find '/') => return dup file
 * (2) retrieve all paths frm PATH environment variable => (get_all_paths())
 * -> this provide array of directories where executables might be located
 * (3) if no path found =>return duped file
 * (4) Iterate through each directory in the PATH.
 * (5) initiaize valid_path / execute_path (strjoin) => free_strs
 * (6) access() -> if not executable | not file exists => free strs(all_paths) + return
 * 
 * @note ft_strdup(file)) ensures returning a newly allocated string, 
 * regardless of the outcome.
 * 1. ensures the caller always gets a string they are responsible for freeing.
 * 2. he returned string will be safely allocated with malloc and can be freed by the caller without impacting the original file
 * 3.  ensures that the returned string is always dynamically allocated and safely managed.
 * @return execute_path  (execute file)
 */
char	*get_execute_path(char **all_paths, char *cmd)
{
	int		i;
	char	*path;
	char	**valid_cmd;
	char	*full_path;



	
}


// char	*get_execute_path(char *file, char *envp[])
// {
// 	int		i;
// 	char	**all_seppaths;
// 	char	*valid_path;
// 	char	*execute_path;
	
// 	if (!envp || is_path_absolute(file) == 1)
// 		return (ft_strdup(file));
// 	all_seppaths = get_all_seppaths(envp);
// 	if (!all_seppaths)
// 		return (ft_strdup(file));
// 	i = -1;
// 	while (all_seppaths[++i])
// 	{
// 		valid_path = ft_strjoin(all_seppaths[i], "/");
// 		all_seppaths[i] = NULL;//is it neccessary?
// 		execute_path = ft_strjoin(valid_path, file);
// 		if (!access(execute_path, X_OK | F_OK))
// 		{
// 			free_strs(all_seppaths); // Free all_seppaths only once here.
// 			return (execute_path);   // Return execute_path directly.
// 		}
// 		free(execute_path);
// 		execute_path = NULL;//do i need to set to NULL here?	
// 	}
// 	free_strs(all_seppaths);//If no valid executable was found, free the array of paths and return a copy of the file
// 	return (ft_strdup(file));
// }


/** EXECUTE
 * @param **cmd : array of arrays to store cmds:
 * cmd[0] = "ls"
 * cmd[1] = "-l"
 * cmd[2] = NULL
 * 
 * (1) Split the input string (av) into an array of strings (cmd)
 * (2) if split commads(i.e. ls -l) fail => return (-1)
 * (3) Get the executable path with 2 command: 
 * 	   (a) if: single cmnd (ie: ls) / (b) else if: cmnd+attached cmnd (ie: ls -l)
 * (4) Check if a valid path found, if not found => free strs => return (-1)
 * (5) Check if a execute path found, if not found => free strs => return (-1)
 * (6) Execute the command -> if execution fails, print error message
 *  -> execve() fail => Free all allocated memory: cmds, execute_path + return (-1)
 *  -> execve() succeed => free all alocated memory + return (0)
 * 
 * @note 
 * execve() : 
 * If execve() succeeds: It replaces the current process image with a new one.
 * If execve() fails: Original process continues executing frm the point right after execve() call.
 * 
 */
int	execute_cmds(char *av, char *envp[])
{
	char	**cmds;
	char	*execute_path;

	// cmds = ft_split_quote(av, ' '); //cmds = ft_split(av, ' ');
	cmds = ft_split(av, ' ');
	if (!cmds)
		return (-1);
	if (cmds[0] == NULL)
		execute_path = get_execute_path(av, envp);
	else
		execute_path = get_execute_path(cmds[0], envp);
	if (!execute_path)
	{
		free_strs(cmds);
		return (-1);
	}
	if (execve(execute_path, cmds, envp) == -1)// if (execve(execute_path, &av, envp) == -1)
	{
		perror_exit(ERR_CMD, 6); //perr_cmd(execute_path, errno);
		free_strs(cmds);
		free(execute_path);
		return (-1);
	}
	free_strs(cmds);// Free allocated memory (but only once, in the parent)
	free(execute_path);
	return (0);
}