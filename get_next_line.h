/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppanpais <ppanpais@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:48:04 by ppanpais          #+#    #+#             */
/*   Updated: 2022/10/23 00:55:13 by ppanpais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif	

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct big_buffer
{
	char	*buf;
	size_t	load;
	size_t	size;
	int		finish;
}	t_BUF;

int		gnl_expand_buf(t_BUF *storage, char *buf, int len);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
t_BUF	*gnl_create_buf();
#endif
