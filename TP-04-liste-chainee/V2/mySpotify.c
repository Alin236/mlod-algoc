// clang -W -Wall -std=c99 linkedListOfMusic.c ../V1/linkedList.c mySpotify.c -o mySpotify

// clang -W -Wall -Wno-unused-parameter -std=c99 linkedListOfMusic.c ../V1/linkedList.c mySpotify.c -o mySpotify

// valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./mySpotify

#include "../V1/linkedList.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]){
    char* fileName = "music.csv";
    if(argc == 2){
		fileName = argv[1];
	}

    FILE* f;
    f = fopen(fileName,"r");
    if(f==NULL) {
        printf ("Erreur ouverture du fichier\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}