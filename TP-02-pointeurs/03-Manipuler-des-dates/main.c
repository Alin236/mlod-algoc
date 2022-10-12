#include <stdlib.h>
#include <stdio.h>

typedef enum {
    Janvier = 1,
    Fevrier, 
    Mars,
    Avril,
    Mai,
    Juin,
    Juillet,
    Aout,
    Septembre,
    Octobre,
    Novembre,
    Decembre
    } Mois;

typedef struct {
    int jour;
    Mois mois;
    int annee;
    } Date;

void initialiseDate(Date *);
void afficheDate(Date *);
Date creerDateParCopie();

int main(){
    Date d;
    initialiseDate(&d); //Pourquoi a t-on ajouté un &?
    afficheDate(&d);

    //Date d;
    d = creerDateParCopie();
    afficheDate(&d);
    return EXIT_SUCCESS;
}

void initialiseDate(Date *d){
    scanf("%i%i%i", &(d->jour), &(d->mois), &(d->annee));
}

void afficheDate(Date *d){
    printf("%i/%i/%i", d->jour, d->mois, d->annee);
}

Date creerDateParCopie(){
    Date d;
    scanf("%i%i%i", &(d.jour), &(d.mois), &(d.annee));
    return d;
}