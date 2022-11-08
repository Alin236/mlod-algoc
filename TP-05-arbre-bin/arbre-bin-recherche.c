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
	if(estVide(a)){
		return creer(e);
	}
	ArbreBinaire pere = a;
	ArbreBinaire fils = a;
	while (!estVide(fils) && e != fils->val){
		pere = fils;
		fils = e < fils->val ? fils->filsGauche : fils->filsDroit;

	}
	if(estVide(fils)){
		if(e < pere->val)
			pere->filsGauche = creer(e);
		else
			pere->filsDroit = creer(e);
	}
	return a;
}	

// insere e dans a sachant que a est un arbre binaire de recherche
// si a contient déjà un element e, ce dernier n'est pas insérer afin d'éviter les doublons
// version récursive
ArbreBinaire insere_r(ArbreBinaire a, Element e) {
	if(estVide(a))
		return creer(e);
	if(e == a->val)
		return a;
	e<a->val ? a->filsGauche = insere_r(a->filsGauche, e) : (a->filsDroit = insere_r(a->filsDroit, e));
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
	if(estVide(a) || elem == a->val)
		return NULL;
	fils = elem < pere->val ? pere->filsGauche : pere->filsDroit;
	while(!estVide(fils) && elem != fils->val ){
		pere = fils;
		fils = elem < pere->val ? pere->filsGauche : pere->filsDroit;
	}
	if(estVide(fils))
		return NULL;
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
	if(estVide(a))
		return NULL;
	ArbreBinaire filsRemplacant;
	if(x == a->val){
		if(estVide(a->filsGauche) && estVide(a->filsDroit)){
			free(a);
			return NULL;
		}
		if(estVide(a->filsGauche)){
			filsRemplacant = a->filsDroit;
			free(a);
			return a->filsDroit;
		}
		if(estVide(a->filsDroit)){
			filsRemplacant = a->filsGauche;
			free(a);
			return filsRemplacant;
		}
		filsRemplacant = max(a->filsGauche);
		ArbreBinaire papa = pere(a->filsGauche, filsRemplacant->val);
		if(!estVide(papa)){
			filsRemplacant->filsGauche = a->filsGauche;
			papa->filsDroit = NULL;
		}
		filsRemplacant->filsDroit = a->filsDroit;
		free(a);
		return filsRemplacant;
	}
	x < a->val ? a->filsGauche = supprimer_r(a->filsGauche, x) : (a->filsDroit = supprimer_r(a->filsDroit, x));
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

