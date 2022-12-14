/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppanpais <ppanpais@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:48:04 by ppanpais          #+#    #+#             */
/*   Updated: 2022/10/24 02:01:06 by ppanpais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif	

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/resource.h>

typedef struct big_buffer
{
	char	*buf;
	size_t	load;
	size_t	size;
	int		fd;
	int		finish;
}	t_BUF;

int		bonus_keygen(int fd, t_BUF **arr);
int		gnl_expand_buf(t_BUF *storage, char *buf, int len);
char	*get_next_line(int fd);
char	*gnl_strlchr(const char *s, int c, int limit);
t_BUF	*gnl_create_buf(int fd);
#endif