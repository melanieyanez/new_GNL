/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:29:03 by melanieyane       #+#    #+#             */
/*   Updated: 2023/01/03 13:10:57 by melanieyane      ###   ########.fr       */
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
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while ((check_newline(*stash, '\n') == 0) && (len != 0))
	{
		if (buffer == NULL)
			return ;
		len = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*stash == NULL && len == 0) || len == -1)
		{
			free(buffer);
			if (len == -1)
			{
				free(*stash);
				stash = NULL;
			}
			return ;
		}
		buffer[len] = '\0';
		add_to_stash(stash, buffer);
	}
	free(buffer);
}

void	add_to_stash(char **stash, char *buffer)
{
	char	*tmp;

	tmp = NULL;
	if (*stash == NULL)
		tmp = ft_strdup(buffer);
	else
		tmp = ft_strjoin(*stash, buffer);
	if (*stash)
		free(*stash);
	*stash = ft_strdup(tmp);
	free(tmp);
}

void	extract_line(char *stash, char **line)
{
	int		i;
	int		j;

	generate_line(line, stash);
	if (*line == NULL)
	{
		free(line);
		return ;
	}
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

	fd = open("files/big_line_no_nl", O_RDONLY);
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	return (0);
}
*/