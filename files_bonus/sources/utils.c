/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 01:18:38 by marvin            #+#    #+#             */
/*   Updated: 2023/03/11 01:18:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_get_cmd_errors(t_pipex *p, int index, char *command)
{
	if (access(p->commands[index][0], X_OK) == 0)
		return (p->cmd = ft_strjoin_ppx("./", p->commands[index][0], p), 1);
	if (access(p->commands[index][0], F_OK) == 0)
		return (p->cmd = command, 3);
	else
		return (p->cmd = command, 4);
}

int	ft_get_cmd(t_pipex *p, int index)
{
	char	*path_tested;
	char	*command;
	int		i;

	i = -1;
	command = ft_strjoin_ppx("/", p->commands[index][0], p);
	if (p->commands[index][0][0] == '.' && p->commands[index][0][1] == '/')
		return (ft_get_cmd_errors(p, i, command));
	else if (p->paths)
	{
		while (p->paths[++i])
		{
			path_tested = ft_strjoin_ppx(p->paths[i], command, p);
			if (access(path_tested, X_OK) == -1)
				free(path_tested);
			else
				return (free(command), p->cmd = path_tested, 0);
		}
		free(command);
	}
	else if (access(p->commands[index][0], X_OK) == 0)
		return (p->cmd = command, 0);
	return (-1);
}

void	ft_get_paths_in_struct(t_pipex *p, char **envp)
{
	int		i;
	char	*envp2;

	i = 0;
	while (envp[i] && ft_ppx_strncmp_path(envp[i], "PATH=", 5) == 0)
		i++;
	envp2 = envp[i] + 5;
	p->paths = ft_split(envp2, ':');
	if (!p->paths)
		ft_free_exit_pipex("Malloc get path in struct", p, 109);
}

void	ft_get_commands(t_pipex *p, char **argv)
{
	int	i;
	int	y;

	i = -1;
	p->argv_x_size = (int *)malloc(sizeof(int) * p->nb_cmds);
	if (!p->argv_x_size)
		ft_free_exit_pipex("malloc 1 ft_get_commands", p, 1);
	while (++i < p->nb_cmds)
	{
		p->commands[i] = ft_split(argv[i + 2 + p->there_is_here_doc], ' ');
		if (!p->commands[i])
			ft_free_exit_pipex("malloc 1 ft_get_commands", p, 1);
		p->commands_were_malloced++;
	}
	i = 0;
	while (i < p->nb_cmds)
	{
		y = 0;
		while (p->commands[i][y])
			y++;
		p->argv_x_size[i] = y;
		i++;
	}
}

void	ft_heredoc_limiter(t_pipex *p, char *buffer2)
{
	close(p->pipe_heredoc[1]);
	free(p->limiter);
	return ;
	if (buffer2)
		write(1, buffer2, ft_strlen(buffer2));
}
