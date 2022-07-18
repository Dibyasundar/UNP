// Program to block using poll for 5 sec....
//
#include<stdio.h>
#include<sys/select.h>
#include<sys/time.h>
#include<poll.h>
/* struct pollfd
 * {
 * 	int fd;
 * 	short events;
 * 	short revents;
 * }
 */
int main()
{
	struct pollfd a_fd[1];
	a_fd[0].fd = fileno(stdin);
	a_fd[0].events = POLLIN | POLLERR;
	int n = poll(a_fd, 1, 5000);
	printf("Prog completed .... poll returned %d\n", n);
	return(0);	
}
