//main.c//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calcul.h"
#include "ef.h"


int main()
{
	int inc;

printf("Le problème contient-il des déplacements inconnus? Répondez 1 pour OUI, 2 pour NON");
scanf("%d", &inc);

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
    affichage(recherche(ptr, "K"));

    //assemblage de U
    ptr = assemblageU(nnoe, noeuds, "U", ptr);
    affichage(recherche(ptr, "U"));
    
    //assemblage de F
    ptr = produit("K", "U", "F", ptr);
    affichage(recherche(ptr, "F"));

    //sous-matrices
    //Kfr
    ptr = sousmatrice(ptr,"K",r,nbr_r,f,nbr_f,"Kfr");
    affichage(recherche(ptr, "Kfr"));
    
    //Kff
    ptr=sousmatrice(ptr,"K",r,nbr_r,f, nbr_f,"Kff");
    affichage(recherche(ptr, "Kff"));
    
    //Ur
    ptr=sousvecteur(ptr,"U",r,nbr_r,"Ur");
    affichage(recherche(ptr, "Ur"));
    
    //Ff
    ptr=sousvecteur(ptr,"F",r,nbr_r,"Ff");
    affichage(recherche(ptr, "Ff"));
    
    //produit Kfr*Ur
    produit("Kfr", "Ur", "E",ptr);
    
    //difference Ff-E (E=Kfr*UR)
    ptr=difference("Ff", "E", "B",ptr); 
    
    //resoudre systeme eq AX=B

    resolutioneq(ptr,"Kff", "B", "Uf"); 
	affichage((recherche(ptr, "Ff"));

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
    affichage(recherche(ptr, "K"));

    //Assemblage de U

    ptr = assemblageU(nnoe, noeuds, "U", ptr);
    affichage(recherche(ptr, "U"));

    //Calcul de F

    ptr = produit("K", "U", "F", ptr);
    affichage(recherche(ptr, "F"));

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
