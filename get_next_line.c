/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:29:03 by melanieyane       #+#    #+#             */
/*   Updated: 2022/12/17 19:36:24 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	add_to_buffer(fd, &stash);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	add_to_buffer(int fd, char **stash)
{
	char	*buffer;
	int		len;

	len = 1;
	while ((check_newline(*stash, '\n') == 0) && (len != 0))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		len = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*stash == NULL && len == 0) || len == -1)
		{
			free(buffer);
			return ;
		}
		buffer[len] = '\0';
		add_to_stash(stash, buffer, len);
		free(buffer);
	}
}

void	add_to_stash(char **stash, char *buffer, int len)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(*stash) + len + 1));
	if (tmp == NULL)
		return ;
	if (*stash == NULL)
		tmp = ft_strdup(buffer);
	else
		tmp = ft_strjoin(*stash, buffer);
	*stash = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
}

void	extract_line(char *stash, char **line)
{
	int		i;
	int		j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	i = 0;
	j = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			(*line)[j] = stash[i];
			j ++;
			break ;
		}
		(*line)[j] = stash[i];
		j ++;
		i ++;
	}
	(*line)[j] = '\0';
}

void	generate_line(char **line, char *stash)
{
	int	i;
	int	malloc_size;

	i = 0;
	malloc_size = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			malloc_size++;
			break ;
		}
		malloc_size++;
		i ++;
	}
	*line = malloc(sizeof(char) * (malloc_size + 1));
}

/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("haricotvert.txt", O_RDONLY);
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	return (0);
}
*/
