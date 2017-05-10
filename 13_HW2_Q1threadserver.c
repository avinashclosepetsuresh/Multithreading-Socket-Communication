#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread

//the thread function
void *child_process(void *);

int main(int argc , char *argv[])
{
    int sock_d_server , sock_d_client , len, client_new_sock, *new_sock;
    struct sockaddr_in server , client;

    //Creating a  server socket
   if((sock_d_server = socket(AF_INET , SOCK_STREAM , 0))==-1)
    {
        printf("Could not create socket");
    }
    printf("Socket created");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 3000 );

   // int	len1 = sizeof(struct sockaddr_in);

    //Binding a socket server
    if( bind(sock_d_server,(struct sockaddr *)&server ,sizeof(server)) < 0)
    {
        perror("binding failed");
        return 1;
    }
   // puts("bind done");

    //Listen
    listen(sock_d_server , 3);

    //Accept and incoming connection
   // puts("Waiting for incoming connections...");
    len = sizeof(struct sockaddr_in);

      //  len=sizeof(struct sockaddr_in);
       while(client_new_sock=accept(sock_d_server,(struct sockaddr*)&client,(socklen_t*)&len))
       {
        printf("Connection accepted");

        pthread_t thread_1;
        new_sock = malloc(1);
        *new_sock = client_new_sock;

        if(pthread_create(&thread_1, NULL , child_process , (void*) new_sock) < 0)
        {
            perror("threading failed at this point");
            return 1;
        }

       
    }

    if (client_new_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    return 0;
}
/*
  This will handle connection for each client
  */
void *child_process(void *sock_d_server)
{
    //Get the socket descriptor
    int sock = *(int*)sock_d_server;
    int catch;

        char sendBuff[100], client_message[2000];

      while((catch=recv(sock,client_message,2000,0))>0)
      {
	printf(" received message:%s \n",client_message);
        send(sock,client_message,catch,0);
      }
      close(sock);


    return 0;
}


