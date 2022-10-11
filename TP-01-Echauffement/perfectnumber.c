#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPerfect(int);

int main(void){
    int N = 500;
    int number = 1;
    for(int k=0; k<=N; k++){
        if(isPerfect(k)){
            printf("Numéro parfait n°%d : %d\n", number, k);
            number++;
        }
    }
    return EXIT_SUCCESS;
}

bool isPerfect(int n){
    int somme = 0;
    for(int i=1; i<n; i++){
        if(n%i == 0)
            somme += i;
    }
    return somme == n;
}