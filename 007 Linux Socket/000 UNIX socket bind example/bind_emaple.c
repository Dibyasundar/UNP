#include<stdio.h>
#include<sys/socket.h>
#include <sys/un.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	int sockfd;
	socklen_t len;
	struct sockaddr_un addr1, addr2;
	if (argc != 2)
		{
			printf("Enter path name");
			exit(0);
		}
	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	unlink(argv[1]);
	
	bzero(&addr1, sizeof(addr1));
	
	addr1.sun_family = AF_LOCAL;
	strcpy(addr1.sun_path, argv[1]);
	bind(sockfd, (struct sockaddr *) &addr1, strlen(addr1.sun_path) +sizeof (addr1.sun_family));
	
	len = sizeof(addr2);
	
	getsockname(sockfd, (struct sockaddr *) &addr2, &len);
	printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);
	return(0);
}
