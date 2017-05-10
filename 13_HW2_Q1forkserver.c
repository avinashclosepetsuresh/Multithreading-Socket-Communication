#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include <netdb.h>
#include <netinet/in.h>


void new_processing (int newsock)
{
printf("entered/n");
int catch;
char buffer[256];
bzero (buffer,256);
char outputmsg[50] = "i got your messasge \n";

catch = recv(newsock,buffer,255,0);
printf("catch=%d",catch);
if(catch < 0)
{
perror(" i dint get your mesage ");
exit(1);
}

else {
printf(" the message is : %s\n", buffer);
catch = write(newsock, outputmsg, strlen(outputmsg) );
}
}


// the main function starts here. 
 main()
{

int sock_d_server, sock_d_client;
struct sockaddr_in serverA, clientB;
char displaymsg[50] = "Hello client what can i  do for you\n";
unsigned int length;
int new_sock;
char buffer[256];
int wait;
int length2;
int newsock_d_server;
int pid;
//int new_processing;
//struct sockaddr_storage serverStorage;
//  socklen_t addr_size;






// Section is for socket system call



if (!(sock_d_server = socket (AF_INET, SOCK_STREAM, 0 )))
{
	perror("Socket failed");
	exit(-1);
}

//bzero((char *)&serverA,sizeof(serverA));


serverA.sin_family = AF_INET;
serverA.sin_port = htons(5000);
serverA.sin_addr.s_addr =  inet_addr("127.0.0.1");
//bzero(&serverA.sin_zero, 8);
  memset(serverA.sin_zero, '\0', sizeof serverA.sin_zero); 

length = sizeof(serverA);

// This section is for the binding of server to a particular IP address or a port.

if ((bind (sock_d_server,(struct sockaddr *) & serverA, length)) == -1)
{
	perror (" binding failed");
	exit(-1);
}



// This section if for the server to listen for the clients to connect.

if((listen (sock_d_server,5)) == -1)
{
	perror(" listen failed");
	exit(-1);
}




// This section is for Accept call 

 length2 = sizeof(clientB);
//addr_size = sizeof(serverStorage);


while(1)
{

 if(( new_sock = accept( sock_d_server, (struct sockaddr*) &clientB, &length))== -1)
{
printf("New_sock/n");
	perror(" accept failed");
	exit(-1);
}

// create a child process here using fork system call 
	pid = fork();
	
	if(pid < 0)
	{
               printf("fork error/n");
		perror(" error in forking");
		exit(1);
	}
	
	if(pid == 0)
	{
           printf("succes/n");
	// this is the child process
	//close(sock_d_server);
	new_processing(new_sock);
	exit(0);
	}
	
	else
	{
	close(newsock_d_server);
	}	

}
}



/*

//call send ()

if( send(new_sock, displaymsg, strlen(displaymsg), 0)== -1)
{
perror(" sending failed");
exit(-1);
}

return 0;
}
 
}
*/
