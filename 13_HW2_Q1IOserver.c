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

int val, fd,count,sock_d_server,flag_catch,i;
fd_set read_set, ready_set;
int client[FD_SETSIZE];
char buffer[200];
struct sockaddr_in servAddr={0};

servAddr.sin_family=AF_INET;
servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
servAddr.sin_port=htons(10000);


sock_d_server=socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
//synchronous IO for non-blocking using fcntl call
flag_catch = fcntl(sock_d_server, F_GETFL, 0);
fcntl(sock_d_server, F_SETFL, flag_catch | O_NONBLOCK);

//Bind system call 
bind(sock_d_server, (struct sockaddr*)&servAddr, sizeof(struct sockaddr));

//Listen for incomming sockets
listen(sock_d_server, 1);

fd=sock_d_server;
val=-1;

for(i=0;i<FD_SETSIZE;i++)
client[i]=-1;
FD_ZERO(&read_set);
FD_SET(sock_d_server, &read_set);

struct sockaddr_in clientAddr={0};
int clientfd, j, k;
struct timeval timeout;

timeout.tv_sec  = 4 * 60;
timeout.tv_usec = 0;


while(1)
{

ready_set = read_set;
//apparent concurrency using select
flag_catch = select(fd+1, &ready_set, NULL, NULL, &timeout);

if(FD_ISSET(sock_d_server, &ready_set))
{
printf("\nNew client");
int size=sizeof(clientAddr);

//Accept the connection
clientfd = accept(sock_d_server, (struct sockaddr*)&clientAddr, &size);
if(clientfd)
{
for(j=0;j<FD_SETSIZE;j++)
if(client[j]<0)
{

client[j]=clientfd;

break;
}
FD_SET(clientfd, &ready_set);
if(clientfd > fd)
fd=clientfd;
if(j>val)
val=j;
}
}

for(k=0;k<=val;k++)
{

if(client[k]>0)
{
char buffer_of_TCP[512]={0};
int data_in=512;
int current_position=0;
int data=0;
do
{

data=recv(clientfd, &buffer_of_TCP[current_position], data_in, 0);
data_in=data_in-data;
current_position=current_position+data;

} while(data_in>0);

printf("\n message received from client is :\n%s\n", buffer_of_TCP);
if(data_in==0)
{
close(client[k]);
FD_CLR(client[k], &ready_set);
client[k]=-1;

}
count--;
if(count<=0)
break;

}
}

}

close(sock_d_server);
return EXIT_SUCCESS;

}
