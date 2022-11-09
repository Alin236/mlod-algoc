#pragma once

#include <stdbool.h>
#include "linkedList.h"

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

Music creerMusic(char* name, char* artist, char* album, char* genre, int discNumber, int trackNumber, int year);

bool compareMusicYear(Music music1, Music music2);

Liste insererMusicDansListeOrdonnee(Liste l, Music m);

Liste sortListeMusic(Liste l);