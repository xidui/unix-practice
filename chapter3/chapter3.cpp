#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char buf1[] = "abcde";
char buf2[] = "123456789";

int main(void)
{
	int fd;
	fd = open("/Users/apple/Documents/github/unix practice/chapter3/chapter3.txt", O_RDWR | O_CREAT | O_TRUNC);
	if (fd < 0)
	{
		printf("open error!\n");
	}

	off_t currpos;
	currpos = lseek(fd, 0, SEEK_CUR);
	printf("current pos: %d\n", (int)currpos);

	printf("size of buf1 : %d\n", (int)sizeof(buf1));
	if (write(fd, buf1, sizeof(buf1)) == -1)
	{
		printf("write error one\n");
	}

	currpos = lseek(fd, 0, SEEK_CUR);
	printf("current pos: %d\n", (int)currpos);

	if (lseek(fd, 3, SEEK_SET) == -1)
	{
		printf("lseek error\n");
	}

	if (write(fd, buf2, 10) != sizeof(buf2))
	{
		printf("write error two\n");
	}

	currpos = lseek(fd, 0, SEEK_CUR);
	printf("current pos: %d\n", (int)currpos);

	return 0;
}