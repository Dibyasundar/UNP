#include<stdio.h>

#include<sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>

#include<sys/select.h>

int main(int argc, char *argv[])
{
    int n;
    char *send_data, *recv_data;
    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    connect( net_socket, ( struct sockaddr * ) &server_address, sizeof( server_address));
    recv_data = (char *) malloc (200*sizeof(char));
    send_data = (char *) malloc (200*sizeof(char));

    fd_set      rset;
    FD_ZERO(&rset);
    int         maxfdp1;

    while (1)
    {
      FD_SET(fileno(stdin), &rset);
      FD_SET(net_socket, &rset);
      maxfdp1 = ((fileno(stdin)>net_socket)?fileno(stdin):net_socket )+ 1;
      select(maxfdp1, &rset, NULL, NULL, NULL);
      if (FD_ISSET(net_socket, &rset)) {  /* socket is readable */
            if (recv(net_socket, recv_data,200,0) == 0)
            {
                printf("server terminated prematurely\n");
                break;
            }
            fputs(recv_data, stdout);
        }
      if (FD_ISSET(fileno(stdin), &rset)) {  /* input is readable */
            if (fgets(send_data, 200, stdin) == NULL)
                break;     /* all done */
            write(net_socket,send_data,strlen(send_data));
      }
    }
    free(send_data);
    free(recv_data);
    close(net_socket);
    return(0);
}
