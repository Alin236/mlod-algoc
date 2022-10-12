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
Date *newDate();

int main(){
    printf("initialiseDate\n");
    Date d;
    initialiseDate(&d); //Pourquoi a t-on ajouté un &?
    afficheDate(&d);

    printf("\ncreerDateParCopie\n");
    //Date d;
    d = creerDateParCopie();
    afficheDate(&d);

    printf("\nnewDate\n");
    Date *date;
    date = newDate();
    afficheDate(date);
    //...
    free(date);

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

Date *newDate(){
    return (Date *) malloc(sizeof(Date));
}