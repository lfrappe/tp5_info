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
    
    //int de r et f
   struct donnee *RF = malloc(sizeof(struct donnee));

    //entree noeuds et elements
    int nnoe = taillenoeud(), nelt = tailleelm();
    struct noeud* noeuds = entrenoeud2(nnoe, RF);
    struct element* elements = entreelmt(nelt,nnoe);
    matrices ptr = NULL;
    

    //assemblage de K
    ptr = assemblageK(nnoe, nelt, elements, "K", ptr,type);
    affichage(recherche(ptr, "K"));

    //assemblage de U
    ptr = assemblageU(nnoe, noeuds, "U", ptr);
    affichage(recherche(ptr, "U"));

    //sous-matrices
    //Kfr
    ptr = sousmatrice(ptr,"K",RF->r,RF->nbr_r,RF->f,RF->nbr_f,"Kfr", "plein");
    affichage(recherche(ptr, "Kfr"));
    
    //Kff
    ptr=sousmatrice(ptr,"K",RF->f,RF->nbr_f,RF->f, RF->nbr_f,"Kff","sym");
    affichage(recherche(ptr, "Kff"));
    
    //Ur
    ptr=sousvecteur(ptr,"U",RF->r,RF->nbr_r,"Ur");
    affichage(recherche(ptr, "Ur"));
    
    //assemblage de Ff
    ptr=assemblageFf( ptr,  RF->nbr_f,  RF->f, noeuds);
    affichage(recherche(ptr, "Ff"));
    
    //produit Kfr*Ur
    ptr=produit("Kfr", "Ur", "E",ptr);
    affichage(recherche(ptr, "E"));
    
    //difference Ff-E (E=Kfr*UR)
    ptr=difference("Ff", "E", "B",ptr);
    affichage(recherche(ptr, "B"));

    //resoudre systeme eq AX=B
    ptr=resolutioneq(ptr,"Kff", "B", "Uf"); 
	affichage(recherche(ptr, "Uf"));

    //assemblage nouveau U (u2??)
    ptr=assemblageU2(ptr,"Uf", "U",RF->f,RF->nbr_f);
    affichage(recherche(ptr, "U2"));
    
    //assemblage de F
    ptr = produit("K", "U2", "F", ptr);
    affichage(recherche(ptr, "F"));
    
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


   
    //destructions
   
    while (ptr != NULL) {
    matrices temp = ptr;
    ptr = ptr->next;
    ptr = destruction(ptr, temp->nom);
     }
   

    free(elements);
    free(noeuds);
}
   }
