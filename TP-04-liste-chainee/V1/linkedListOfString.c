#include "linkedList.c"
#include <string.h>

void afficheElement(Element e){
    printf("%s ",e);
}

void detruireElement(Element e){}

bool equalsElement(Element e1, Element e2){
    return strcmp(e1, e2) == 0;
}