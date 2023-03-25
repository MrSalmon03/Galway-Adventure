//Conor Salmon, 22402456, 21st of March 2023

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#pragma warning(disable:4996) 

typedef struct {
    char description[100];
    int n, s, e, w, in, out, quit, help, look;
} location;

location locations[40];
int numLocations = 0;
char locationsFile[] = "C:\\Users\\conor\\OneDrive\\Desktop\\adventure_locations.txt"; //This is the file containing the locations.

FILE* openFileForReading(char* filename) { //Here, the file is opened and read.
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL)
        printf("Could not open %s\n", filename); //If the file isn't found, an error message is given.
    return fptr;
}

bool readLocations() {
    FILE* fptr = openFileForReading(locationsFile);
    if (fptr == NULL) {
        return false;
    }

    numLocations = 0;
    int readHeaderLines = 0;
    char line[200];
    while (fgets(line, 99, fptr) != NULL) {
        if (readHeaderLines < 2) { //The first two rows, which contain headers, are ignored.
            readHeaderLines++;
        }
        else {
            numLocations++;
            location l;
            int locNum;
            sscanf(line, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%[^\t]\n", &locNum, &l.n, &l.s, &l.e, &l.w, &l.in, &l.out, l.description); //Information is taken in from the document.
            locations[numLocations] = l; 
        }
    }

    return true;
}

int main() {
    if (readLocations()) {
        printf("Successfully read %d locations from file\n", numLocations);
    }
    int gameOver = 0; //This integer exists to check and see if the player has lost or wants to quit the game. When they do, it will change to 1 and the game loop will end.
    char command[10];
    location l;
    int playerLocation = 1; //The player begins in the first location, the NUIG campus.
    printf("Type help for a list of commands.\n"); //The player is informed of the help option, which can be seen below.
    while (gameOver != 1) { //This is the game loop. It will repeat until the player gets a game obver or chooses to quit.
        location currentLocation = locations[playerLocation];
        printf("You are %s\n", currentLocation.description); //The player is told where they are.
        printf("Enter a command: \n");
        scanf("%s", &command); //The player's command is taken in.

        if (!strcmp(command, "n")) { //This if statement checks to see if the command was to go north.
            if (playerLocation == 1) {
                playerLocation = 5;
            }
            else if (playerLocation == 8) {
                playerLocation = 1;
            }
            else if (playerLocation == 4) {
                playerLocation = 1;
            }
            else if (playerLocation == 9) {
                gameOver++;
                printf("You swim aimlessly for hours. In the end, you tire and the sea claims you...");
            }
            else { //If the player is in the northernmost area, it won't allow them to go any further north. The same applies to the other movement commands.
                printf("You can't go north from here.\n");
            }
        }

        else if (!strcmp(command, "s")) { //This if statement checks to see if the command was to go south.
            if (playerLocation == 1) { //If the player is able to go north from their current location, the location is updated. 
                playerLocation = 4;
            }
            else if (playerLocation == 6) { 
                playerLocation = 8;
            }
            else if (playerLocation == 5) {
                playerLocation = 1;
            }
            else if (playerLocation == 9) {
                gameOver++;
                printf("You swim aimlessly for hours. In the end, you tire and the sea claims you...");
            }
            else {
                printf("You can't go south from here.\n");
            }
        }

        else if (!strcmp(command, "w")) { //This if statement checks to see if the command was to go west.
            if (playerLocation == 1) {
                playerLocation = 7;
            }
            else if (playerLocation == 6) {
                playerLocation = 1;
            }
            else if (playerLocation == 5) {
                playerLocation = 7;
            }
            else if (playerLocation == 4) {
                playerLocation = 7;
            }
            else if (playerLocation == 8) {
                playerLocation = 4;
            }
            else if (playerLocation == 9) {
                gameOver++;
                printf("You swim aimlessly for hours. In the end, you tire and the sea claims you...");
            }
            else {
                printf("You can't go west from here.\n");
            }
        }
        else if (!strcmp(command, "e")) { //This if statement checks to see if the command was to go east.
            if (playerLocation == 1) {
                playerLocation = 6;
            }
            else if (playerLocation == 7) {
                playerLocation = 1;
            }
            else if (playerLocation == 5) {
                playerLocation = 6;
            }
            else if (playerLocation == 4) {
                playerLocation = 8;
            }
            else if (playerLocation == 9) {
                gameOver++;
                printf("You swim aimlessly for hours. In the end, you tire and the sea claims you...");
            }
            else {
                printf("You can't go east from here.\n");
            }
        }

        else if (!strcmp(command, "in")) { //This if statement checks to see if the command was to enter a building or the sea.
            if (playerLocation == 1) {
                playerLocation = 2;
            }
            else if (playerLocation == 2) {
                playerLocation = 3;
            }
            else if (playerLocation == 4) {
                playerLocation = 9;
            }
            else if (playerLocation == 9) {
                playerLocation = 9;
                printf("You dive deep underwater. Incredible. Eventually you resurface.\n");
            }
            else {
                printf("You can't go in from here.\n");
            }
        }

        else if (!strcmp(command, "out")) { //This if statement checks to see if the command was to exit a building or the sea.
            if (playerLocation == 2) {
                playerLocation = 1;
            }
            else if (playerLocation == 3) {
                playerLocation = 2;
            }
            else if (playerLocation == 9) {
                playerLocation = 4;
            }
            else {
                printf("You can't go out from here.\n");
            }
        }

        else if (!strcmp(command, "look")) { //This if statement checks to see if the command was to look around.
            printf("You look around.\n"); //This code won't move the player. The location description will be repeated at the top of the loop.
        }

        else if (!strcmp(command, "quit")) { //When the player wants to quit, they can type it here and the loop will end.
            gameOver++;
            printf("Bye! Thanks for playing!");
        }

        else if (!strcmp(command, "help")) { //If the player wants help, they can type help and all possible commands will be printed.
            printf("The commands I know are: Move north, south, east or west (n, s, e, w), go into/out of a building/the sea (in, out), quit the game (quit).\n");
        }

        else { //This code will run if a command is entered that the program doesn't recognize.
            printf("I don't know the command %s. Please try something else.\n", command);
        }
    }
}