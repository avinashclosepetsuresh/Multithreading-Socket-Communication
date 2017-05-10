#include <stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <sys/fcntl.h>

int main(int argc, char *argv[])
{
struct sockaddr_in client_Addr={0};
int sock_d_client;
serverddr.sin_family=AF_INET;
serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
serveraddr.sin_port=htons(10000);

sock_d_client= socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

int len = sizeof(struct sockaddr);
connect(sock_d_client,(struct sockaddr*)&serveraddr,len);
char buffer_client[512] = " hi server";
int data = 512;
int pos=0;
int data_sent=0;

while(1)
{
buffer_client[512]="NULL";
fgets(buffer_client,50,stdin);
 do
{
data_sent = send(sock_d_client,&buffer_client[pos],data,0);
data = data-data_sent;
pos = pos+data_sent;
}
while(data > 0);
}
printf("Message received is : %s\n",buffer_client);
close(sock_d_client);

return 1;
}

