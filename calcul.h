//calcul.h//

#ifndef calcul_h
#define calcul_h

struct matrice
   {
      char nom[20];
      char type[20];
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
matrices produit(char* tab1, char* tab2,char* nom,matrices ptr);

//difference
matrices difference(char* tab1, char* tab2,char* nom,matrices ptr);

//fpriv:cas plein et symetrique
void produit_plein(double** ta1, double** ta2, double** res, int n, int m, int m2);
void produit_sym(double** ta1, double** ta2, double** res, int n, int m2) ;

// affichage
void affichage(matrices tab1);

//fpriv:cas plein et symetrique
void affichage_plein(double** mat, int n, int m);
void affichage_sym(double** mat, int n);

// destruction
matrices destruction(matrices top, char* nom);

//res system eq AX=B
matrices resolutioneq(matrices ptr, char *nom1, char *nom2, char *nom3);

#endif /* calcul_h */
