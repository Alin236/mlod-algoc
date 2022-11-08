#include "../V1/linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void afficheElement(Element e){
    Music music = (Music) e;
    printf("(%s, %s, %s, %s, %i, %i, %i)", music->name, music->artist, music->album, music->genre, music->discNumber, music->trackNumber, music->year);
}

void detruireElement(Element e){
    free((Music) e);
}

bool equalsElement(Element e1, Element e2){
    Music music1 = (Music) e1;
    Music music2 = (Music) e2;
    bool resultat = true;
    resultat = resultat && strcmp(music1->name, music2->name) == 0;
    resultat = resultat && strcmp(music1->artist, music2->artist) == 0;
    resultat = resultat && strcmp(music1->album, music2->album) == 0;
    resultat = resultat && strcmp(music1->genre, music2->genre) == 0;
    resultat = resultat && music1->discNumber == music2->discNumber;
    resultat = resultat && music1->trackNumber == music2->trackNumber;
    resultat = resultat && music1->year == music2->year;
    return resultat;
}

Music creerMusic(char* name, char* artist, char* album, char* genre, int discNumber, int trackNumber, int year){
    Music music = malloc(sizeof(MusicElement));
    music->name = name;
    music->artist = artist;
    music->album = album;
    music->genre = genre;
    music->discNumber = discNumber;
    music->trackNumber = trackNumber;
    music->year = year;
    return music;
}

bool compareMusicYear(Music music1, Music music2){
    return music1->year < music2->year;
}