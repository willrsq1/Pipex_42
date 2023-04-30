/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:42:53 by marvin            #+#    #+#             */
/*   Updated: 2023/03/11 20:42:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_forking(t_pipex *p, char **envp)
{
	int	i;

	i = -1;
	while (++i < p->nb_cmds)
	{
		if (ft_command_check(p, i) == 0)
		{
			p->forks_id[i] = fork();
			if (p->forks_id[i] == -1)
				ft_free_exit_pipex("Fail fork[i]\n", p, 5);
			else if (p->forks_id[i] != 0)
			{
				if (i == 0)
					close(p->pipe[i][1]);
				free(p->cmd);
			}
			else if (p->forks_id[i] == 0)
				ft_first_and_last_fork(p, envp, i);
		}
	}
	ft_close_pipes(i, p);
}

void	ft_first_and_last_fork(t_pipex *p, char **envp, int i)
{
	if (i == 0)
	{
		if (dup2(p->fd1, 0) < 0)
			ft_free_exit_pipex("Dup2 n*1 of firstfork_bonus\n", p, 127);
		close(p->pipe[0][0]);
		if (dup2(p->pipe[0][1], 1) < 0)
			ft_free_exit_pipex("Dup2 n*2 of firstfork_bonus\n", p, 12);
	}
	else if (i == p->nb_cmds - 1)
	{
		close(p->pipe[(i - 1)][1]);
		if (dup2(p->pipe[(i - 1)][0], 0) < 0)
			ft_free_exit_pipex("Dup2 n*1 of lastfork_bonus\n", p, 31);
		if (dup2(p->fd2, 1) < 0)
			ft_free_exit_pipex("Dup2 n*2 of lastfork_bonus\n", p, 32);
	}
	if (execve(p->cmd, p->commands[i], envp) == -1)
		ft_free_exit_pipex("Execve\n", p, 14);
}

void	ft_close_pipes(int i, t_pipex *p)
{
	int	y;

	y = -1;
	while (++y < i - 1)
	{
		close(p->pipe[y][0]);
		close(p->pipe[y][1]);
	}
	if (p->err_fd1 == 1)
		return ;
	while (waitpid(-1, NULL, 0) > 0)
		;
}
