#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	*test_read(int fd)
{
	char	buf[1000];
	int	len;

	len = read(fd, buf, 500);
	buf[len] = '\0';
	printf("%s\n", buf);
}

int	main()
{
	int	fd1, fd2;

	fd1 = open("x.file", O_RDONLY);
	fd2 = open("x2.file", O_RDONLY);
	test_read(fd1);
//	test_read(fd2);
//	test_read(fd1);
}
