#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long TypeEntier;

TypeEntier factorielle(TypeEntier);

int main(void){
    for(TypeEntier i=1; i<=15; i++){
        printf("%llu! = %llu\n", i, factorielle(i));
    }
    return EXIT_SUCCESS;
}

TypeEntier factorielle(TypeEntier n){
    if(n == 1)
        return 1;
    return n * factorielle(n-1);
}