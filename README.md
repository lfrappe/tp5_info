1. Rentrer les données des efforts et des déplacements connus dans le tableau de structures noeud
FINI
2. Rentrer les données de la raideur et de la connectivité de chaque élément dans le tableau de structures element ;
FINI
3. Former la matrice raideur K et les vecteurs F et U à partir des données contenues dans les structures noeud et element avec une ou plusieurs fonctions d’assemblage (l’assemblage de F se fait comme celui de U) ;
VERIFIER ASSEMBLAGE F
4. Si certains efforts sont connus, calculer Uf = K1 f f (Ff  Kf r Ur ) en utilisant vos fonctions déjà programmées dans les TD précédents, “multiplication” et “soustraction” de matrices ainsi qu’une fonction de résolution (décrite ci-après) ;
soustraction s'appelle difference attentionnn**
sinon bien avancé, manque les variables dans les structures et fonctions dans le main.c, fonction de resolution a tester
6. Calculer le produit F = KU ;
A FAIRE
7. Restituer les déplacements solutions et les efforts solutions de F dans la structure noeud ;
A FAIRE
8. Détruire les matrices K, F et U ;
A FAIRE
9. Afficher la structure noeud.
FAIT, A VERIFIER SI FONCTIONNEL
