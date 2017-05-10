#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_SIZE 50

int main()
{
    int sock_d_client;
    struct sockaddr_in serv_addr;
    char send_buff[MAX_SIZE],recv_buff[MAX_SIZE];

    if((sock_d_client = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("Failed creating socket\n");

    bzero((char *) &serv_addr, sizeof (serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(3000);

    if (connect(sock_d_client, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) 
    {
        printf("connection failed\n");
        return -1;
    }

    printf("Connection established\n");

    while(fgets(send_buff, MAX_SIZE , stdin)!=NULL)
    {
      send(sock_d_client,send_buff,strlen(send_buff),0);

          if(recv(sock_d_client,recv_buff,MAX_SIZE,0)==0)
           printf("Error");
          else
           fputs(recv_buff,stdout);

       bzero(recv_buff,MAX_SIZE);
    }
        close(sock_d_client);
    return 0;

}
