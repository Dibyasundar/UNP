#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	int net_socket = socket(AF_INET, SOCK_DGRAM, 0);
	int val, val_len;
	val_len = sizeof(val);
	getsockopt(net_socket, SOL_SOCKET, SO_BROADCAST, &val, &val_len);
	if(val == 1)
		printf("UDP Broadcast is allowed\n");
	else
	{
		printf("UDP Broadcast is not allowed\n");
		printf("Seting the Broadcast option to 1\n");
		val = 1;
		setsockopt(net_socket, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val));
	}
	val=0;
	val_len = sizeof(val);
        getsockopt(net_socket, SOL_SOCKET, SO_BROADCAST, &val, &val_len);
        if(val == 1)
                printf("NOW UDP Broadcast is allowed\n");


	struct sockaddr_in cli_addr;
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_port = htons(atoi(argv[2]));
	cli_addr.sin_addr.s_addr = inet_addr(argv[1]); // broadcast ip and fix port


	char buffer[20] = "Hello .....";
	sendto(net_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&cli_addr, sizeof(struct sockaddr_in));

	close(net_socket);
	return(0);
}
