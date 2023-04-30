/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:44:50 by root              #+#    #+#             */
/*   Updated: 2023/03/20 09:36:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h> //printf
# include "../sources/gnl/get_next_line.h"
# include <stddef.h> //write
# include <stdlib.h>   //malloc
# include <unistd.h> //pipe
# include <sys/types.h> //open
# include <sys/stat.h> //open
# include <fcntl.h> //open
# include <sys/wait.h> //waitpid
# include <errno.h>

typedef struct s_pipex
{
	char	**paths;
	char	***commands;
	char	*cmd;
	int		fd1;
	int		fd2;
	int		err_fd1;
	int		err_fd2;
	int		nb_cmds;
	int		commands_were_malloced;
	int		*argv_x_size;
	int		**pipe;
	int		*forks_id;
	int		there_is_here_doc;
	char	*limiter;
	int		*pipe_heredoc;
	int		fork_here;
	int		temp_fork_heredoc;
	char	**envp;
	char	**argv;
	char	*buffer;
	char	*buffer2;
	char	*temp;
	int		y;
	int		loops;

}	t_pipex;

/* MAIN.C */

int		main(int argc, char **argv, char **envp);
void	ft_pipex(int argc, char **argv, char **envp);
void	ft_pipex_initialisation(t_pipex *p);
void	ft_here_doc_one_command(t_pipex *p, char **argv, char **envp);

/* ERROR.C */

int		ft_command_check(t_pipex *p, int i);
int		ft_command_check_part2(t_pipex *p, int i, int return_value);

/* FDS.C */

void	ft_get_fds(t_pipex *p, char **argv, int argc);
void	ft_fd2_open_error(char **argv, int argc, t_pipex *p);

/* FORKING.C */

void	ft_forking(t_pipex *p, char **envp, char **argv);
void	ft_first_fork(t_pipex *p, char **envp, int i);
void	ft_fork_loop(t_pipex *p, char **envp, int i);
void	ft_last_fork(t_pipex *p, char **envp, int i);
void	ft_close_pipes(int i, t_pipex *p);

/* FREE.C */

void	ft_free_commands(t_pipex *p);
void	ft_free_paths(t_pipex *p);
void	ft_free_pipes(t_pipex *p);
void	ft_free_exit_pipex(char *message, t_pipex *p, int exit_code);

/* FT_SPLIT.C*/

char	**ft_split(char *s, char c);

/* HEREDOC.C */

void	ft_here_doc(t_pipex *p, char **envp, char **argv);
void	ft_input_loop_heredoc(t_pipex *p);
int		ft_loop_heredoc(t_pipex *p, int y, char *buffer, char *buffer2);
int		ft_heredoc_newline(int i, char *buffer, char *buffer2, t_pipex *p);
void	ft_full_pipe(t_pipex *p, char **envp, char **argv, char *buffer);

/* LIBFT_FUNCTS.C */

int		ft_ppx_strncmp_path(char *str, char *checked, int size);
char	*ft_strjoin_ppx(char *s1, char *s2, t_pipex *p);
void	ft_putchar_error(char c);
void	ft_putnbr_error(int nb);
void	ft_putchar(char c);

/* UTILS.C */

int		ft_get_cmd_errors(t_pipex *p, int index, char *command);
int		ft_get_cmd(t_pipex *p, int i);
void	ft_get_paths_in_struct(t_pipex *p, char **envp);
void	ft_get_commands(t_pipex *p, char **argv);
void	ft_heredoc_limiter(t_pipex *p, char *buffer2);

#endif
