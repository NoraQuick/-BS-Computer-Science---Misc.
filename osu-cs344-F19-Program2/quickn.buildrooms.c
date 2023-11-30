//Rooms file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

//char* roomArray[] = { "Aerary", "Ballroom", "Closet", "Dungeon", "Kitchen", "Lobby", "Sunroom", "Bedroom", "Office", "Hell" };

struct Rooms {
	char roomName[9];
	int numConnections;
	char connRoom[6][9];
	char roomType[11];
};

char* roomArray[] = { "Aerary", "Ballroom", "Bedroom", "Closet", "Dungeon", "Hell", "Kitchen", "Lobby", "Office", "Sunroom" };
struct Rooms playableRooms[7];

void assignRoomName();
int checkRoom(char*);
void assignRoomType();
void addRandomConnection();
struct Rooms* getRandomRoom();
void connectRoom(struct Rooms*, struct Rooms*);
void creatingConnections();
void displayRooms();
int isRoomFull();
int canAddConnectionFrom(struct Rooms*);
int isSameRoom(struct Rooms*, struct Rooms*);
int connectionAlreadyExists(struct Rooms*, struct Rooms*);

int main() {
	srand(time(NULL));

	int pid = getpid();

	char* tempDirName = "quickn.rooms.";
	char dirName[20];

	sprintf(dirName, "%s%d", tempDirName, pid);
	if(mkdir(dirName) != 0){
		printf("%s", "Dir was not made.");
	}

	assignRoomName();
	assignRoomType();
	creatingConnections();

	displayRooms(dirName);

	return 0;
}

void assignRoomName(){
	int i = 0;
	int roomNum = 0;

	for(i=0; i < 7; i++){
		do {
			roomNum = rand()%(9 + 1 - 0) + 0;
		}
		while(checkRoom(roomArray[roomNum]) == 0);
			strcpy(playableRooms[i].roomName, roomArray[roomNum]);
			roomNum = 0;
	}
}

int checkRoom(char* largeArray){
	int i = 0;
	
	for(i; i < 7; i++){
		if(strcmp(largeArray, playableRooms[i].roomName) == 0){
			return 0;			
		}
	}
	return 1;
}

void assignRoomType(){
	int i = 0;

	char* roomTypeStart = "START_ROOM";
	char* roomTypeMid = "MID_ROOM";
	char* roomTypeEnd = "END_ROOM";

	int randStart = rand()%(6 + 1 - 0) + 0;
	int randEnd = rand()%(6 + 1 - 0) + 0;

	if(randEnd == randStart){
		randEnd = rand()%(6 + 1 - 0) + 0;
	}

	for(i; i < 7; i++){
		if(i == randStart){
			strcpy(playableRooms[i].roomType, roomTypeStart);	
		}
		else if(i == randEnd){
			strcpy(playableRooms[i].roomType, roomTypeEnd);
		}
		else{
			strcpy(playableRooms[i].roomType, roomTypeMid);
		}
	}
}

void creatingConnections(){
	while(isRoomFull() == 0) {
		addRandomConnection();
	}
}

int isRoomFull() {
	int i = 0;

	for(i; i < 7; i++){
		if(playableRooms[i].numConnections < 3){
			return 0;
		}
	}
	return 1;
}

void addRandomConnection() {
	struct Rooms* A;
	struct Rooms* B;

	while(1){
		A = getRandomRoom();

		if(canAddConnectionFrom(A) == 1){
			break;
		}
	}

	do{
		B = getRandomRoom();
	}
	while(canAddConnectionFrom(B) == 0 || isSameRoom(A, B) == 1 || connectionAlreadyExists(A, B) == 1);
	connectRoom(A, B);
	connectRoom(B, A);
}

struct Rooms* getRandomRoom(){
	int i = 0;
	struct Rooms* theRandRoom;
	int randRoom = rand()%((6 + 1 - 3) + 3);

	return &playableRooms[randRoom];
}

int canAddConnectionFrom(struct Rooms* x){
	if(x->numConnections < 6){
		return 1;
	}
	return 0;
}

int connectionAlreadyExists(struct Rooms* x, struct Rooms* y){
	int i = 0;

	for(i; i < x->numConnections; i++){
		if(strcmp(x->connRoom[i], y->roomName) == 0)
			return 1;
	}
	return 0;
}

void connectRoom(struct Rooms* x, struct Rooms* y){
	strcpy(x->connRoom[x->numConnections], y->roomName);
	x->numConnections++;
}

int isSameRoom(struct Rooms* x, struct Rooms* y){
	if(strcmp(x->roomName, y->roomName) == 0){
		return 1;
	}
	return 0;
}

void displayRooms(char* dirName){
	int i = 0;
	int j = 0;

	for(i; i < 7; i++){
		char pathName[20];

		sprintf(pathName, "%s/%s_room", dirName, playableRooms[i].roomName);

		FILE* fd = fopen(pathName, "w");

		fprintf(fd, "%s%s\n", "ROOM NAME: ", playableRooms[i].roomName);

		for(j=0; j < playableRooms[i].numConnections; j++){
			fprintf(fd, "%s%d%s%s\n", "CONNECTIONS ", j+1, ": ", playableRooms[i].connRoom[j]);
		}

		fprintf(fd, "%s%s\n", "ROOM TYPE: ", playableRooms[i].roomType);
	}
}
