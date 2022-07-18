#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<time.h>



int main()
{
	int u_socket = socket(AF_INET, SOCK_DGRAM, 0);// 0 -> IPPROTO_UDP
	if(u_socket<0)
		perror("socket failed : ");
	else
		printf("socket created .... \n");

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(33456);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int len = sizeof(struct sockaddr_in);
	int br = bind (u_socket, (struct sockaddr *)&serv_addr, len);
	if(br < 0)
		perror("bind failed : ");
	else
	{
		printf("bind completed ..\n");
		len = sizeof(struct sockaddr_in);
		getsockname(u_socket, (struct sockaddr *)&serv_addr, &len);
		printf("server ip : %s\n", inet_ntoa(serv_addr.sin_addr));
		printf("server port : %d\n", ntohs(serv_addr.sin_port));
	}

	char buffer[200];
	int n;

	struct sockaddr_in ca;
	time_t tick;
	while(1)
	{
		n = read(u_socket, buffer, 200);
		if(n < 0)
			perror("read failed : ");
		else if(n==0)
			break;
		buffer[n] = '\0';
		tick = time(NULL);
		snprintf(buffer, 200, "%s", ctime(&tick));
		n = write(u_socket, buffer, strlen(buffer));
		if(n<0)
			perror("write failed : ");
	}

	close(u_socket);
	return(0);

}
