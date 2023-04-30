/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:26:05 by marvin            #+#    #+#             */
/*   Updated: 2023/03/16 12:26:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_fd2_open_error(char **argv, int argc, t_pipex *p)
{
	p->fd2 = open(argv[argc - 1], O_DIRECTORY);
	if (p->fd2 != -1)
	{
		write(2, "bash: ", 7);
		write(2, argv[argc -1], ft_strlen(argv[argc -1]));
		write(2, ": Is a directory\n", 18);
		close(p->fd2);
	}	
	else
	{
		write(2, "zsh: no such file or directory: ", 33);
		write(2, argv[argc -1], ft_strlen(argv[argc -1]));
		write(2, "\n", 1);
	}
	p->err_fd2 = 1;
}

void	ft_get_fds(t_pipex *p, char **argv, int argc)
{
	p->err_fd2 = 0;
	p->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 000644);
	if (p->fd2 < 0)
		ft_fd2_open_error(argv, argc, p);
	p->fd1 = open(argv[1], O_RDONLY);
	p->err_fd1 = 0;
	if (p->fd1 < 0)
	{
		write(2, "bash: ", 7);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": No such file or directory\n", 29);
		p->err_fd1 = 1;
	}
}
