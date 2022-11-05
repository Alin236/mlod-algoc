// clang -W -Wall -std=c99 linkedListOfString.c main.c -o main
// clang -W -Wall -Wno-unused-parameter -std=c99 linkedListOfString.c main.c -o main

#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
	Liste l, p;

	l = NULL;
	printf("estVide(l) = %s\n",estVide(l)?"TRUE":"FALSE");

	l = ajoutTete("1",l);
	l = ajoutTete("2",l);
	l = ajoutTete("abcd",l);
	l = ajoutTete("1",l);
	l = ajoutTete("5",l);
	l = ajoutTete("6",l);
	l = ajoutTete("2",l);
	l = ajoutTete("abcd",l);
	l = ajoutTete("1",l);

	afficheListe_i(l);

	ajoutFin_r("99",l);
	afficheListe_i(l);

	ajoutFin_r("100",l);
	afficheListe_i(l);

	p = cherche_i("200",l);
	printf("cherche_i(\"200\") : %s\n",estVide(p)?"pas trouve":"[ERREUR] trouve !!!");

	p = cherche_i("99",l);
	if(estVide(p))
		printf("cherche_i(\"99\") : [ERREUR] pas trouve \n");
	else {
		printf("cherche_i(\"99\") : trouve ");
		afficheElement(p->val);
		printf("\n");
	}

	p = cherche_r("200",l);
	printf("cherche_r(\"200\") : %s\n",estVide(p)?"pas trouve":"[ERREUR] trouve !!!");

	p = cherche_r("99",l);
	if(estVide(p))
		printf("cherche_r(\"99\") : [ERREUR] pas trouve \n");
	else {
		printf("cherche_r(\"99\") : trouve ");
		afficheElement(p->val);
		printf("\n");
	}

	printf("retirePremier_i(\"1\")   : ");
	l = retirePremier_i("1",l);
	afficheListe_r(l);

	printf("retirePremier_i(\"1\")   : ");
	l = retirePremier_i("1",l);
	afficheListe_r(l);

	printf("retirePremier_i(\"100\") : ");
	l = retirePremier_i("100",l);
	afficheListe_r(l);

	printf("retirePremier_r(\"abcd\")   : ");
	l = retirePremier_r("abcd",l);
	afficheListe_r(l);

	printf("retirePremier_r(\"abcd\")   : ");
	l = retirePremier_r("abcd",l);
	afficheListe_r(l);

	printf("retirePremier_r(\"99\")  : ");
	l = retirePremier_r("99",l);
	afficheListe_r(l);

	detruire_r(l);
	return EXIT_SUCCESS;
}