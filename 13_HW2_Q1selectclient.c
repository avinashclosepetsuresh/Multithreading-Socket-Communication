#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>




int main(int args, char *argv[])
{
	int sock_d_client, catch2;
	struct sockaddr_in client;
	struct hostent *server_addr;
	char buffer[1024];

	
	

	if((sock_d_client = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket failed \n");
		close(sock_d_client);
		exit(1);
	}

	client.sin_family = AF_INET;
	client.sin_port = htons(55000);
	
	server_addr = gethostbyname("localhost");

	memcpy(&client.sin_addr, server_addr->h_addr, server_addr->h_length);

	if(connect(sock_d_client, (struct sockaddr *) &client, sizeof(client)) < 0)
	{
		perror("connect failed\n");
		close(sock_d_client);
		exit(1);
	}
while(1)
{
	printf("enter the message you want to send\nsend: ");
	memset((char *)&buffer, 0, 1024);
	
	fgets(buffer, 1024, stdin);
	if(send(sock_d_client, buffer, sizeof(buffer), 0) < 0)
	{
		perror("sending failed \n");
		close(sock_d_client);
		exit(1);
	}

	if((catch2= recv(sock_d_client, buffer, 1024, 0)) < 0)
		perror("receive failed");
	else {
		//printf("Accepting Data \n");
		 printf(" server msg:  %s \n", buffer);
       	}
	
	
}
	
	close(sock_d_client);

	return 0;

}

