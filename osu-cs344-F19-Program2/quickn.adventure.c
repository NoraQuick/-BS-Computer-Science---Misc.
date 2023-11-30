//Adventure file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Rooms(){
	char roomName[9];
	char conn[6][9];
	int numConnections;
	char roomType[11];
};

void movement();
void playGame();

int main(){
	movement();

	return 0;
}

void movement(){
	int moves = 0;
	char storeRoom[100];
	struct Rooms* rooms = malloc(sizeof(struct Rooms)*7);

	void playGame(struct rooms);

	/*printf("%s\n", "CURRENT LOCATION: ");
	printf("%s\n", "POSSIBLE CONNECTIONS: ");
	
	int i;
	int k;
	int inc = 0;
	for(i=0; i < 5; i++){
		printf("%s", "WHERE TO? ");
		scanf("%s", room);
		for(k=0; k < 5; k++){
			strcpy(storeRoom[k], room);
		}
		inc++;
		moves++;
	}
	int j;
	for(j=0; j < inc; j++){
		printf("%s\n", storeRoom[j]);
	}*/
}

void findDir() {
	DIR* directory;

	directory = opendir("./");

	if(directory == NULL){
		prinf("%s", "No build directory exists");
	}

	while(readdir(directory)) {
		if(strcmp(/*filename*/, "quickn.rooms.") == 0) {
			//check newest time into int

			if(/*int != NULL*/){
				strcpy(/*tempname, filename*/);
			}
		}
	}

	closedir(directory);
}

void readFiles(){
	int i = 0;
	int roomsRead = 0;
	DIR* directory;
	FILE* file;

	directory = findDir();

	for(i; roomsRead < 7; i++){
		Rooms[roomsRead].numConnections = 0;
	}
}

void playGame(struct rooms){
	int i;
	char currentRoom[9];

	printf("%s%s\n ", "CURRENT LOCATION: ", rooms[currentRoom].roomName);
	printf("%s", "POSSIBLE CONNECTIONS:");

	for(i=0; i < rooms[currentRoom].numConnections; i++){
		printf(" %s,", rooms[currentRoom].numConnections[i]);
	}

	printf("%s", "WHERE TO? ");
}
