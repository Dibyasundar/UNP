#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/signal.h>
int main()
{

	signal(SIGCHLD, SIG_IGN);

	int socket,len;
	socket = socket(AF_INET, SOCK_STREAM, 0);
	if(socket <0)
		perror("socket failed .... : ");
	else
		printf("Socket created ....\n");
	struct sockaddr_in s_addr;
	/*s_addr.sin_port = htons(33456);
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// s_addr.sin_addr.s_addr = inet_addr("0.0.0.0"); // htonl(INADDR_ANY)
	// inet_aton("0.0.0.0", &s_addr.sin_addr);
	
	int br = bind(socket, (struct sockaddr *)&s_addr, sizeof(s_addr));
	if (br<0)
		perror("bind failed : ");
	else
		printf("bind completed .....\n");
	*/
	int lr = listen(socket, 10);
	if(lr<0)
		perror("listen failed : ");
	else
	{
		printf("listen completed ... \n");
		len = sizeof(struct sockaddr_in);
		getsockname(socket, (struct sockaddr * )&s_addr, &len);
		printf("server ip : %s\n", inet_ntoa(s_addr.sin_addr));
		printf("server is listening on %d\n", ntohs(s_addr.sin_port));
	}

	int fd;
	struct sockaddr_in c_addr;
	while(1) // for(; ;)
	{
		len = sizeof(struct sockaddr_in);
		fd = accept(socket, (struct sockaddr *) &c_addr, &len);
		if(fd<0)
			perror("accept failed : ");
		else
		{
			printf("accept completed ....\n");
			len = sizeof(struct sockaddr_in);
			getsockname(fd, (struct sockaddr *) &c_addr, &len);
			printf("local endpoint ip : %s\n", inet_ntoa(c_addr.sin_addr));
			printf("local endpoint port : %d\n", ntohs(c_addr.sin_port));
			len = sizeof(struct sockaddr_in);
			getpeername(fd, (struct sockaddr *) &c_addr, &len);
			printf("remote endpoint ip : %s\n", inet_ntoa(c_addr.sin_addr));
			printf("remote endpoint port : %d\n", ntohs(c_addr.sin_port));
		}

		pid_t pid = fork();
		if(pid<0)
			perror("fork failde : ");
		else if(pid ==0)
		{
			// client operation
			close(socket);
			char buffer[200];
			int n;
			while(1)
			{
				n =  read(fd, buffer, 199);
				if(n==0)
				{
					printf("client terminated .....\n");
					break;
				}
				else
				{
					write(fd, buffer, strlen(buffer));
				}	
			}
			exit(0);
		}
		else
		{
			close(fd);
		}
			
	}
}
