//calcul.c//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calcul.h"

//fpub:choix du type de matrice pour K
char* choixmatrice(char* c)
{
do{
printf("Choisissez le type de matrice (plein/sym) : ");
scanf("%s",c);
   }while((strcmp(c,"plein")!=0) && (strcmp(c,"sym")!=0));
   return c;
}

//fpub:Fonctions affichage
void affichage(matrices tab1,char* type)
{  
   if (tab1 == NULL)
   {
      printf("Matrice inexistante\n");
      return;
      }
   if (!strcmp(type, "plein"))
   {
  affichage_plein(tab1->mat, tab1->n, tab1->m);
  }
   else if (!strcmp(type, "sym")) {
  affichage_sym(tab1->mat, tab1->n);
  }
     
       printf("\n\n");
      return;

}

//fpriv:affichage matrice pleine
void affichage_plein(double** mat, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
        {
            printf("%lf ", mat[i][j]);
}
        printf("\n");
    }
}

//fpriv:affichage matrice symetriques
void affichage_sym(double** mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            if (i <= j) {
                printf("%lf ", mat[i][j-i]);
            } else {
                printf("         ");

            }
        }
            printf("\n");
    }
}

//fpub:Fonction recherche
matrices recherche(matrices temp,char* nm)
{
   while (temp!=NULL){
      if(!strcmp(temp->nom,nm)){
         return(temp);
      }
      temp=temp->next;
   }
   printf("pas de matrice %s",nm);
   return(temp);
}

//fpub:Fonction création matrice
matrices creation(int n, int m, char* nom,matrices ptr,char* type)
{
   
   matrices temp = malloc(sizeof(struct matrice));
   
   strcpy( temp->nom,nom);
   temp->n=n, temp->m=m;
   
   
   if (!strcmp(type, "plein")) {
        temp-> mat = creation_plein(n, m);
    } else if (!strcmp(type, "sym")) {
        temp-> mat = creation_sym(n);
    }
   
   temp->next= ptr ;
   ptr = temp;
   return temp;


}

//fpriv:creation matrice pleine
double** creation_plein(int n, int m)
{
int i;
double **mat= (double**)malloc(n*sizeof(double*));
if (!mat) return NULL;
    for (i = 0; i < n; i++) {
        mat[i] = (double*)malloc(m*sizeof(double*));
        if (!mat[i]) return NULL;
    }
    return mat;
}

//fpriv:creation matrice symetriques
double** creation_sym(int n)
{
int i;
double **mat = (double**)malloc(n*sizeof(double*));
    if (!mat) return NULL;
    for (i = 0; i < n; i++) {
        mat[i] = (double*)malloc((n - i) * sizeof(double));
        if (!mat[i]) return NULL;
    }
    return mat;
}

//fpub:Fonction destruction
matrices destruction(matrices top, char* nom)
{
    matrices tmp = recherche(top, nom);
    if (tmp == NULL) return top;

   
    if (tmp == top) {
        top = top->next;
    }
   
    else {
        matrices prev = top;
        while (prev->next != tmp) {
            prev = prev->next;
        }
        prev->next = tmp->next;
    }

   int i ;
   for(i=0; i<tmp->n; i++){
      free(tmp->mat[i]);
   }
   free(tmp->mat);
   free(tmp);
   tmp=NULL;
   
    return top;
}

//fpub:Fonction produit
matrices produit(char* tab1, char* tab2,char* nom,matrices ptr,char* type)
{  
   matrices ta1=NULL,ta2=NULL;
   ta1=recherche(ptr,tab1);
   ta2=recherche(ptr,tab2);
   
   if (ta1 == NULL || ta2 == NULL) {
    printf("matrice n'existe pas\n");
    return ptr;
}

   if (ta1->m != ta2->n) {
    printf("dimensions incompatibles\n");
    return ptr;
    }
   
    matrices res = creation(ta1->n, ta2->m, nom,ptr,"plein");
    if (!strcmp(type, "plein")) {
produit_plein(ta1->mat, ta2->mat, res->mat, ta1->n, ta1->m, ta2->m);
}
else if (!strcmp(type, "sym")) {
  produit_sym(ta1->mat, ta2->mat, res->mat, ta1->n, ta2->m);
  }
return res;
}

//fpriv:produit matrice pleine
void produit_plein(double** ta1, double** ta2, double** res, int n, int m, int m2) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < m; k++) {
                res[i][j] += ta1[i][k] * ta2[k][j];
            }
        }
    }
}

//fpriv:produit matrice symetriques
void produit_sym(double** ta1, double** ta2, double** res, int n, int m2) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m2; j++) {
            res[i][j] = 0;
            for (int k = 0; k <= i; k++) {

              
                res[i][j] += ta1[k][i-k] * ta2[k][j];
            }
            for (int k = i + 1; k < n; k++) {

                res[i][j] += ta1[i][k-i] * ta2[k][j];
               
            }
        }
    }
}

