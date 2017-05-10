#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>


int main()
{

int sock_d_server, sock_d_client;
struct sockaddr_in serverA;
char displaymsg[50];
unsigned int length, length2;
//char buffer[256];
int wait, server;
char sendmsg [50] = "hi server\n";


if ((sock_d_client = socket (AF_INET, SOCK_STREAM, 0 )) == -1)
{
	perror("Socket failed");
	exit(-1);
}
/*
if(server = gethostbyname(localhost)== 0)
{
  perror("error finding the hsot");
	exit(-1);
}
*/


//bzero((char *)&serverA,sizeof(serverA));
serverA.sin_family = AF_INET;
serverA.sin_port = htons(5000);
serverA.sin_addr.s_addr =  inet_addr("127.0.0.1");
//bzero(&serverA.sin_zero, 8);



length = sizeof(serverA);

if( connect( sock_d_client,(struct sockaddr*) &serverA, length) == -1)
{
printf("Not connect/n");
perror (" failed to connect");
exit(-1);
}
//printf(" connect/n");
//printf("enter the msg to be sent to server: ");

//bzero(buffer, 256);

//scanf("%s", buffer);
/*
if (wait= write( sock_d_server, buffer, strlen(buffer) )==-1)
{ 
 perror("client failed to write ");
exit(-1);
}

bzero(buffer, 256);
if (wait = read( sock_d_server, buffer, 255) == -1)
{
perror("read failed on the client side");
exit(-1);
}
printf (" %s\n", buffer);

*/
send(sock_d_client, sendmsg, sizeof(sendmsg), 0);
printf(" the sending message is: %s \n", sendmsg);

if( recv(sock_d_client, displaymsg , 50 , 0)== -1)
{
perror(" receiving form the socket failed");
exit(-1);
}
printf("Message=%s",displaymsg);


return 0;
}

