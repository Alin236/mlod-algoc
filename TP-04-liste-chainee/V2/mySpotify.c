// clang -W -Wall linkedListOfMusic.c ../V1/linkedList.c mySpotify.c -o mySpotify

// clang -W -Wall -Wno-unused-parameter linkedListOfMusic.c ../V1/linkedList.c mySpotify.c -o mySpotify

// valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./mySpotify

#include "../V1/linkedList.h"
#include "linkedListOfMusic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
    char* fileName = "music.csv";
    if(argc == 2){
		fileName = argv[1];
	}

    FILE* file;
    file = fopen(fileName,"r");
    if(file==NULL) {
        printf ("Erreur ouverture du fichier\n");
        return EXIT_FAILURE;
    }

    char nextLine[250];
    fgets(nextLine, 250, file);

    char* copyOfLine;
    char *name, *artist, *album, *genre;
    int discNumber, trackNumber, year;
    Music music;
    Liste liste;
    while(fgets(nextLine, 255, file) != NULL){
        copyOfLine = strdup(nextLine);
        name = strsep(&copyOfLine, ",");
        artist = strsep(&copyOfLine, ",");
        album = strsep(&copyOfLine, ",");
        genre = strsep(&copyOfLine, ",");
        discNumber = atoi(strsep(&copyOfLine, ","));
        trackNumber = atoi(strsep(&copyOfLine, ","));
        year = atoi(strsep(&copyOfLine, ","));
        music = creerMusic(name, artist, album, genre, discNumber, trackNumber, year);
        afficheElement(music);
        liste = ajoutFin_i((void *) music, liste);
    }
    afficheListe_r(liste);

    return EXIT_SUCCESS;
}