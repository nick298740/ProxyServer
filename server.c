#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
 
char str[2000];
char fileToOpen[1000];
char fileLine[4096];
char buffer[2000000];
int listen_fd, conn_fd, n, PORT_NUMBER;
struct sockaddr_in servaddr;
FILE *file, *cachedFileList, *blackList;


void clearBuffer(char * arrayToClear){
	bzero(arrayToClear, sizeof(arrayToClear) / sizeof(arrayToClear[0]));
}

void setFileContents(){ 
    printf("\nHere is the current file to open: |%s|\n", fileToOpen);
    file = fopen(fileToOpen, "r");
    	
	clearBuffer(buffer);

    if(!file){ // check if file exists
	    perror("fopen"); 
	    strcat(buffer, "File not found.");
		
	} else { // if file exists, then...	
	    int lineCount = 1;	
		
		while(fgets(fileLine, sizeof fileLine, file)){ // while we have not reached end of file (EOF)...
			//printf("Inserted line number %d\n", lineCount);
				
			strcat(buffer, fileLine);
			lineCount++;
		}
		clearBuffer(fileLine);
	}
}

int checkCacheForRequestedURL(){
	
	cachedFileList = fopen(fileToOpen, "r");

	if(!cachedFileList){
		return -1; // Not found

	} else {
		return 1; // found
	}
}

void readMessage(){
   bzero(buffer,2000); 
   n = read( conn_fd,buffer,2000 );

   if (n < 0) {
	  perror("ERROR reading from socket");
	  //exit(1);
   }
}


void writeMessage(){
   n = write( conn_fd,buffer,2000 );
   bzero(buffer,2000);

   if (n < 0) {
	  perror("ERROR reading from socket");
	 // exit(1);
   }
}

void listenForConnection(){
	 /* AF_INET - IPv4 IP , Type of socket, protocol*/
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero(&servaddr, sizeof(servaddr));
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(PORT_NUMBER);
	printf("here is port number: %d", PORT_NUMBER);
 
    /* Binds the above details to the socket */
	bind(listen_fd,  (struct sockaddr *) &servaddr, sizeof(servaddr));
	/* Start listening to incoming connections */
	listen(listen_fd, 10);
}
 
int main(int argc,char **argv){
	PORT_NUMBER = atoi(argv[1]);

	system("sleep 3");
	listenForConnection();
    /* Accepts an incoming connection */
	conn_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
    bzero(buffer, 2000);
	printf("\n\nAccepted connection, waiting for message...\n\n");
	readMessage();
	strcpy(fileToOpen, buffer);

	printf("\n\nHere is the client requested URL: %s\n\n", fileToOpen);
	
	if(checkCacheForRequestedURL() == 1){
		// get file contents
		// send data to client
		setFileContents();
	} else { // cached file DNE
		// create command for getting cached file
		// run command, save as file
		// get file contents
		// send data to client
		char temp[2000];
		const char cache[10] = "";
		const char wget[8] = "wget ";
		const char apost[3] = "\"";
		const char fileNameCommand[5] = "-O ";
		const char html[7] = ".html";
		const char space[2] = " ";
		const char output[19] = " 2> wgetOutput.txt";
		clearBuffer(temp);
		// Build the command...
		strcat(temp, wget); // Add wget to command | wget 
		strcat(temp, fileNameCommand); // Add -O to command | wget -O 
		strcat(temp, fileToOpen); // Add to command the fileName based on requestedIP name | wget -O www.google.com
		strcat(temp, space);
		strcat(temp, fileToOpen); // Add to command the requestedIP based on requestedIP name | wget -O www.google.com www.google.com
		printf("\nHere is the command to execute: %s\n", temp);
		system(temp);
		
		system("sleep 5");
	}
	setFileContents();
	writeMessage();
    close (conn_fd); //close the connection
   
}
