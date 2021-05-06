#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
void reverse_string(char *str, char *rev_str)
{
	int i;
	char temp;
	for(i=0; i<strlen(str); i++)
	{
		rev_str[i]=str[strlen(str)-i-1];
	}
	rev_str[i++]='\n';
	rev_str[i]='\0';
}

int main(int argc, char *argv[])
{
    int n;
    char data[200];
    char rev_data[200];
    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    //construct a server
    //where we want to Listen to

    struct sockaddr_in server_address, client_address;

    server_address.sin_family = AF_INET;

    server_address.sin_port = htons(5600);

    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    bind(net_socket, (struct sockaddr*)&server_address,sizeof(server_address));
    listen(net_socket,10);
    int fd;
    int c;
    pid_t pid;
		while(1)
		{
		fd=accept(net_socket,(struct sockaddr*)&client_address,&c);
		printf("Accepted\n");
    while(recv(fd, data,200,0)!=0)
    {
			reverse_string(data, rev_data);
      write(fd,rev_data,strlen(rev_data));
    }
		close(fd);
	}
    return(0);

}