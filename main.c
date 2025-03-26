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
