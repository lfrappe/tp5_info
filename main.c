//main.c//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calcul.h"
#include "ef.h"


int main()
{

printf("Le problème contient-il des déplacements inconnus? Répondez 1 pour OUI, 2 pour NON");
scanf("%d"; &inc);

    // 1-OUI, INCONNUES //
if (inc==1)
{
    //choix type matrice
    char type[20];
    choixmatrice(type);

    //entree noeuds et elements
    int nnoe = taillenoeud(), nelt = tailleelm();
    struct noeud* noeuds = entrenoeud2(nnoe);
    struct element* elements = entreelmt(nelt,nnoe);
    matrices ptr = NULL;

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
    ptr=sousmatrice("K", *,*,*,*,"Kfr","sym");
    affichage("Kfr");
    
    //Kff
    ptr=sousmatrice("K", *,*,*,*,"Kff","sym");
    affichage("Kff");
    
    //Ur
    ptr=sousvecteur("U",*,*,*,*,"Ur","plein");
    affichage("Ur");
    
    //Ff
    ptr=sousvecteur("F",*,*,*,*,"Ff","plein");
    affichage("Ff");
    
    //produit Kfr*Ur
    ptr=creation("E",*,*, "plein");
	produit("Kfr", "Ur", "E");
    
    //difference Ff-E (E=Kfr*UR)
    ptr=difference(ptr, "Ff", "E", "B?")
        
    //creation Uf
    ptr=creation("Uf",*,*,"plein");

    //resoudre systeme eq AX=B
    resolutioneq("Kff", "B?", "Uf");
	affichage("Uf");

    //assemblage nouveau U (u2??)

    //besoin de ca? si oui mettre ou
    affecterresults("F",noeuds,ptr);
    
    //affichage
    affichageliste(nnoe,noeuds);

    //suppressions
    ptr = destruction(ptr, "K");
    ptr = destruction(ptr, "U");
    ptr = destruction(ptr, "F");
    
}

    // 2-NON, PAS INCONNUES //
    
else
{
    //choix type matrice
    char type[20];
    choixmatrice(type);

    //entree noeuds et elements
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
   }
