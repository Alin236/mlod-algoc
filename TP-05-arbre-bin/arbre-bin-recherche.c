#include "arbre-bin-recherche.h"
#include <stdlib.h>
#include <stdbool.h>

// retourne TRUE si a est l'arbre vide et FALSE sinon
bool estVide(ArbreBinaire a) {
	return a == NULL;
}

// initialise l'arbre a à l'arbre vide
void initialiser(ArbreBinaire* a) {
	*a = NULL;
}

// créer un arbre contenant un seul noeud ayant la valeur e
ArbreBinaire creer(Element e) {
	ArbreBinaire a = malloc(sizeof(Noeud));
	if(a!=NULL){
		a->val = e;
		a->filsDroit = NULL;
		a->filsGauche = NULL;
	}
	return a;
}

// insere e dans a sachant que a est un arbre binaire de recherche
// si a contient déjà un element e, ce dernier n'est pas insérer afin d'éviter les doublons
// version itérative
ArbreBinaire insere_i(ArbreBinaire a, Element e) {
	ArbreBinaire* p = &a;
	while (!estVide(*p) && e != (*p)->val){
		if(e<(*p)->val){
			p = &((*p)->filsGauche);
		}
		else{
			p = &((*p)->filsDroit);
		}
	}
	if(estVide(*p)){
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
	if(estVide(a)){
		a = creer(e);
		return a;
	}
	if(estVide(a) || e == a->val){
		a->val = e;
		return a;
	}
	if(e<a->val){
		if(estVide(a->filsGauche)){
			a->filsGauche = creer(e);
			return a;
		}
		insere_r(a->filsGauche, e);
	}
	else{
		if(estVide(a->filsDroit)){
			a->filsDroit = creer(e);
			return a;
		}
		insere_r(a->filsDroit, e);
	}
	return a;
}

// retourne le nombre de noeud contenus dans l'arbre a
int nombreDeNoeud(ArbreBinaire a){
	int nombreDeNoeudGauche;
	int nombreDeNoeudDroit;
	if(estVide(a)){
		return 0;
	}
	nombreDeNoeudGauche = nombreDeNoeud(a->filsGauche);
	nombreDeNoeudDroit = nombreDeNoeud(a->filsDroit);
	return nombreDeNoeudGauche + nombreDeNoeudDroit + 1;
}


// retourne la profondeur du noeud ayant la valeur e dans a
// retourne -1 si a est vide ou si e n'est pas dans a
int profondeur(ArbreBinaire a, Element e){
	int profond = 1;
	while (!estVide(a) && e != a->val){
		if(e < a->val){
			a = a->filsGauche;
		}
		else{
			a = a->filsDroit;
		}
		profond++;
	}
	if(estVide(a)){
		return -1;
	}
	return profond;
}

// retourne la hauteur de l'arbre a
int hauteur(ArbreBinaire a){
	int haut;
	int hauteurFilsGauche;
	int hauteurFilsDroit;
	if(estVide(a)){
		return 0;
	}
	hauteurFilsGauche = hauteur(a->filsGauche);
	hauteurFilsDroit = hauteur(a->filsDroit);
	haut = (hauteurFilsGauche < hauteurFilsDroit ? hauteurFilsDroit : hauteurFilsGauche) + 1;
	return haut;
}

// retourne le pere de elem dans l'arbre a ou NULL s'il n'existe pas
ArbreBinaire pere(ArbreBinaire a, Element elem){
	ArbreBinaire pere;
	ArbreBinaire fils;
	pere = a;
	if(estVide(a)){
		return NULL;
	}
	if(elem == a->val){
		return NULL;
	}
	fils = elem < pere->val ? pere->filsGauche : pere->filsDroit;
	while(!estVide(fils) && elem != fils->val ){
		pere = fils;
		fils = elem < pere->val ? pere->filsGauche : pere->filsDroit;
	}
	if(estVide(fils)){
		return NULL;
	}
	return pere;
}


void afficheRGD_r(ArbreBinaire a){
	if(!estVide(a)){
		afficheRGD_r(a->filsDroit);
		afficheRGD_r(a->filsGauche);
		printf("%i ", a->val);
	}
}

void afficheGRD_r(ArbreBinaire a){
	if(!estVide(a)){
		afficheRGD_r(a->filsGauche);
		afficheRGD_r(a->filsDroit);
		printf("%i ", a->val);
	}
}

void afficheGDR_r(ArbreBinaire a){
	if(!estVide(a)){
		afficheRGD_r(a->filsGauche);
		printf("%i ", a->val);
		afficheRGD_r(a->filsDroit);
	}
}

// retourne le noeud dont la valeur est minimum dans l'arbre
// Suppose que a est un arbre binaire de recherche sans doublons
ArbreBinaire min(ArbreBinaire a){
	if(estVide(a)){
		return NULL;
	}
	while(!estVide(a->filsGauche)){
		a = a->filsGauche;
	}
	return a;
}

// retourne le noeud dont la valeur est maximum dans l'arbre
// Suppose que a est un arbre binaire de recherche sans doublons
ArbreBinaire max(ArbreBinaire a){
	if(estVide(a)){
		return NULL;
	}
	while(!estVide(a->filsDroit)){
		a = a->filsDroit;
	}
	return a;
}


// retourne l'arbre dont la valeur de la racine est elem et NULL si elem n'existe dans a 
// version récursive
ArbreBinaire recherche_r(ArbreBinaire a, Element elem){
	if(estVide(a) || elem == a->val){
		return a;
	}
	return elem < a->val ? recherche_r(a->filsGauche, elem) : recherche_r(a->filsDroit, elem);
}


// suppime x de a
ArbreBinaire supprimer_r(ArbreBinaire a,Element x)
{
	if(estVide(a)){
		return NULL;
	}
	ArbreBinaire filsRemplacant;
	if(x == a->val){
		if(a->filsGauche == NULL && a->filsDroit == NULL){
			detruire_r(a);
			return NULL;
		}
		if(a->filsGauche == NULL){
			filsRemplacant = a->filsDroit;
		}
		else if(a->filsDroit == NULL){
			filsRemplacant = a->filsGauche;
		}
		else{
			filsRemplacant = max(a->filsGauche);
			ArbreBinaire papa = pere(a->filsGauche, filsRemplacant->val);
			papa->filsDroit = NULL;
			filsRemplacant->filsGauche = a->filsGauche;
			filsRemplacant->filsDroit = a->filsDroit;
		}
		a->val = filsRemplacant->val;
		a->filsGauche = filsRemplacant->filsGauche;
		a->filsDroit = filsRemplacant->filsDroit;
		filsRemplacant->filsGauche = NULL;
		filsRemplacant->filsDroit = NULL;
		detruire_r(filsRemplacant);
		return a;
	}
	ArbreBinaire fils;
	fils = x < a->val ? a->filsGauche : a->filsDroit;
	if(fils == NULL){
		return NULL;
	}
	if(x == fils->val){
		if(fils->filsGauche == NULL && fils->filsDroit == NULL){
			if(fils == a->filsGauche){
				a->filsGauche = NULL;
			}
			else{
				a->filsDroit = NULL;
			}
			detruire_r(fils);
			return a;
		}
		if(fils->filsGauche == NULL){
			filsRemplacant = a->filsDroit;
		}
		else if(fils->filsDroit == NULL){
			filsRemplacant = a->filsGauche;
		}
		else{
			filsRemplacant = max(a->filsGauche);
			ArbreBinaire papa = pere(a, filsRemplacant->val);
			papa->filsDroit = NULL;
			filsRemplacant->filsGauche = fils->filsGauche;
			filsRemplacant->filsDroit = fils->filsDroit;
		}
		fils->val = filsRemplacant->val;
		fils->filsGauche = filsRemplacant->filsGauche;
		fils->filsDroit = filsRemplacant->filsDroit;
		filsRemplacant->filsGauche = NULL;
		filsRemplacant->filsDroit = NULL;
		detruire_r(filsRemplacant);
		return a;
	}
	supprimer_r(fils, x);
	return a;
}

void detruire_r(ArbreBinaire a){
	if(estVide(a)){
		return;
	}
	detruire_r(a->filsGauche);
	detruire_r(a->filsDroit);
	free(a);
}

