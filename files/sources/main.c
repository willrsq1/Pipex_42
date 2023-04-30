/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:13:01 by root              #+#    #+#             */
/*   Updated: 2023/04/30 14:21:00 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;

	i = -1;
	while (++i < argc)
	{
		if ((argv[i][0]) == '\0')
		{
			write(2, "zsh: parse error near `|'\n", 27);
			exit(17);
		}
	}
	if (argc == 5)
		ft_pipex(argc, argv, envp);
	else
	{
		write(1, "Please enter 4 args: FILE - CMD1 - CMD2", 40);
		write(1, " - OUTFILE.\nThank you !\n", 25);
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
	p->nb_cmds = argc - 3;
	ft_pipex_initialisation(p);
	ft_get_fds(p, argv, argc);
	ft_get_paths_in_struct(p, envp);
	ft_get_commands(p, argv);
	ft_forking(p, envp);
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
		if (pipe(p->pipe[i]) == -1)
			ft_free_exit_pipex("Fail pipe[i]\n", p, 4);
	}
}
