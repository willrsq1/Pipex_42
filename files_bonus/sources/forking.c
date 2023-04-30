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

void	ft_forking(t_pipex *p, char **envp, char **argv)
{
	int	i;

	i = -1;
	if (p->there_is_here_doc == 1)
		ft_here_doc(p, envp, argv);
	while (++i < p->nb_cmds)
	{
		if (ft_command_check(p, i) == 0)
		{
			p->forks_id[i] = fork();
			if (p->forks_id[i] == -1)
				ft_free_exit_pipex("Fail fork[i]\n", p, 5);
			else if (p->forks_id[i] != 0)
			{
				if (i > 0 && i != p->nb_cmds - 1)
					close(p->pipe[i - 1][1]);
				else if (i == 0)
					close(p->pipe[i][1]);
				free(p->cmd);
			}
			else if (p->forks_id[i] == 0)
				ft_fork_loop(p, envp, i);
		}
	}
	ft_close_pipes(i, p);
}

void	ft_first_fork(t_pipex *p, char **envp, int i)
{
	if (p->there_is_here_doc == 1)
	{
		close(1);
		close(p->pipe_heredoc[1]);
		if (dup2(p->pipe_heredoc[0], 0) < 0)
			ft_free_exit_pipex("Dup2 n*1 of firstfork_HERE\n", p, 127);
	}
	else
	{
		if (dup2(p->fd1, 0) < 0)
			ft_free_exit_pipex("Dup2 n*1 of firstfork_bonus\n", p, 127);
	}
	close(p->pipe[0][0]);
	if (dup2(p->pipe[0][1], 1) < 0)
		ft_free_exit_pipex("Dup2 n*2 of firstfork_bonus\n", p, 12);
	if (execve(p->cmd, p->commands[i], envp) == -1)
		ft_free_exit_pipex("Execve\n", p, 14);
}

void	ft_fork_loop(t_pipex *p, char **envp, int i)
{
	if (i == 0)
		ft_first_fork(p, envp, i);
	else if (i == p->nb_cmds - 1)
		ft_last_fork(p, envp, i);
	else
	{
		close(p->pipe[(i - 1)][1]);
		if (dup2(p->pipe[(i - 1)][0], 0) < 0)
			ft_free_exit_pipex("Dup2 n*1 of forkloop_bonus\n", p, 31);
		close(p->pipe[i][0]);
		if (dup2(p->pipe[i][1], 1) < 0)
			ft_free_exit_pipex("Dup2 n*2 of forkloop_bonus\n", p, 22);
		if (execve(p->cmd, p->commands[i], envp) == -1)
			ft_free_exit_pipex("Execve\n", p, 24);
	}
}

void	ft_last_fork(t_pipex *p, char **envp, int i)
{
	close(p->pipe[(i - 1)][1]);
	if (dup2(p->pipe[(i - 1)][0], 0) < 0)
		ft_free_exit_pipex("Dup2 n*1 of lastfork_bonus\n", p, 31);
	if (dup2(p->fd2, 1) < 0)
		ft_free_exit_pipex("Dup2 n*2 of lastfork_bonus\n", p, 32);
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
	if (p->there_is_here_doc == 1)
	{
		close (p->pipe_heredoc[1]);
		close (p->pipe_heredoc[0]);
		close (1);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	close(0);
}
