#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
    unsigned short jour;
    Mois mois;
    unsigned short annee;
    } Date;

void initialiseDate(Date *);
void afficheDate(Date *);
Date creerDateParCopie();
Date *newDate();
unsigned int nbreJours(Mois mois, unsigned int annee);
bool dateValide(Date uneDate);

int main(){
    printf("Version 1 : initialisation d'une date allouée statiquement\n");
    Date d;
    initialiseDate(&d); //Pourquoi a t-on ajouté un &?
    afficheDate(&d);

    printf("\nVersion 2 : recopie d'une date allouée statiquement\n");
    //Date d;
    d = creerDateParCopie();
    afficheDate(&d);

    printf("\nVersion 3 : allocation dynamique de date\n");
    Date *date;
    date = newDate();
    afficheDate(date);
    free(date);
    date = NULL;

    return EXIT_SUCCESS;
}

void initialiseDate(Date *d){
    scanf("%hi%i%hi", &(d->jour), &(d->mois), &(d->annee));
}

void afficheDate(Date *d){
    printf("%hi/%i/%hi", d->jour, d->mois, d->annee);
}

Date creerDateParCopie(){
    Date d;
    scanf("%hi%i%hi", &(d.jour), &(d.mois), &(d.annee));
    return d;
}

Date *newDate(){
    Date *d = (Date *) malloc(sizeof(Date));
    scanf("%hi%i%hi", &(d->jour), &(d->mois), &(d->annee));
    return d;
}

unsigned int nbreJours(Mois mois, unsigned int annee){
    return 31;
}

bool dateValide(Date uneDate){
    unsigned int maxj = nbreJours(uneDate.mois, uneDate.mois);
    if(uneDate.jour < 1 || uneDate.jour > maxj)
        return false;
    if(uneDate.mois < 1 || uneDate.mois > 12)
        return false;
    return true;
}