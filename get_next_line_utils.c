/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppanpais <ppanpais@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:48:20 by ppanpais          #+#    #+#             */
/*   Updated: 2022/10/23 00:55:36 by ppanpais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_bufjoin(char *src, char *buf)
{
	size_t	len;
	size_t	i;
	char	*ret;

	len = 0;
	i = 0;
	while(src[i++])
		len++;
	i = 0;
	while(buf[i++])
		len++;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while(*src)
		ret[i++] = *src++;
	src -= i;
	while(*buf)
		ret[i++] = *src++;
	free(src);
	return (ret);
}
/*
	expand_buf: sub func = gnl_bufjoin
	-join storage->buffer with the buf 
	-(join = free(old storage->buf) and assign new one to it)
	return 0 if allocation failed otherwise return 1
*/
int	gnl_expand_buf(t_BUF *storage, char *buf, int len)
{
	int	i;
	char	*new_buf;

	i = 0;
	if (storage->load + len <= storage->size)
	{
		while(i < len)
		{
			(storage->buf)[storage->load] = buf[i];
			storage->load++;
			i++;
		}
	}
	else
	{
		new_buf = gnl_bufjoin(storage->buf, buf);
		if (!new_buf)
		{
			free(buf);
			return(0);
		}
		storage->load += len;
		storage->size = storage->load;
		storage->buf = new_buf;
	}
	return (1);
}

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p)
	{
		if (*p == (char)c)
			return (p);
		p++;
	}
	if (*p == (char)c)
		return (p);
	else
		return (NULL);
}

t_BUF	*gnl_create_buf()
{
	t_BUF	*new;
	size_t	i;

	i = 0;
	new = (t_BUF *)malloc(sizeof(t_BUF));
	if (!new)
		return (NULL);
	new->buf = (char *)malloc(sizeof(char) * 1025);
	if(!new->buf)
	{
		free(new);
		return (NULL);
	}
	new->size = 1024;
	new->load = 0;
	new->finish = 0;
	while(i <= new->size)
		(new->buf)[i++] = (char)0;
	return (new);
}
