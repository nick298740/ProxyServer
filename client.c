#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IP_ADDRESS 127.0.0.1

int sockfd, n, PORT_NUMBER;
int len = sizeof(struct sockaddr);
char recvline[40960];
char buffer[2000];
struct sockaddr_in servaddr;

void readMessage(){
   bzero(buffer,2000);
   n = read( sockfd,buffer,2000 );

   if (n < 0) {
	  perror("ERROR reading from socket");
	  exit(1);
   }
}


void writeMessage(){
   n = write( sockfd,buffer,2000 );
   bzero(buffer,2000);

   if (n < 0) {
	  perror("ERROR reading from socket");
	  exit(1);
   }
}

void connectToServer(){
	    /* AF_INET - IPv4 IP , Type of socket, protocol*/
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr,sizeof(servaddr));
 
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT_NUMBER); // Server port number
 
    /* Convert IPv4 and IPv6 addresses from text to binary form */
	inet_pton(AF_INET,IP_ADDRESS,&(servaddr.sin_addr));
 
    /* Connect to the server */
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
 
}

int main(int argc,char **argv){
	PORT_NUMBER = atoi(argv[1]);
	printf("here is port: %d", PORT_NUMBER);
	connectToServer();

	printf("\n\nPlease enter the URL to request from proxy server, using this form : www.example.com\n\n");
	
	char option[64],line[256];
        printf(">> ");
        if(fgets(line, sizeof(line), stdin)) {
            if (1 == sscanf(line, "%[^\n]%*c", option)) {//[^\n] isn't newline chars
	        strcpy(buffer, option);
	
	    }
        }
	
	printf("\n\nHere is the message written to the server: %s\n\n", buffer);
	writeMessage();
		
	readMessage();
	
	printf("\n\nHere is the message from the server, the website: %s\n\n", buffer);

	close(sockfd);
 
}
