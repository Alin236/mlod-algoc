#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int* repeat(int*, int*);

int* repeat(int* t1, int* t2){
    int size = SIZE;
    int tailleFinale = 0;
    for(int i=0; i<size; i++){
        tailleFinale += t1[i];
    }
    int* resultat = calloc(tailleFinale, sizeof(int));
    int comteur = 0;
    for(int i=0; i<size; i++){
        for(int j=0; j<t1[i]; j++){
            resultat[comteur] = t2[i];
            comteur += 1;
        }
    }
    return resultat;
}

int main(){
    int size = SIZE;
    int* t1 = calloc(size, sizeof(int));
    t1[0] = 1;
    t1[1] = 2;
    t1[2] = 4;

    int* t2 = calloc(size, sizeof(int));
    t2[0] = 10;
    t2[1] = 3;
    t2[2] = 8;

    int* resultat = repeat(t1, t2);

    int tailleFinale = 0;
    for(int i=0; i<size; i++){
        tailleFinale += t1[i];
    }

    printf("(");
    for(int i=0; i<tailleFinale; i++){
        printf("%i", resultat[i]);
        if(i != tailleFinale-1){
            printf(",");
        }
    }
    printf(")\n");

    free(t1);
    free(t2);
    free(resultat);

    return 1;
}