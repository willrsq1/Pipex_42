/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:32:43 by marvin            #+#    #+#             */
/*   Updated: 2023/03/13 15:33:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static size_t	ft_strclen(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_spliting(char **tab, char const *s, char c, int lignes)
{
	int	i;
	int	j;
	int	len;
	int	w;

	i = 0;
	j = 0;
	while (j < lignes)
	{
		w = -1;
		while (s[i] == c)
			i++;
		len = ft_strclen(&s[i], (int) c);
		tab[j] = (char *)malloc((len + 1) * sizeof(char));
		if (tab[j] == 0)
			return (NULL);
		while (w++ < len - 1)
			tab[j][w] = s[i++];
		tab[j][w] = '\0';
		j++;
	}
	return (tab);
}

static int	ft_nb_lignes(char const *s, char c, int i)
{
	int	lignes;

	lignes = 0;
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		lignes++;
		if (!s[i])
			return (lignes);
		while (s[i] && s[i] == c)
			i++;
	}
	return (lignes);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		lignes;
	char	**tab;

	i = 0;
	if (s == NULL)
		return (NULL);
	lignes = ft_nb_lignes(s, c, i);
	tab = (char **)malloc((lignes + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	if (lignes == 1)
	{
		tab[0] = s;
		tab[1] = NULL;
		return (tab);
	}
	ft_spliting(tab, s, c, lignes);
	tab[lignes] = NULL;
	return (tab);
}
