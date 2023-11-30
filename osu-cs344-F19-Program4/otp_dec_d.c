#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void error(const char *msg) {
  perror(msg);
  exit(1);
}


int main(int argc, char* argv[]) {
  int listenSocketFD;
  int establishedConnectionFD;
  int portNumber;
  int charsRead;
  int charsWritten;
  int inputLength;
  int i;
  int j;
  int k;
  int l;
  int m;
  int encInt;
  int keyInt;
  int theSecret;
  char character;
  char tempString[5];
  char msgToEnc;
  char msgKey;
  char buffer[256];
  socklen_t sizeOfClientInfo;
  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;
  //pid_t listenForNew;


  if (argc < 2) {
    fprintf(stderr,"USAGE: %s port\n", argv[0]);
    exit(1);
  }


  memset((char *)&serverAddress, '\0', sizeof(serverAddress));
  portNumber = atoi(argv[1]);

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(portNumber);
  serverAddress.sin_addr.s_addr = INADDR_ANY;


  listenSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (listenSocketFD < 0){
	  error("ERROR opening socket");
  }

  if (bind(listenSocketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
	  error("ERROR on binding");
  }

  listen(listenSocketFD, 5);

fprintf(stderr, "Listening\n");
  while(1){
	  sizeOfClientInfo = sizeof(clientAddress);
	  establishedConnectionFD = accept(listenSocketFD, (struct sockaddr*)&clientAddress, &sizeOfClientInfo);
  fprintf(stderr, "Accepted\n");
	  if (establishedConnectionFD < 0){
		  error("ERROR on accept");
	  }


	  //Print message from 4.3 Network servers slides
	  //printf("SERVER: Connected Client at port %d\n", ntohs(clientAddress.sin_port));

fprintf(stderr, "Forking\n");
  	  pid_t listenForNew = fork();

fprintf(stderr, "%s%d\n", "Fork ", getpid());
	  if(listenForNew < 0){
		  perror("Unable to create another incoming connection.");
	  }
	  else if(listenForNew == 0){
		  for(m = 0; m < 256; m++){
			buffer[m] = '\0';
		  }


		  charsRead = recv(establishedConnectionFD, buffer, 1, 0);
		  if(charsRead < 0){
			error("SERVER: ERROR reading to socket");
		  }
		  if(strcmp(buffer, "D") == 0){
			charsWritten = send(establishedConnectionFD, "Y", 1, 0);
			if(charsWritten < 0){
				error("SERVER: ERROR writing to socket");
			}
		  }
		  if(strcmp(buffer, "E") == 0){
			charsWritten = send(establishedConnectionFD, "N", 1, 0);
			if(charsWritten < 0){
				error("SERVER: ERROR writing to socket");
			}
		  }


		  charsRead = recv(establishedConnectionFD, buffer, 255, 0);
		  if (charsRead < 0){
			  error("SERVER: ERROR reading from socket");
		  }


		  for(i = 0; i < 5; i++){
			character = buffer[i];

			tempString[i] = character;
		  }

		  if(strcmp(tempString, "gotit") == 0){

			  inputLength = atoi(&buffer[5]);


			  charsWritten = send(establishedConnectionFD, "I am the server, and I got your message", 39, 0);
			  if(charsWritten < 0){
				error("SERVER: ERROR writing to socket");
			  }


			  char encMsg[inputLength];
			  memset(encMsg, '\0', inputLength);
			  char keyMsg[inputLength];
			  memset(keyMsg, '\0', inputLength);

			charsRead = 0;
			  while(charsRead < inputLength){
				  charsRead += recv(establishedConnectionFD, &encMsg[charsRead], inputLength - charsRead, 0);
				  if (charsRead < 0){
					  error("SERVER: ERROR reading to socket");
			  	}
			  }

			  charsWritten = send(establishedConnectionFD, "I am the server, and I got your message", 39, 0);
			  if(charsWritten < 0){
				  error("SERVER: ERROR writing to socket");
			  }
			charsRead = 0;
		  	  while(charsRead < inputLength){
				  charsRead += recv(establishedConnectionFD, &keyMsg[charsRead], inputLength - charsRead, 0);
				  if(charsRead < 0){
					  error("SERVER: ERROR reading to socket");
				  }
			  }


			  charsWritten = send(establishedConnectionFD, "I am the server, and I got your message", 39, 0);
			  if(charsWritten < 0){
				  error("SERVER: ERROR writing to socket");
			  }


			  char justWork[inputLength];
			  memset(justWork, '\0', inputLength);


			  for(l = 0; l < inputLength; l++){

				encInt = (int)encMsg[l];
				//printf("%s%d", "enc msg: ", encInt);
				keyInt = (int)keyMsg[l];
				//printf("%s%d", "key msg: ", keyInt);

				encInt = encInt - (int)'A';
				keyInt = keyInt - (int)'A';

				if(encInt < 0){
					encInt = 26;
				}
				if(keyInt < 0){
					keyInt = 26;
				}

				theSecret = encInt - keyInt;

				if(theSecret < 0){
					theSecret = theSecret + 27;
				}

				theSecret = theSecret % 27;

				theSecret = theSecret + (int)'A';

				if(theSecret == 91){
					theSecret = (int)' ';
				}

				justWork[l] = (char)theSecret;
			  }

			charsWritten = 0;
			  while(charsWritten < inputLength){
				  charsWritten += send(establishedConnectionFD, justWork, inputLength - charsWritten, 0);
				  if(charsWritten < 0){
					error("ERROR writing to socket");
				  }
			  }

			  close(establishedConnectionFD);
			  return 0;
	  	}
		else{
			close(establishedConnectionFD);
			return (1);
//			continue;
		}
	  }
	//Parent process is here
 }

  close(listenSocketFD);


  return 0;
}
