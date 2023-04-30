/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:44:50 by root              #+#    #+#             */
/*   Updated: 2023/03/16 12:34:22 by marvin           ###   ########.fr       */
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

typedef struct s_pipex
{
	char	**paths;
	char	***commands;
	char	*cmd;
	int		fd1;
	int		fd2;
	int		*argv_x_size;
	int		**pipe;
	int		*forks_id;
	int		nb_cmds;
	int		commands_were_malloced;
	int		err_fd1;
	int		err_fd2;

}	t_pipex;

/* MAIN.C */

int		main(int argc, char **argv, char **envp);
void	ft_first_fork(t_pipex *p, char **envp, int i);
void	ft_last_fork(t_pipex *p, char **envp, int i);
void	ft_forking(t_pipex *p, char **envp);
void	ft_program_termination(t_pipex *p);

/* UTILS.C */

int		ft_get_cmd(t_pipex *p, int i);
void	ft_get_commands(t_pipex *p, char **argv);
void	ft_get_fds(t_pipex *p, char **argv, int argc);
void	ft_get_paths_in_struct(t_pipex *p, char **envp);

/* FT_SPLIT.C*/

char	**ft_split(char *s, char c);

/* LIBFT_FUNCTS.C */

int		ft_ppx_strncmp_path(char *str, char *checked, int size);
char	*ft_strjoin_ppx(char *s1, char *s2, t_pipex *p);
// int		ft_strlen(char *str);
void	ft_putchar_error(char c);
void	ft_putnbr_error(int nb);

/* FREE.C */

void	ft_free_commands(t_pipex *p);
void	ft_free_paths(t_pipex *p);
void	ft_free_exit_pipex(char *message, t_pipex *p, int exit_code);
void	ft_free_exit_pipex(char *message, t_pipex *p, int exit_code);

/* ----- BONUS PART -----*/

/* BONUS.C*/

void	ft_pipex_initialisation(t_pipex *p);
void	ft_pipex(int argc, char **argv, char **envp);
int		ft_command_check(t_pipex *p, int i);
void	ft_forking(t_pipex *p, char **envp);
void	ft_first_and_last_fork(t_pipex *p, char **envp, int i);
void	ft_pipex_initialisation(t_pipex *p);
void	ft_close_pipes(int i, t_pipex *p);
int		ft_get_cmd_err(char *command, t_pipex *p, int index);

#endif
