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
      int dep;
      double eff;
};

//entrée elements
struct element* entreelmt(int nelt, int nnoe);
//entrée noeuds
struct noeud* entrenoeud(int nnoe);
struct noeud* entrenoeud2(int nnoe);
// assemblage K
matrices assemblageK(int nnoe, int nelt, struct element *elements, char* nmK,matrices ptr,char* symp);
// assemblage U
matrices assemblageU(int nnoe, struct noeud *noeuds, char* nmU,matrices ptr);
// affectation resultats
void affecterresults(char* F, struct noeud *noeuds, matrices ptr);
// affiche_liste
void affichageliste(int nnoe,struct noeud *noeuds);
//entrée taille element
int tailleelm();
//entrée taille noeuds
int taillenoeud();
//assemblage U2
void assemblageU2(matrices ptr, char *Uf, char *U, int *f, int nbr_f);

#endif /* ef_h */
