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

    //assemblage de U
    ptr = assemblageU(nnoe, noeuds, "U", ptr);

    //sous-matrices
    //Kfr
    ptr=sousmatrice(ptr,"K",RF->r,RF->nbr_r,RF->f,RF->nbr_f,"Kfr", "plein");
    
    //Kff
    ptr=sousmatrice(ptr,"K",RF->f,RF->nbr_f,RF->f, RF->nbr_f,"Kff","sym");
    
    //Ur
    ptr=sousvecteur(ptr,"U",RF->r,RF->nbr_r,"Ur");
    
    //assemblage de Ff
    ptr=assemblageFf( ptr,  RF->nbr_f,  RF->f, noeuds);
    
    //produit Kfr*Ur
    ptr=produit("Kfr", "Ur", "E",ptr);
    
    //difference Ff-E (E=Kfr*UR)
    ptr=difference("Ff", "E", "B",ptr);

    //resoudre systeme eq AX=B
    ptr=resolutioneq(ptr,"Kff", "B", "Uf"); 

    //assemblage nouveau U (u2??)
    ptr=assemblageU2(ptr,"Uf", "U",RF->f,RF->nbr_f);
    
    //assemblage de F
    ptr = produit("K", "U2", "F", ptr);
    
    //affectation des resultats dans les noeuds
    affecterresults("F","U2",noeuds,ptr);
    
    //affichage
    
    printf("matrice F: \n");
    affichage(recherche(ptr,"F"));
    printf("matrice U: \n");
    affichage(recherche(ptr,"U2"));
    
    printf("liste des noeuds: \n");
    affichageliste(nnoe,noeuds);

    //destructions
   
    while (ptr != NULL) {
    matrices temp = ptr;
    ptr = destruction(ptr, temp->nom);
     }
   
    free(elements);
    free(noeuds);
    free(RF);
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

    //Assemblage de U

    ptr = assemblageU(nnoe, noeuds, "U", ptr);

    //Calcul de F

    ptr = produit("K", "U", "F", ptr);

    //affectation des resultats dans les noeuds
    affecterresults("F","U",noeuds,ptr);
    
    //affichage
    
    printf("matrice F: \n");
    affichage(recherche(ptr,"F"));
    printf("matrice U: \n");
    affichage(recherche(ptr,"U"));
    
    printf("liste des noeuds: \n");
    affichageliste(nnoe,noeuds);


   
    //destructions
   
    while (ptr != NULL) {
    matrices temp = ptr;
    ptr = destruction(ptr, temp->nom);
     }
   
    free(elements);
    free(noeuds);
    
}
   }
