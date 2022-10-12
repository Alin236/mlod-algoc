#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    uint8_t numLines;
    uint8_t numColumns;
    int **value;
} Matrix;

#define SIZE 5

void matrix_mult(int64_t[][SIZE],int64_t[][SIZE],int64_t[][SIZE]);
void matrix_print(int64_t[][SIZE]);

int main(void) {
    //matrices en ligne * colonne
    int64_t matrice1[][SIZE]={{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5}};
    int64_t matrice2[][SIZE]={{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10}};
    int64_t matriceResultat[SIZE][SIZE];

    matrix_mult(matriceResultat,matrice1,matrice2);
    matrix_print(matriceResultat);

    return EXIT_SUCCESS;
}

void matrix_mult(int64_t mResultat[][SIZE], int64_t matrice1[][SIZE], int64_t matrice2[][SIZE]){
    int64_t c;
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            c = 0;
            for(int k=0; k<SIZE; k++){
                c += matrice1[i][k] * matrice2[k][j];
            }
            mResultat[i][j] = c;
        }
    }
}

void matrix_print(int64_t mResultat[][SIZE]){
    for(int i = 0; i<SIZE; i++){
        printf("(");
        for(int j = 0; j<SIZE; j++){
            printf("%li", mResultat[i][j]);
        }
        printf(")\n");
    }
}
