#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int net_socket = socket(AF_INET, SOCK_DGRAM, 0);// 0 -> IPPROTO_UDP
	if(net_socket <0)
		perror("socket error : ");
	else
		printf("socket created .... \n");

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(33456);
	serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0"); // htonl(INETADDR_ANY);
	// inet_aton("0.0.0.0", &serv_addr.sin_addr);
	// inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr);
	
	int len = sizeof(struct sockaddr_in);
	int br = bind(net_socket, (struct sockaddr *)&serv_addr, len);

	if(br<0)
		perror("bind error : ");
	else
	{
		printf("bind completed ....\n");
		len = sizeof(struct sockaddr_in);
		getsockname(net_socket, (struct sockaddr *)&serv_addr, &len);
		printf("local ip : %s\n", inet_ntoa(serv_addr.sin_addr));
		printf("local port : %d\n", ntohs(serv_addr.sin_port));
	}


	char buffer[200];
	int n;
	struct sockaddr_in ca;
	while(1)//for(;;)
	{
		//n = read(net_socket, buffer, 200);
		len = sizeof(struct sockaddr_in);
		n = recvfrom(net_socket, buffer, 200, 0, (struct sockaddr *)&ca, &len);
		if(n<0)
			perror("read failed : ");
		buffer[n] = '\0';
		//n = write(net_socket, buffer, strlen(buffer));
		len = sizeof(struct sockaddr_in);
		n = sendto(net_socket, buffer, strlen(buffer),0 , (struct sockaddr *)&ca, len);
		if(n<0)
			perror("write failed : ");
	}
	close(net_socket);
	return(0);
}
