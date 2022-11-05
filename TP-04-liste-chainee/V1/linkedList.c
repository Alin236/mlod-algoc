#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

#define TODO NULL;

// retourne vrai si l est vide et faux sinon
bool estVide(Liste l) {
	return l == NULL;
}

// créer une liste d'un seul élément contenant la valeur v
Liste creer(Element v){
	Liste l = malloc(sizeof(Cellule));
	if(l!=NULL){
		l->val = v;
		l->suiv = NULL;
	}
	return l;
}

// ajoute l'élément v en tete de la liste l
Liste ajoutTete(Element v, Liste l) {
	Liste newL = creer(v);
	newL->suiv = l;
	return newL;
}

// affiche tous les éléments de la liste l
// Attention, cette fonction doit être indépendante du type des éléments de la liste
// utiliser une fonction annexe affiche_element
// Attention la liste peut être vide !
// version itérative
void afficheListe_i(Liste l) {
	while(!estVide(l)){
		afficheElement(l->val);
		l = l->suiv;
	}
	printf("\n");
}

// version recursive
void afficheListe_r(Liste l) {
	if(!estVide(l)){
		afficheElement(l->val);
		afficheListe_r(l->suiv);
		return;
	}
	printf("\n");
}

// Détruit tous les éléments de la liste l
// version itérative
void detruire_i(Liste l) {
	while(!estVide(l)){
		detruireElement(l->val);
		l = l->suiv;
	}
}

// version récursive
void detruire_r(Liste l) {
	if(!estVide(l)){
		detruireElement(l->val);
		detruire_r(l->suiv);
	}
}

// retourne la liste dans laquelle l'élément v a été ajouté en fin
// version itérative
Liste ajoutFin_i(Element v, Liste l) {
	Liste head = l;
	if(!estVide(l)){
		while(!estVide(l->suiv)){
			l = l->suiv;
		}
		l->suiv = creer(v);
	}
	return head;
}

// version recursive
Liste ajoutFin_r(Element v, Liste l) {
	if(estVide(l)){
		l = creer(v);
		return(l);
	}
	if(estVide(l->suiv)){
		l->suiv = creer(v);
		return(l);
	}
	ajoutFin_r(v, l->suiv);
	return l;
}

// Retourne un pointeur sur l'élément de la liste l contenant la valeur v ou NULL
// version itérative
Liste cherche_i(Element v,Liste l) {
	while(!estVide(l) && !equalsElement(v, l->val)){
		l = l->suiv;
	}
	return l;
}

// version récursive
Liste cherche_r(Element v,Liste l) {
	if(!estVide(l) && !equalsElement(v, l->val)){
		return cherche_r(v, l->suiv);
	}
	return l;
}

// Retourne la liste modifiée dans la laquelle le premier élément ayant la valeur v a été supprimé
// ne fait rien si aucun élément possède cette valeur
// version itérative
Liste retirePremier_i(Element v, Liste l) {
	Liste head = l;
	if(estVide(l)){
		return head;
	}
	if(equalsElement(v, l->val)){
		return l->suiv;
	}
	while(!estVide(l->suiv) && !equalsElement(v, l->suiv->val)){
		l = l->suiv;
	}
	if(estVide(l->suiv)){
		return head;
	}
	l->suiv = l->suiv->suiv;
	return head;
}


// version recursive
Liste retirePremier_r(Element v, Liste l) {
	if(estVide(l)){
		return l;
	}
	if(equalsElement(v, l->val)){
		return l->suiv;
	}
	if(equalsElement(v, l->suiv->val)){
		l->suiv = l->suiv->suiv;
		return l;
	}
	retirePremier_r(v, l->suiv);
	return l;
}


void afficheEnvers_r(Liste l) {
	if(estVide(l)){
		return;
	}
	afficheEnvers_r(l->suiv);
	afficheElement(l->val);
}



