/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:44:28 by melanieyane       #+#    #+#             */
/*   Updated: 2023/04/13 14:30:08 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Fonction qui calcule la taille d'une chaîne de caractères */

int	ft_strlen(char const *str)
{
	int	size;

	size = 0;
	if (!str)
		return (0);
	while (str[size] != '\0')
		size ++;
	return (size);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Fonction qui copie une chaîne de caractères */

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		i;

	result = malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i ++;
	}
	result[i] = '\0';
	return (result);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Fonction qui joint deux chaînes de caractères en allouant de la mémoire */

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*result;

	result = malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i ++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i + j] = s2[j];
		j ++;
	}
	result[i + j] = '\0';
	return (result);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Fonction pour chercher un passage à la ligne dans une chaîne de caractères */

int	check_newline(const char *str, char c)
{
	if (str == NULL)
		return (0);
	while (*str != c)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	return (1);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Fonction qui permet d'enlever de la stash ce qui a deja été extrait */

void	clean_stash(char **stash)
{
	char	*clean_stash;
	int		i;
	int		j;

	clean_stash = NULL;
	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i ++;
	if ((*stash)[i] && (*stash)[i] == '\n')
		i ++;
	clean_stash = malloc(sizeof(char) * (ft_strlen(*stash) - i + 1));
	if (clean_stash == NULL)
		return ;
	j = 0;
	while ((*stash)[i])
	{
		clean_stash[j] = (*stash)[i];
		j ++;
		i ++;
	}
	clean_stash[j] = '\0';
	free(*stash);
	*stash = ft_strdup(clean_stash);
	free(clean_stash);
}
