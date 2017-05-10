#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>   
#include <arpa/inet.h>    
#include <sys/time.h> 

#define PORT 55000


int main(int argc, char *argv[])
{
	

	
	int sock_d_server, catch, client_fd, clientsock[10], max_client = 10, select_val, max_fd, i, fd, addrlen, new_sock;
	struct sockaddr_in server;
	char buffer[512];
	char sendmsg[50] = "thank you\n" ;
	struct timeval time;

	  // Waiting time of two sec 
    	time.tv_sec = 2;
    	time.tv_usec = 0;
	
	fd_set rfds, wfds; 
	
	for (i = 0; i < max_client; i++) 
   	 {
       	 clientsock[i] = 0;
  	  }

	/*create socket*/
	sock_d_server = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_d_server <= 0)
	{
		perror("Socket failed \n");
		exit(EXIT_FAILURE);
	}

	
	memset((char *) &server, 0 , sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY; 
	server.sin_port = htons( PORT );



	/*binding the  socket*/
	if((bind(sock_d_server, (struct sockaddr *) &server, sizeof(server))) < 0)
		{
		perror("Failed to bind \n");
		exit(EXIT_FAILURE);
		}

	/* Listening state  function */
	if(listen(sock_d_server, 7) < 0)
	{
		perror("failed to listen \n");
		exit(EXIT_FAILURE);
	}
	else
		printf("server is ready \n");
	addrlen = sizeof(server);
	

	/* Accept state function */
	while(1)
	{
		FD_ZERO(&rfds);   
		FD_ZERO(&wfds);
		FD_SET(sock_d_server, &rfds);
		FD_SET(sock_d_server, &wfds);
		max_fd = sock_d_server;

		for ( i = 0 ; i < max_client ; i++) 	//add new sockets to set rfds
        	{
                       fd = clientsock[i];
                       if(fd > 0)
			{
           		     FD_SET( fd , &rfds);
			     FD_SET( fd , &wfds);
			}             
	               if(fd > max_fd)	
           		     max_fd = fd;
       		 }

	select_val = select(max_fd+1, &rfds, &wfds, NULL, &time);

	if(select_val < 0)
		perror("select error \n");

	if(FD_ISSET(sock_d_server, &rfds))
	{
		if((new_sock = accept(sock_d_server, (struct sockaddr *) &server, (socklen_t*)&addrlen)) < 0)
		 {
     	           perror("accept failed");
     	           exit(EXIT_FAILURE);
                 }
		 //printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_sock , inet_ntoa(server.sin_addr) , ntohs(server.sin_port));

	//printf("client new connected");

	
        for ( i = 0 ; i < max_client; i++) 
            {
                
                if( clientsock[i] == 0 )
                {
                   clientsock[i] = new_sock;
                   // printf("Adding to list of fd_set as %d\n" , i);                     
                    break;
                }
            }
	}

	for ( i = 0 ; i < max_client ; i++) 
            {
		fd = clientsock[i];

		if (FD_ISSET( fd , &rfds)) 
            	{
                	
                	if ((catch = recv( fd , buffer, sizeof(buffer), 0)) == 0)
                	{
                    		
                    		getpeername(fd , (struct sockaddr*)&server , (socklen_t*)&addrlen);
                    		printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(server.sin_addr) , ntohs(server.sin_port));
                      		printf(" received msg from client is: %s\n" , buffer);
                    //Close the socket using close call
                    close( fd );
                    clientsock[i] = 0;
                }
                  
                //Echo back the message that came in
                else
                {
                    
                    buffer[catch] = '\0';
                    send(fd , sendmsg , strlen(sendmsg) , 0 );
                }
            }	
	}
	}





	return 0;
}

