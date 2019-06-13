/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:08:28 by apion             #+#    #+#             */
/*   Updated: 2019/04/03 17:40:59 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

#define EOL_CHAR		'\n'

#define CHAR_NOT_FOUND		-1
#define EXTRACT_WITH_BUFFER	1

static ssize_t	memsearch(char *mem, size_t size)
{
	unsigned int	i;

	if (!mem)
		return (CHAR_NOT_FOUND);
	i = 0;
	while (i < size && *(mem + i) != EOL_CHAR)
		++i;
	if (i < size && *(mem + i) == EOL_CHAR)
		return (i);
	return (CHAR_NOT_FOUND);
}

static char		*memjoin(char *mem1, size_t size1, char *mem2, size_t size2)
{
	char			*mem;
	unsigned int	size;

	size = size1 + size2;
	if (!size && (size < size1 || size < size2))
		return (0);
	mem = (char *)malloc(sizeof(*mem) * (size + 1));
	if (!mem)
		return (0);
	*(mem + size) = 0;
	if (mem2)
		while (size2--)
			*(mem + size1 + size2) = *(mem2 + size2);
	if (mem1)
		while (size1--)
			*(mem + size1) = *(mem1 + size1);
	return (mem);
}

static ssize_t	extract_temp(t_gnl *gnl)
{
	void			*temp_copy;

	temp_copy = gnl->temp;
	gnl->temp = memjoin(gnl->temp, gnl->temp_size, gnl->buff + gnl->index_start,
			gnl->buff_read - gnl->index_start);
	free(temp_copy);
	if (!gnl->temp)
	{
		gnl->temp_size = 0;
		return (-1);
	}
	gnl->temp_size += gnl->buff_read - gnl->index_start;
	return (0);
}

static ssize_t	extract_line(char **line, t_gnl *gnl, int had_newline)
{
	size_t		size_in_buff;
	ssize_t		ret;

	size_in_buff = had_newline ? gnl->index_eol - gnl->index_start : 0;
	if (had_newline)
		*line = memjoin(gnl->temp, gnl->temp_size,
				gnl->buff + gnl->index_start, size_in_buff);
	else
		*line = memjoin(gnl->temp, gnl->temp_size, 0, size_in_buff);
	ret = gnl->temp_size + size_in_buff;
	gnl->index_start = had_newline ? gnl->index_eol + 1 : 0;
	free(gnl->temp);
	gnl->temp_size = 0;
	gnl->temp = 0;
	*(gnl->buff + gnl->index_eol) = 0;
	if (!*line)
		return (GNL_ERROR);
	if (gnl->index_start < gnl->buff_read
			&& CHAR_NOT_FOUND == memsearch(gnl->buff + gnl->index_start,
				gnl->buff_read - gnl->index_start)
			&& extract_temp(gnl) < 0)
		return (GNL_ERROR);
	return (ret);
}

ssize_t			get_next_line(const int fd, char **line, int *eol_had_newline)
{
	static t_gnl	gnl;

	if (fd < 0 || !line)
		return (GNL_ERROR);
	if ((gnl.index_eol = gnl.index_start + memsearch(
					gnl.buff + gnl.index_start,
					gnl.buff_read - gnl.index_start + 1))
			>= gnl.index_start)
		return (extract_line(line, &gnl, (*eol_had_newline = 1)));
	while ((gnl.buff_read = read(fd, gnl.buff, BUFF_SIZE)) > 0)
	{
		gnl.index_start = 0;
		if ((gnl.index_eol = memsearch(gnl.buff, gnl.buff_read)) >= 0)
			return (extract_line(line, &gnl, (*eol_had_newline = 1)));
		else if (extract_temp(&gnl) < 0)
			return (GNL_ERROR);
	}
	if (!gnl.buff_read && gnl.temp_size > 0)
		return (extract_line(line, &gnl, (*eol_had_newline = 0)));
	return (gnl.buff_read == 0 ? GNL_EOF : GNL_ERROR);
}
