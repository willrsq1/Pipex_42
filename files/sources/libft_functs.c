/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:59:51 by marvin            #+#    #+#             */
/*   Updated: 2023/03/11 11:59:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_ppx_strncmp_path(char *str, char *checked, int size)
{
	int	i;

	if (!str || !checked)
		return (0);
	i = 0;
	while (str[i] && checked[i] && str[i] == checked[i])
		i++;
	if (i == size)
		return (1);
	return (0);
}

char	*ft_strjoin_ppx(char *s1, char *s2, t_pipex *p)
{
	char	*str;
	int		i;
	int		y;

	i = -1;
	y = -1;
	if (!s1)
		return (s2);
	if (!s2)
		return (NULL);
	if (!s1 && !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		ft_free_exit_pipex("strjoin", p, 1);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++y])
		str[i + y] = s2[y];
	str[i + y] = '\0';
	return (str);
}

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

void	ft_putchar_error(char c)
{
	write (2, &c, 1);
}

void	ft_putnbr_error(int nb)
{
	if (nb < 0)
	{
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_error(nb / 10);
		ft_putnbr_error(nb % 10);
	}
	else
		ft_putchar_error(nb + '0');
}
