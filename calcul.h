//calcul.h//

#ifndef calcul_h
#define calcul_h

struct matrice
   {
      char nom[20];
      int n;
      int m;
      double **mat;
      struct matrice *next ;
   };

typedef struct matrice* matrices;

//choix type matrice 
char* choixmatrice(char* c);

//recherche
matrices recherche(matrices temp,char* nm);

// creation
matrices creation(int n, int m, char* nom,matrices ptr, char* type);

//fpriv:cas plein et symetrique
double** creation_sym(int n);
double** creation_plein(int n, int m);

// produit
matrices produit(char* tab1, char* tab2,char* nom,matrices ptr,char* type);

//somme ??
//difference
matrice* difference(struct matrice* ptr, char* nom_A, char* nom_B, char* nom_C);

//fpriv:cas plein et symetrique
void produit_plein(double** ta1, double** ta2, double** res, int n, int m, int m2);
void produit_sym(double** ta1, double** ta2, double** res, int n, int m2) ;

// affichage
void affichage(matrices tab1,char* type);
//fpriv:cas plein et symetrique
void affichage_plein(double** mat, int n, int m);
void affichage_sym(double** mat, int n);

// destruction
matrices destruction(matrices top, char* nom);

//sous-matrices
matrice *sousmatrice_plein_vers_plein(struct matrice *K,int *r,int nbr_r,int *f,int nbr_f,char *nom2);
matrice *sousmatrice_sym_vers_plein(struct matrice *K, int *r,int nbr_r,int *f,int nbr_f, char* nom2);
matrice *sousmatrice_sym (struct matrice *K,int *f,int nbr_f,char* nom2);
matrice* sousmatrice(char *nom1,int *r,int nbr_r,int *f,int nbr_f,char *nom2,char *type);

//sous-vecteurs
matrice *sousvecteurU(char *nom1, int *r, int nbr_r, int* f, int nbr_f, char *nom2, char* type);
matrice *sousvecteurF(char *nom1, int *r, int nbr_r, int *f, int nbr_f, char *nom2, char *type);

//res system eq AX=B
void resolutioneq(char *nom1, char *nom2, char *nom3);

#endif /* calcul_h */
