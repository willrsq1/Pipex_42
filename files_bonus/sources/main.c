/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:13:01 by root              #+#    #+#             */
/*   Updated: 2023/04/30 14:21:30 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;

	i = -1;
	while (++i < argc)
	{
		if ((argv[i][0]) == '\0')
		{
			write(2, "zsh: parse error near `|'\n", 27);
			exit(17);
		}
	}
	if (argc > 4)
		ft_pipex(argc, argv, envp);
	else
	{
		write(1, "Please enter at least 4 args: FILE - CMD1 - CMD2 ", 50);
		write(1, "- - CMDX - OUTFILE.\nThank you !\n", 33);
		return (1);
	}
	return (0);
}

void	ft_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	p = malloc(sizeof(t_pipex));
	if (!p)
		exit(200);
	p->there_is_here_doc = 0;
	if (ft_ppx_strncmp_path(argv[1], "here_doc", 8) == 1)
	{
		p->there_is_here_doc = 1;
		p->limiter = argv[2];
	}
	p->nb_cmds = argc - 3 - p->there_is_here_doc;
	ft_pipex_initialisation(p);
	ft_get_fds(p, argv, argc);
	ft_get_paths_in_struct(p, envp);
	ft_get_commands(p, argv);
	if (p->there_is_here_doc == 1 && argc < 6)
		ft_here_doc_one_command(p, argv, envp);
	ft_forking(p, envp, argv);
	ft_free_exit_pipex(NULL, p, 0);
}

void	ft_pipex_initialisation(t_pipex *p)
{
	int	i;

	i = -1;
	p->forks_id = NULL;
	p->commands = NULL;
	p->pipe = NULL;
	p->paths = NULL;
	p->argv_x_size = NULL;
	p->forks_id = malloc(sizeof(int) * p->nb_cmds);
	p->commands = malloc(sizeof(char **) * p->nb_cmds);
	p->commands_were_malloced = 0;
	p->pipe = malloc(sizeof(int *) * p->nb_cmds - 1);
	if (!p->commands || !p->forks_id || !p->pipe)
		ft_free_exit_pipex("Commands ***'s // forks_id Malloc.\n", p, 2);
	while (++i < p->nb_cmds - 1)
	{
		p->pipe[i] = malloc(sizeof(int) * 2);
		if (!p->pipe[i])
			ft_free_exit_pipex("Pipe's Malloc.\n", p, 2);
		if (i < p->nb_cmds - 1 && pipe(p->pipe[i]) == -1)
			ft_free_exit_pipex("Fail pipe[i]\n", p, 4);
	}
}

void	ft_here_doc_one_command(t_pipex *p, char **argv, char **envp)
{
	ft_here_doc(p, envp, argv);
	if (ft_command_check(p, 0) == 0)
	{
		p->forks_id[0] = fork();
		if (p->forks_id[0] == -1)
			ft_free_exit_pipex("Fail fork[i]\n", p, 5);
		else if (p->forks_id[0] != 0)
			free(p->cmd);
		else if (p->forks_id[0] == 0)
		{
			close(1);
			close(p->pipe_heredoc[1]);
			if (dup2(p->pipe_heredoc[0], 0) < 0)
				ft_free_exit_pipex("Dup2 n*1 of firstfork_HERE\n", p, 127);
			if (dup2(p->fd2, 1) < 0)
				ft_free_exit_pipex("Dup2 n*2 of lastfork_bonus\n", p, 32);
			if (execve(p->cmd, p->commands[0], envp) == -1)
				ft_free_exit_pipex("Execve\n", p, 14);
		}
	}
	ft_close_pipes(1, p);
	ft_free_exit_pipex(NULL, p, 0);
}
