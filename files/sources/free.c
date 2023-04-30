/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:57:20 by marvin            #+#    #+#             */
/*   Updated: 2023/03/11 12:57:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_commands(t_pipex *p)
{
	int	i;
	int	y;

	i = 0;
	while (p->commands_were_malloced > 0)
	{
		y = 0;
		while (p->argv_x_size[i] > 1 && y < p->argv_x_size[i])
		{
			free(p->commands[i][y]);
			y++;
		}
		free(p->commands[i]);
		i++;
		p->commands_were_malloced--;
	}
}

void	ft_free_paths(t_pipex *p)
{
	int	i;

	i = -1;
	while (p->paths[++i])
		free(p->paths[i]);
	free(p->paths);
}

void	ft_free_pipes(t_pipex *p)
{
	int	i;

	i = -1;
	while (++i < p->nb_cmds - 1 && p->pipe[i])
		free(p->pipe[i]);
	free(p->pipe);
}

void	ft_free_exit_pipex(char *message, t_pipex *p, int exit_code)
{
	if (message)
		write(2, message, ft_strlen(message));
	if (p->err_fd1 == 0)
		close(p->fd1);
	if (p->err_fd2 == 0)
		close(p->fd2);
	if (!p)
		exit(exit_code);
	if (p->forks_id)
		free(p->forks_id);
	if (p->commands)
	{
		ft_free_commands(p);
		free(p->commands);
	}
	if (p->pipe)
		ft_free_pipes(p);
	if (p->paths)
		ft_free_paths(p);
	if (p->argv_x_size)
		free(p->argv_x_size);
	if (p)
		free(p);
	exit(exit_code);
}
