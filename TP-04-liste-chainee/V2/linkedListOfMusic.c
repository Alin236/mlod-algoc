#include "../V1/linkedList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* artist;
    char* album;
    char* genre;
    int discNumber;
    int trackNumber;
    int year;
} MusicElement;

typedef MusicElement* Music;

void afficheElement(Element e){}

void detruireElement(Element e){}

bool equalsElement(Element e1, Element e2){}

Music creerMusic(char* name, char* artist, char* album, char* genre, int discNumber, int trackNumber, int year){
    Music music = malloc(sizeof(MusicElement));
    music->name = name;
    music->artist = artist;
    music->album = album;
    music->genre = genre;
    music->discNumber = discNumber;
    music->trackNumber = trackNumber;
    music->year = year;
}
