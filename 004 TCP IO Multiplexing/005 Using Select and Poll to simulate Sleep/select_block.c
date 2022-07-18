// Program to block using select for 5 sec....
//
#include<stdio.h>
#include<sys/select.h>
#include<sys/time.h>
#include<poll.h>
int main()
{
	struct timeval t;
	t.tv_sec  = 5;
	int fd= fileno(stdin);
	int maxfd = fd +1;
	fd_set readset;
	FD_ZERO(&readset);
	FD_SET(fd, &readset);
	int n = select(maxfd, &readset, NULL, NULL, &t);
	printf("Prog Completed ..... select returned %d\n", n);
	return(0);	
}
