
/*

 Prototypes des fonctions de resolution.
 Attention : pour compiler sur Linux 64 bits, ajouter l'option "-no-pie"

 Resoud A*X = B pour A matrice carree de determinant non nul.

 Arguments :

  A : tableau 2D, de taille n par n
  B : tableau 2D, taille n par m (m colonnes -> mettre 1 pour un vecteur)
  X : tableau 2D, taille n par m

 La fonction solveplein resoud le cas d'une matrice A de type plein
 en utilisant toutes les composantes de A.
 
 La fonction solvesym resoud le cas d'une matrice A symetrique
 en utilisant seulement les composantes du triangle superieur de A.
 Dans ce cas, on peut ne stocker que cette partie de A en memoire
 en faisant les decalages d'indices necessaires pour acceder
 correctement a ces elements.

 */

void solvesym(double **A,double **B,double **X,int n,int m);
void solveplein(double **A,double **B,double **X,int n,int m);
