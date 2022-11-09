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
String string_new_aux(char*, String);

int main(){

    String s = string_new("HELLO !");
    string_affiche_r(s);

    return EXIT_SUCCESS;
}

String string_new(char* c){
    String s = NULL;
    s = string_new_aux(c, s);
    return s;
}

String string_new_aux(char* c, String s){
    if(s == NULL){
        s = string_creer(c);
        return s;
    }
    int chunkSize = strlen(c) <= CHUNK_SIZE_MAX ? strlen(c) : CHUNK_SIZE_MAX;
    s->next = string_new_aux(c+chunkSize, s);
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