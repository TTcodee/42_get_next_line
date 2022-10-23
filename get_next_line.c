/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppanpais <ppanpais@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:47:52 by ppanpais          #+#    #+#             */
/*   Updated: 2022/10/23 01:10:41 by ppanpais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	buf_len(int len, char *buf)
{
	int	l;

	if (len != 0)
		return (len);
	l = 0;
	while(buf[l])
		l++;
	return (l);
}

char	*gnl_get_line(t_BUF *storage)
{
	char	*last;
	char	*start;
	char	*line;
	size_t	i;

	i = 0;
	start = storage->buf;
	if (ft_strchr(storage->buf, '\n'))
		last = ft_strchr(storage->buf, '\n') + 1;
	else
		last = storage->buf + storage->load;
	line = (char *)malloc(sizeof(char) * (last - start + 1));
	line[last - start] = '\0';
	if (!line)
		return (NULL);
	storage->load -= last - start;
	while(start < last)
		line[i++] = *start++;
	i = 0;
	while(*last)
		storage->buf[i++] = *last++;
	return (line);
}

int	gnl_read_line(int fd, t_BUF *storage)
{
	char	*buf;
	int	len;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	len = 1;
	while (len != 0)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len < 0)
		{
			free(buf);
			return (0);
		}
		buf[len] = '\0';
		if (!gnl_expand_buf(storage, buf, buf_len(len, buf)))
			return (0);
		if (ft_strchr(storage->buf, '\n'))
			break ;
	}
	if (len == 0)
		storage->finish = 1;
	free(buf);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_BUF	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);	
	if (buffer == NULL)
		buffer = gnl_create_buf();
	if (!buffer)
	{
		if (buffer->buf)
			free(buffer);
		free(buffer);
		return (NULL);
	}
	if (!gnl_read_line(fd, buffer))
		return (NULL);
	line = gnl_get_line(buffer);	
	if (buffer->load == 0 && buffer->finish)
	{
		free(buffer->buf);
		free(buffer);
	}
	return (line);
}
