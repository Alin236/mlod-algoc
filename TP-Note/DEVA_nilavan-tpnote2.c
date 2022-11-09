// clang -W -Wall DEVA_nilavan-tpnote2.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHUNK_SIZE_MAX 5

struct StringElement_s {
    struct StringElement_s* next;
    int chunkSize;
    char chunk[CHUNK_SIZE_MAX];
};

typedef struct StringElement_s StringElement;

typedef StringElement* String;

String string_new(char*);


//bool string_estVide(String);
void string_affiche_r(String);
String string_creer(char*);

int main(){

    String s = string_new("HELLO !");
    string_affiche_r(s);

    return EXIT_SUCCESS;
}

String string_new(char* c){
    String s = string_creer(c);
    String suiv = s->next;
    int totalSize = strlen(c);
    for(int i=CHUNK_SIZE_MAX; i<totalSize; i+=CHUNK_SIZE_MAX){
        suiv = string_creer(c+(i*CHUNK_SIZE_MAX));
        suiv = suiv->next;
    }
    return s;
}

void string_affiche_r(String s){
    if(s == NULL)
        return;
    printf("%i : %s\n", s->chunkSize, s->chunk);
}

String string_creer(char* c){
    String s = malloc(sizeof(StringElement));
    s->next = NULL;
    s->chunkSize = strlen(c) <= CHUNK_SIZE_MAX ? strlen(c) : CHUNK_SIZE_MAX;
    for(int i=0; i<s->chunkSize; i++)
        s->chunk[i] = c[i];
    return s;
}