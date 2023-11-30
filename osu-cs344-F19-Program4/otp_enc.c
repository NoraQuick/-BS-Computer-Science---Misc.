#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


void error(const char *msg) {
	//Print the error message passed in
	perror(msg);

	//Exit
	exit(0);
}


int main(int argc, char* argv[]) {
	//Initialize the vairables used in this function
	int socketFD;
	int portNumber;
	int charsWritten;
	int charsRead;
	int encLength;
	int keyLength;
	int i;
	int j;
	int k;
	int l;
	int m;
	int n;
	char character;
	char buffer[256];
	char* encInput = NULL;
	char* keyInput = NULL;
	FILE* readEncInfo;
	FILE* readKeyInfo;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	ssize_t bufSize;


	//For the length of the string
	for(k = 0; k < 256; k++){
		//Clear the buffer out
		buffer[k] = '\0';
	}

	
	//If there aren't enough arguments passed in
	if (argc < 4) {
		//Print an error
		fprintf(stderr,"USAGE: %s hostname port\n", argv[0]);
		
		//Exit
		exit(0);
	}


	//Set the memory of the server address
	memset((char*)&serverAddress, '\0', sizeof(serverAddress));
	

	//Get the port number the user want's to use
	portNumber = atoi(argv[3]);


	//Set up the server address
	//Create a network-capavle socket
	serverAddress.sin_family = AF_INET;
	//Store the port number
	serverAddress.sin_port = htons(portNumber);
	//Convert the machine name into a special form of address
	serverHostInfo = gethostbyname("localhost");

	//If there is no info in serverHostInfo
	if (serverHostInfo == NULL) {
		//Print an error
		fprintf(stderr, "CLIENT: ERROR, no such host\n");
		
		//Exit
		exit(0);
	}


	//Copy the address
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length);


	//Set up the socket
	//Create the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	//If the socket is not made
	if (socketFD < 0){
		//Call the error function to print the error
		error("CLIENT: ERROR opening socket");
	}

	//If the server does not connect
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
		//Call the error function to print the error
		error("CLIENT: ERROR connecting");
	}


	//Read in the first file which should be the plaintext
	readEncInfo = fopen(argv[1], "r");
	//If no information was read
	if(readEncInfo == NULL){
		//Call the error function to print the error
		fprintf(stderr, "Could not read plaintext.");
		//Exit
		exit(0);
	}
	

	getline(&encInput, &bufSize, readEncInfo);
	
	encLength = strlen(encInput) - 1;
	fclose(readEncInfo);


	//Read in the second file which should be the key
	readKeyInfo = fopen(argv[2], "r");
	//If no information was read
	if(readKeyInfo == NULL){
		//Call the error function to print the error
		fprintf(stderr, "Could not read key.");
		//Exit
		exit(0);
	}

	getline(&keyInput, &bufSize, readKeyInfo);

	keyLength = strlen(keyInput) - 1;

	fclose(readKeyInfo);

//	printf("keyInfo: %s\n", keyInput);
	
	//If the length of the encryption file is not the same length as the key
	//file
	if(keyLength < encLength){
		//Call the error function to print the error
		fprintf(stderr, "ERROR: key is too-small\n");
		//Exit
		exit(1);
	}

	for(i < 0; i < encLength; i++){
		if(encInput[i] != ' '){
			if(encInput[i] < 65 || encInput[i] > 90){
				fprintf(stderr, "Not a valid character\n");
				exit(1);
			}
		}
	}
	for(j < 0; j < keyLength; j++){
		if(keyInput[j] != ' '){
			if(keyInput[j] < 65 || keyInput[j] > 90){
				fprintf(stderr, "Not a valid character\n");
				exit(1);
			}
		}
	}


	charsWritten = send(socketFD, "E", 1, 0);
	if(charsWritten < 0){
		error("No");
	}

	charsRead = recv(socketFD, buffer, 1, 0);
	if(charsRead < 0){
		error("CLIENT: ERROR reading to socket");
	}
	if(strcmp(buffer, "N") == 0){
		fprintf(stderr, "otp_enc cannot connect to otp_dec_d\n");
		exit(2);
	}
	
	//Sprintf so the other file can get the info found in this file
	sprintf(buffer, "%s%d", "gotit", encLength);


	//Send a success message
	charsWritten = send(socketFD, buffer, strlen(buffer), 0);
	//If no characters are written
	if(charsWritten < 0){
		//Print an error
		error("CLIENT: ERROR written to socket");
	}

	
	//For the size of buffer
	for(l = 0; l < 6; l++){
		//Make that index null
		buffer[l] = '\0';
	}


	//Read in the information
	charsRead = recv(socketFD, buffer, 39, 0);
	//If nothing is read in
	if(charsRead < 0){
		//Send an error
		error("CLIENT: ERROR reading from socket");
	}

	
	charsWritten = 0;
	while(charsWritten < encLength){
		//Send a success message
		charsWritten += send(socketFD, encInput, encLength - charsWritten, 0);
		//If nothing was written
		if(charsWritten < 0){
			//Send an error
			error("CLIENT: ERROR writing to socket");
		}
	}


	//Read in message
	charsRead = recv(socketFD, buffer, 39, 0);
	//If nothing is read in
	if(charsRead < 0){
		//Print an error
		error("CLIENT: ERROR reading from socket");
	}


	charsWritten = 0;
	while(charsWritten < encLength){
		//Write to the server
		charsWritten += send(socketFD, keyInput, encLength - charsWritten, 0);
		//If there was an error writing to the server
		if (charsWritten < 0){
			//Call the error function to print the error
			error("CLIENT: ERROR writing to socket");
		}
	}


	//Read in message
	charsRead = recv(socketFD, buffer, 39, 0);
	//If nothing was read in
	if(charsRead < 0){
		//Send an error
		error("CLIENT: ERROR reading from socket");
	}


	//For the number of key indexs
	for(n = 0; n < 39; n++){
		//Make that index null
		buffer[n] = '\0';
	}
	
	char encryption[encLength+1];
	memset(encryption, '\0', encLength+1);
	charsRead = 0;
	while(charsRead < encLength){
		//Read in message
		charsRead += recv(socketFD, encryption, encLength - charsRead, 0);
		//If nothing was read in
		if(charsRead < 0){
			//Send an error
			error("CLIENT: ERROR reading from socket");
		}
	}


	//Print out the encrypted message
	fprintf(stdout, "%s\n", encryption);


	//Close the socket
	close(socketFD);


	//Return 0
	return 0;
}
