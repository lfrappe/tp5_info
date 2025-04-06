//ef.h//

#ifndef ef_h
#define ef_h

#include "calcul.h"

struct element
   {
      int num;
      int k[2];
      double raid;
   };
   
struct noeud
   {
      int num;
      double dep;
      double eff;
};

typedef struct donnee
{
int nbr_r;
int nbr_f;
int* r;
int* f;
}donnee;

//entrée elements
struct element* entreelmt(int nelt, int nnoe);
//entrée noeuds
struct noeud* entrenoeud(int nnoe);
struct noeud* entrenoeud2(int nnoe, struct donnee *RF);
// assemblage K
matrices assemblageK(int nnoe, int nelt, struct element *elements, char* nmK,matrices ptr,char* symp);
// assemblage U
matrices assemblageU(int nnoe, struct noeud *noeuds, char* nmU,matrices ptr);
// affectation resultats
void affecterresults(char* F,char* U, struct noeud *noeuds, matrices ptr);
// affiche_liste
void affichageliste(int nnoe,struct noeud *noeuds);
//entrée taille element
int tailleelm();
//entrée taille noeuds
int taillenoeud();
//assemblage U2
matrices assemblageU2(matrices ptr, char *Uf, char *U, int *f, int nbr_f);
//asemblage Ff
matrices assemblageFf(matrices ptr, int nbr_f, int *f, struct noeud* noeuds);
//sous-matrices
matrices sousmatrice(matrices ptr,char *nomK, int *r, int nbr_r, int *f,int nbr_f, char *nom2, char* type);
//sous-vecteur
matrices sousvecteur(matrices ptr,char *nom1, int *r, int nbr, char *nom2);


#endif /* ef_h */
