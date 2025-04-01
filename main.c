//main.c//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calcul.h"
#include "ef.h"


int main()
{
//choix type matrice
char type[20];
choixmatrice(type);

int nnoe = taillenoeud(), nelt = tailleelm();

struct noeud* noeuds = entrenoeud(nnoe);
struct element* elements = entreelmt(nelt,nnoe);
matrices ptr = NULL;

printf("Le problème contient-il des déplacements inconnus? Répondez 1 pour OUI, 2 pour NON");
scanf("%d"; &inc);

    // 1-OUI, INCONNUES //
if (inc==1)
{
    //noeuds

    //elements

    //choix type k

    //

    //assemblage de K
    ptr = assemblageK(nnoe, nelt, elements, "K", ptr,type);
    affichage(recherche(ptr, "K"),type);

    //assemblage de U
    ptr = assemblageU(nnoe, noeuds, "U", ptr);
    affichage(recherche(ptr, "U"),"plein");
    
    //assemblage de F
    ptr = produit("K", "U", "F", ptr,type);
    affichage(recherche(ptr, "F"),"plein");

    //sous-matrices
    //Kfr
    //Kff
    
}

    // 2-NON, PAS INCONNUES //
else
{

//Assemblage de K

ptr = assemblageK(nnoe, nelt, elements, "K", ptr,type);
affichage(recherche(ptr, "K"),type);

//Assemblage de U

ptr = assemblageU(nnoe, noeuds, "U", ptr);
affichage(recherche(ptr, "U"),"plein");

//Calcul de F

ptr = produit("K", "U", "F", ptr,type);
affichage(recherche(ptr, "F"),"plein");

affecterresults("F",noeuds,ptr);

affichageliste(nnoe,noeuds);

    ptr = destruction(ptr, "K");
    ptr = destruction(ptr, "U");
    ptr = destruction(ptr, "F");
   
   
//autre maniere de faire les destructions, peut etre mieux
   
    //~ while (ptr != NULL) {
    //~ matrices temp = ptr;
    //~ ptr = ptr->next;
    //~ ptr = destruction(ptr, temp->nom);
//~ }
   

    free(elements);
    free(noeuds);
}
   }
