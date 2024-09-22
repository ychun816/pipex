#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h> //file manipulation like open(), creat(), fcntl(), file descriptors(fd)
# include <sys/wait.h> //wait() and waitpid() functions
# include <errno.h> //Defines macros for reporting and retrieving error conditions

# include <limits.h> //Defines constants for sizes of integral types, Provides minimum and maximum values for various data types
# include <stdint.h> //Defines fixed-width integer types and their limits, Provides types like int8_t, uint32_t, etc.
# define STDOUT STDOUT_FILENO
# define STDIN STDIN_FILENO
# define STDERR STDERR_FILENO
# define ERR_AC "ERROR: NOT ENOUGH ARGS"
# define ERR_PIPE "ERROR: PIPE FAIL"
# define ERR_OPEN "ERROR: OPEN FAIL"
# define ERR_FORK "ERROR: FORK FAIL"
# define ERR_WRITE "ERROR: WRITE FAIL"
# define ERR_CMD "ERROR: COMMAND FAIL"
// # define P_NAME "pipex"

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

typedef enum e_error
{
TRUE = 0,
FALSE = 1,
}t_error;

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

/*main*/
void	handle_false_fd(int *index, int pipe_mode);
int	init_heredoc(char *file, char *eof);
int	init_fds(int *in_fd, int *out_fd, int ac, char *av[]);
/*pipe fork*/
void	do_pipe(char *cmd, char *envp[]);
void	do_fork_main(char *cmd, char *envp[]);
/*check*/
int	is_path_absolute(char *path);
void check_n_dupclose_fd(int in_fd, int out_fd, int *start, int *out_start);
/*execute*/
char	**get_all_seppaths(char *envp[]);
char	*get_execute_path(char *file, char *envp[]);
int	execute_cmds(char *av, char *envp[]);
/*helper*/
void	free_strs(char **strs);
void	dup_n_close(int fd, int new_fd);


void	perror_exit(char *err_message, int err_n);
char	**ft_split_quote(char const *s, char c);
/*print error*/
// void	perr_ac(int ac);
// void	perr_pipe(int err_n);
// void	perr_open(int err_n, char *filename);
// void	perr_fork(int err_n);
// void	perr_write(int err_n, char *filename, char *line);
// void	perr_cmd(char *pathname, int err_n);

#endif