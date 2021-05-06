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
    // Open the file
    FILE *fp = fopen ( "dd.txt", "r" );
    int is_all_sent=0;
    char *ch;
    fflush(stdout);
    fflush(stdin);
    while (1)
    {
      if (is_all_sent==0)
        FD_SET(fileno(fp), &rset);

      FD_SET(net_socket, &rset);

      if (is_all_sent==0)
          maxfdp1 = ((fileno(fp)>net_socket)?fileno(fp):net_socket) + 1;
      else
          maxfdp1 = net_socket + 1;

      select(maxfdp1, &rset, NULL, NULL, NULL);
      if (is_all_sent==0)
      {
        ch = fgets(send_data, 200, fp);
      }
      if (FD_ISSET(net_socket, &rset))
      {  /* socket is readable */
            if (recv(net_socket, recv_data,200,0) == 0)
            {
               if ( is_all_sent ==1 )
               {
                 break;
               }
               else
               {
                printf("server terminated prematurely\n");
                break;
              }
            }
            fputs(recv_data, stdout);
        }
        if (FD_ISSET(fileno(fp), &rset))
        {  /* input is readable */
              if (ch == NULL)
              {
                is_all_sent=1;
                shutdown(net_socket, SHUT_WR);
                FD_CLR(fileno(fp), &rset);
                printf("All Line sent... treminating the writing half...\n" );
                continue;
              }
              write(net_socket,send_data,strlen(send_data));
        }
    }
    shutdown(net_socket, SHUT_RD);
    free(send_data);
    free(recv_data);
    return(0);
}
