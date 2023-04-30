/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:23:36 by marvin            #+#    #+#             */
/*   Updated: 2023/03/16 12:23:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_command_check_part2(t_pipex *p, int i, int return_value)
{
	if (return_value == 1)
	{
		if (ft_ppx_strncmp_path(p->cmd, "/./", 3) == 1)
		{
			write(2, "zsh: permission denied: ./\n", 28);
			return (-1);
		}
	}
	else if (return_value == 3)
	{
		write(2, "zsh: permission denied: ", 25);
		write(2, p->commands[i][0], ft_strlen(p->commands[i][0]));
		write(2, "\n", 1);
		return (-1);
	}
	else if (return_value == 4)
	{
		write(2, "zsh: no such file or directory: ", 33);
		write(2, p->commands[i][0], ft_strlen(p->commands[i][0]));
		write(2, "\n", 1);
		return (-1);
	}
	return (0);
}

int	ft_command_check(t_pipex *p, int i)
{
	int	return_value;

	if (p->commands[i][0][0] == '.' && p->commands[i][0][1] == '\0')
	{
		write(2, ".: not enough arguments\n", 25);
		return (-1);
	}
	if ((i == 0 && p->err_fd1 == 1) || (i == p->nb_cmds -1 && p->err_fd2 == 1))
		return (-1);
	return_value = ft_get_cmd(p, i);
	if (return_value == -1)
	{
		write(2, p->commands[i][0], ft_strlen(p->commands[i][0]));
		write(2, ": command not found\n", 21);
		return (-1);
	}
	else if (return_value > 0)
		return (ft_command_check_part2(p, i, return_value));
	return (0);
}
