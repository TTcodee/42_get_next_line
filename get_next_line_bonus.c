/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppanpais <ppanpais@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:47:52 by ppanpais          #+#    #+#             */
/*   Updated: 2022/10/24 02:16:53 by ppanpais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*free_buf(t_BUF *buffer)
{
	if (buffer->buf)
		free(buffer->buf);
	if (buffer)
		free(buffer);
	return (NULL);
}

int	buf_len(int len, char *buf)
{
	int	l;

	if (len != 0)
		return (len);
	l = 0;
	while (buf[l])
		l++;
	return (l);
}

char	*gnl_get_line(t_BUF *storage)
{
	char	*last;
	char	*start;
	char	*line;
	int		i;

	if (storage->load == 0 && storage->finish)
		return (NULL);
	i = 0;
	start = storage->buf;
	if (gnl_strlchr(storage->buf, '\n', storage->load))
		last = gnl_strlchr(storage->buf, '\n', storage->load) + 1;
	else
		last = storage->buf + storage->load;
	line = (char *)malloc(sizeof(char) * (last - start + 1));
	line[last - start] = '\0';
	if (!line)
		return (NULL);
	storage->load -= last - start;
	while (start < last)
		line[i++] = *start++;
	while (i)
		storage->buf[--i] = (char)0;
	while (*last)
		storage->buf[i++] = *last++;
	return (line);
}

int	gnl_read(int fd, t_BUF *storage, int buffer_size)
{
	char	*buf;
	int		len;

	buf = (char *)malloc(sizeof(char) * (buffer_size + 1));
	if (!buf)
		return (0);
	len = 1;
	while (len != 0)
	{
		len = read(fd, buf, buffer_size);
		if (len < 0)
		{
			free(buf);
			return (0);
		}
		buf[len] = '\0';
		if (!gnl_expand_buf(storage, buf, buf_len(len, buf)))
			return (0);
		if (gnl_strlchr(storage->buf, '\n', storage->load))
			break ;
	}
	if (len == 0)
		storage->finish = 1;
	free(buf);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_BUF	*buffer[RLIMIT_OFILE];
	char			*line;
	int				key;

	key = bonus_keygen(fd, buffer);
	if (fd < 0 || BUFFER_SIZE <= 0 || key < 0)
		return (NULL);
	if (buffer[key] == NULL)
		buffer[key] = gnl_create_buf(fd);
	if (buffer[key] == NULL)
		buffer[key] = gnl_create_buf(fd);
	if (!buffer[key])
		return ((char *)(buffer[key] = free_buf(buffer[key])));
	if (BUFFER_SIZE < 42)
	{
		if (gnl_read(fd, buffer[key], 42) == 0)
			return ((char *)(buffer[key] = free_buf(buffer[key])));
	}
	else
		if (gnl_read(fd, buffer[key], BUFFER_SIZE) == 0)
			return ((char *)(buffer[key] = free_buf(buffer[key])));
	line = gnl_get_line(buffer[key]);
	if (buffer[key]->load == 0 && buffer[key]->finish)
		buffer[key] = free_buf(buffer[key]);
	return (line);
}
