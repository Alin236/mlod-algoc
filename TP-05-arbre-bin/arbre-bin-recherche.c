#include "arbre-bin-recherche.h"
#include <stdlib.h>
#include <stdbool.h>

// retourne TRUE si a est l'arbre vide et FALSE sinon
bool estVide(ArbreBinaire a) {
	bool valVide = a->val == NULL;
	bool filsDroitVide = a->filsDroit == NULL;
	bool filsGaucheVide = a->filsGauche == NULL;
	return valVide && filsDroitVide && filsGaucheVide;
}

// initialise l'arbre a à l'arbre vide
void initialiser(ArbreBinaire* a) {
	*a = malloc(sizeof(Noeud));
	if(*a!=NULL){
		(*a)->filsDroit = NULL;
		(*a)->filsGauche = NULL;
	}
}

// créer un arbre contenant un seul noeud ayant la valeur e
ArbreBinaire creer(Element e) {
	ArbreBinaire a;
	initialiser(&a);
	a->val = e;
	return a;
}

// insere e dans a sachant que a est un arbre binaire de recherche
// si a contient déjà un element e, ce dernier n'est pas insérer afin d'éviter les doublons
// version itérative
ArbreBinaire insere_i(ArbreBinaire a, Element e) {
	ArbreBinaire* p = &a;
	while (*p != NULL && !estVide(*p) && e != (*p)->val){
		if(e<(*p)->val){
			p = &((*p)->filsGauche);
		}
		else{
			p = &((*p)->filsDroit);
		}
	}
	if(*p == NULL){
		*p = creer(e);
		return a;
	}
	(*p)->val = e;
	return a;
}	

// insere e dans a sachant que a est un arbre binaire de recherche
// si a contient déjà un element e, ce dernier n'est pas insérer afin d'éviter les doublons
// version récursive
ArbreBinaire insere_r(ArbreBinaire a, Element e) {
	if(a == NULL){
		a = creer(e);
		return a;
	}
	if(estVide(a) || e == a->val){
		a->val = e;
		return a;
	}
	if(e<a->val){
		insere_r(a->filsGauche, e);
	}
	else{
		insere_r(a->filsDroit, e);
	}
	return a;
}

// retourne le nombre de noeud contenus dans l'arbre a
int nombreDeNoeud(ArbreBinaire a){
	int nombreDeNoeudGauche;
	int nombreDeNoeudDroit;
	if(a == NULL){
		return 0;
	}
	nombreDeNoeudGauche = nombreDeNoeud(a->filsGauche);
	nombreDeNoeudDroit = nombreDeNoeud(a->filsDroit);
	return nombreDeNoeudGauche + nombreDeNoeudDroit + 1;
}


// retourne la profondeur du noeud ayant la valeur e dans a
// retourne -1 si a est vide ou si e n'est pas dans a
int profondeur(ArbreBinaire a, Element e){
	int profond;
	while (a != NULL && !estVide(a) && e != a->val){
		if(e < a->val){
			a = a->filsGauche;
		}
		else{
			a = a->filsDroit;
		}
		profond++;
	}
	return profond;
}

// retourne la hauteur de l'arbre a
int hauteur(ArbreBinaire a){
	int haut;
	int hauteurFilsGauche;
	int hauteurFilsDroit;
	if(a == NULL){
		return 0;
	}
	hauteurFilsGauche = hauteur(a->filsGauche);
	hauteurFilsDroit = hauteur(a->filsDroit);
	haut = (hauteurFilsGauche < hauteurFilsDroit ? hauteurFilsDroit : hauteurFilsGauche) + 1;
	return haut;
}

// retourne le pere de elem dans l'arbre a ou NULL s'il n'existe pas
ArbreBinaire pere(ArbreBinaire a, Element elem){

	return NULL;
}


void afficheRGD_r(ArbreBinaire a){
}

void afficheGRD_r(ArbreBinaire a){
}

void afficheGDR_r(ArbreBinaire a){
}

// retourne le noeud dont la valeur est minimum dans l'arbre
// Suppose que a est un arbre binaire de recherche sans doublons
ArbreBinaire min(ArbreBinaire a){
	return NULL;
}

// retourne le noeud dont la valeur est maximum dans l'arbre
// Suppose que a est un arbre binaire de recherche sans doublons
ArbreBinaire max(ArbreBinaire a){
	return NULL;
}


// retourne l'arbre dont la valeur de la racine est elem et NULL si elem n'existe dans a 
// version récursive
ArbreBinaire recherche_r(ArbreBinaire a, Element elem){

	return NULL;
}


// suppime x de a
ArbreBinaire supprimer_r(ArbreBinaire a,Element x)
{

	return NULL;
}

void detruire_r(ArbreBinaire a){

}

