/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:03:30 by marvin            #+#    #+#             */
/*   Updated: 2023/03/16 23:03:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_here_doc(t_pipex *p, char **envp, char **argv)
{
	int	y;

	p->pipe_heredoc = malloc(sizeof(int) * 2);
	if (!p->pipe_heredoc)
		ft_free_exit_pipex("Pipe's Malloc.\n", p, 2);
	if (pipe(p->pipe_heredoc) == -1)
		ft_free_exit_pipex("Pipe Heredoc", p, 42);
	y = -1;
	while (argv[2][++y])
		;
	if (y > 1000)
		ft_free_exit_pipex("Please enter a smaller DELIMITER.", p, 99);
	p->limiter = ft_strjoin_ppx(argv[2], "\n", p);
	if (!p->limiter)
		ft_free_exit_pipex("Limiter heredoc", p, 69);
	if (dup2(p->pipe_heredoc[1], 1) == -1)
		ft_free_exit_pipex("dup2 heredoc", p, 66);
	p->buffer = NULL;
	p->buffer2 = NULL;
	p->temp = NULL;
	p->envp = envp;
	p->argv = argv;
	write(2, "> ", 2);
	ft_input_loop_heredoc(p);
}

void	ft_input_loop_heredoc(t_pipex *p)
{
	p->loops = 0;
	p->y = 0;
	while (1)
	{
		p->buffer = get_next_line(0);
		if (p->buffer)
		{
			p->y = ft_loop_heredoc(p, p->y, p->buffer, p->buffer2);
			if (p->y == -5)
			{
				if (p->buffer2)
					free(p->buffer2);
				if (p->buffer)
					free(p->buffer);
				return ;
			}
			p->temp = p->buffer2;
			p->buffer2 = ft_strjoin_ppx(p->buffer2, p->buffer, p);
			if (p->temp)
				free(p->temp);
			if (p->loops != 0)
				free (p->buffer);
			p->loops++;
		}
	}
}

int	ft_loop_heredoc(t_pipex *p, int y, char *buffer, char *buffer2)
{
	int	i;

	if (ft_ppx_strncmp_path(buffer, p->limiter, ft_strlen(p->limiter)) == 1)
		return (ft_heredoc_limiter(p, buffer2), -5);
	i = -1;
	i = ft_heredoc_newline(i, buffer, buffer2, p);
	if (i == -5)
		return (-5);
	while (buffer2 && buffer2[y++])
	{
		if (i + y > 65533)
		{
			write(1, buffer2, ft_strlen(buffer2));
			free(p->limiter);
			return (ft_full_pipe(p, p->envp, p->argv, buffer), -5);
		}
	}
	return (y);
}

int	ft_heredoc_newline(int i, char *buffer, char *buffer2, t_pipex *p)
{
	while (buffer[++i])
	{
		if (buffer[i] == '\n')
			write(2, "> ", 2);
		if (i > 65534)
		{
			if (buffer2)
				write(1, buffer2, ft_strlen(buffer2));
			free(p->limiter);
			return (ft_full_pipe(p, p->envp, p->argv, buffer), -5);
		}
		ft_putchar(buffer[i]);
	}
	return (i);
}

void	ft_full_pipe(t_pipex *p, char **envp, char **argv, char *buffer)
{
	p->fork_here = fork();
	if (p->fork_here == 0)
	{
		write(2, "This pipe is full. Another one was opened.\n", 44);
		p->temp_fork_heredoc = fork();
		if (p->temp_fork_heredoc != 0)
		{
			write(1, buffer, ft_strlen(buffer));
			while (waitpid(-1, NULL, 0) > 0)
				;
		}
		close(p->pipe_heredoc[1]);
		return ;
	}
	else if (p->fork_here != 0)
	{
		while (waitpid(-1, NULL, 0) > 0)
			;
		execve(argv[0], argv, envp);
	}
}
