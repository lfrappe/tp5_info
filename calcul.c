//calcul.c//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calcul.h"
#include "libmat.h"

//fpub: choix du type de matrice pour K
char* choixmatrice(char* c)
{
do{
printf("Choisissez le type de matrice K (plein/sym) : ");
scanf("%s",c);
   }while((strcmp(c,"plein")!=0) && (strcmp(c,"sym")!=0));
   return c;
}

//fpub: fonctions affichage
void affichage(matrices tab1)
{  
	//verification que la matrice existe
    if (tab1 == NULL)
   {
		printf("Matrice inexistante\n");
		return;
      }
      
    //verification type matrice
    if (!strcmp(tab1->type, "plein"))
   {
		affichage_plein(tab1->mat, tab1->n, tab1->m);
  }
    else if (!strcmp(tab1->type, "sym")) {
		affichage_sym(tab1->mat, tab1->n);
  }
     //saut de lignes pour la présentation
     printf("\n\n");
     return;
}

//fpriv: affichage matrice pleine
void affichage_plein(double** mat, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
        {
            printf("%lf ", mat[i][j]);
}
		//saut de lignes pour la présentation
        printf("\n");
    }
}

//fpriv: affichage matrice symetriques
void affichage_sym(double** mat, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++){
            if (i <= j) {
                printf("%lf ", mat[i][j-i]);
            } else {
			//espaces et saut de lignes pour la présentation
                printf("         ");
            }
        }
            printf("\n");
    }
}

//fpub: fonction recherche
matrices recherche(matrices temp,char* nm)
{
	//parcour de la liste chainée pour trouver le nom de la matrice recherchée
    while (temp!=NULL){
		if(!strcmp(temp->nom,nm)){
			return(temp);
      }
      temp=temp->next;
   }
   //verification que la matrice existe
   printf("pas de matrice %s",nm);
   
   return(temp);
}

//fpub: fonction création matrice
matrices creation(int n, int m, char* nom,matrices ptr,char* type)
{
   //creation matrice 
   matrices temp = malloc(sizeof(struct matrice));
   strcpy( temp->nom,nom);
   temp->n=n, temp->m=m;
   strcpy( temp->type,type);
   
   //choix type matrice
   if (!strcmp(temp->type, "plein")) {
        temp-> mat = creation_plein(n, m);
    } else if (!strcmp(temp->type, "sym")) {
        temp-> mat = creation_sym(n);
    }
   //inclusion dans la liste chainée
   temp->next= ptr ;
   ptr = temp;
   
   return temp;
}

//fpriv: creation matrice pleine
double** creation_plein(int n, int m)
{
int i;
//creation lignes
double **mat= (double**)malloc(n*sizeof(double*));
//verification malloc fonctionne
if (!mat) return NULL;
//creation colonnes
for (i = 0; i < n; i++) {
	mat[i] = (double*)malloc(m*sizeof(double*));
	//verification malloc fonctionne
	if (!mat[i]) return NULL;
    }
    
    return mat;
}

//fpriv:creation matrice symetriques
double** creation_sym(int n)
{
int i;
//creation lignes
double **mat = (double**)malloc(n*sizeof(double*));
//verification malloc fonctionne
if (!mat) return NULL;
//creation colonnes
for (i = 0; i < n; i++) {
    mat[i] = (double*)malloc((n - i) * sizeof(double));
    //verification malloc fonctionne
    if (!mat[i]) return NULL;
    }
    return mat;
}

//fpub: fonction destruction
matrices destruction(matrices top, char* nom)
{
	//recherche de la matrice
	matrices tmp = recherche(top, nom);
	if (tmp == NULL) return top;
    //cas ou la matrice est tete de chaine
	if (tmp == top) {
		top = top->next;
	}
    //recherche de la matrice precedant la matrice a detruire dans la liste chainée
	else {
		matrices prev = top;
		while (prev->next != tmp) {
			prev = prev->next;
		}
	prev->next = tmp->next;
}
	//destruction colonnes
	int i ;
	for(i=0; i<tmp->n; i++){
		free(tmp->mat[i]);
}
	//destruction matrice
	free(tmp->mat);
	free(tmp);
	tmp=NULL;
	
	return top;
}

//fpub:Fonction produit
matrices produit(char* tab1,char* tab2,char* nom,matrices ptr)
{  
	//assignation a ta1 et ta2 des matrices qu'on multiplie
	matrices ta1=NULL,ta2=NULL;
	ta1=recherche(ptr,tab1);
	ta2=recherche(ptr,tab2);
	//verifications qu'elles existent
	if (ta1 == NULL || ta2 == NULL) {
		printf("matrice n'existe pas\n");
	return ptr;
}
	//verification dimensions
	if (ta1->m != ta2->n) {
		printf("dimensions incompatibles\n");
	return ptr;
}
   //creation en fonction du type
	matrices res = creation(ta1->n, ta2->m, nom,ptr,"plein");
	if (!strcmp(ta1->type, "plein")) {
		produit_plein(ta1->mat, ta2->mat, res->mat, ta1->n, ta1->m, ta2->m);
}
	else if (!strcmp(ta1->type, "sym")) {
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

//
//
//
//ajouts TD5
//
//
//


//fpub : difference C = A - B 
matrices difference(char* tab1, char* tab2,char* nom,matrices ptr)
{  
   int i,j;
   matrices ta1=NULL,ta2=NULL;
   ta1=recherche(ptr,tab1);
   ta2=recherche(ptr,tab2);
   
      if (ta1 == NULL || ta2 == NULL) {
    printf(" une des matrices n'existe pas.\n");
    return ptr;
}
if (ta1->n != ta2->n || ta1->m != ta2->m) {
    printf("dimensions incompatibles pour la soustraction\n");
    return ptr;
}


   matrices res = creation(ta1->n, ta2->m, nom,ptr,"plein");

   for(i = 0; i < ta1->n; i++)
  {
    for(j = 0; j < ta2->m; j++)
    {
       res->mat[i][j]=ta1->mat[i][j]-ta2->mat[i][j];
      }
    }
  return res;
   
}

//fpriv : extraction plein vers plein 
matrices sousmatrice_plein_vers_plein(matrices ptr,char* nomK,int *r,int nbr_r,int *f,int nbr_f,char *nom2)
{
	int i,j;
  matrices K=recherche(ptr, nomK);
	matrices Krf=creation(nbr_f, nbr_r, nom2,ptr, "plein");
	
	for(i=0;i<nbr_f;i++)
		{
		for(j=0;j<nbr_r;j++)
			{

				Krf->mat[i][j]=K->mat[f[i]][r[j]];

			}}	
	return Krf;

}

//fpriv : extraction sym vers plein
matrices sousmatrice_sym_vers_plein(matrices ptr,char* nomK, int *r,int nbr_r,int *f,int nbr_f, char* nom2)
{
	int i,j;
    matrices K=recherche(ptr, nomK);
	matrices Krf=creation(nbr_f, nbr_r, nom2,ptr, "plein");
	for(i=0;i<nbr_r;i++)
		for(j=0;j<nbr_f;j++)
		{
			if(r[i]<=f[j])
				Krf->mat[i][j]=K->mat[r[i]][f[j]];
			else
				Krf->mat[i][j]=K->mat[f[j]][r[i]];
		}
	return Krf;
}

//fpriv : extraction sym
matrices sousmatrice_sym (matrices ptr,char* nomK,int *f,int nbr_f,char* nom2)
{
	int i,j;
    matrices K=recherche(ptr,nomK);
	matrices Kff=creation(nbr_f, nbr_f, nom2,ptr, "sym");
	
	for(i=0;i<nbr_f;i++){
		for(j=0;j<nbr_f-i;j++)
		{
				Kff->mat[i][j]=K->mat[f[i]][f[i+j]-f[i]];
		}
	}
	return Kff;
}

//fpub : sous-matrice
matrices sousmatrice(matrices ptr,char *nomK, int *r, int nbr_r, int *f,int nbr_f, char *nom2, char* type)
{
	matrices K = recherche(ptr,nomK);
	matrices Krf;
	
	if(!strcmp(K->type,"plein"))
		Krf= sousmatrice_plein_vers_plein(ptr,nomK, r, nbr_r, f, nbr_f, nom2);
   
	else if(!strcmp(K->type,"sym")&&!strcmp(type,"plein"))
		Krf = sousmatrice_sym_vers_plein(ptr,nomK, r, nbr_r, f, nbr_f, nom2);
		
	else if (!strcmp(K->type,"sym")&&!strcmp(type,"sym"))
		Krf = sousmatrice_sym(ptr,nomK, f, nbr_f, nom2);	
	
	return Krf;
}

//fpub : sous vecteur
matrices sousvecteur(matrices ptr,char *nom1, int *r, int nbr_r, char *nom2)
{
	matrices ptr1=recherche(ptr,nom1);
	matrices ptr2=creation(nbr_r, 1,nom2,ptr ,"plein");
	int i;
	
	for(i=0; i<nbr_r; i++)
	{
		ptr2->mat[i][0]=ptr1->mat[r[i]][0];
	}
	return ptr2;
}

//fpriv:tagrossetante
double** cavamarcher(double** mat1,double** mat2, int n, int m)
{
   int i;
   int j;

   for(i=0;i<n;i++)
   {
		for(j=0;j<m;j++)
		{
			printf("%d,%d//",i,j);
         if(i<=j)
         {
				mat2[i][j]=mat1[i][j-i];
				
         }

		}
		printf("\n");
	}
return mat2;
}
//fpub : permet la résolution de l'équation AX=B
matrices resolutioneq(matrices ptr, char *nom1, char *nom2, char *nom3)
{
	matrices ptr1= recherche(ptr,nom1);
	matrices ptr2=recherche(ptr,nom2);
	matrices ptr3=creation( ptr1->n,1, nom3,ptr, "plein");

	if(ptr1!=NULL)
		{
			if (!strcmp(ptr1->type, "plein"))
			solveplein(ptr1->mat, ptr2->mat, ptr3->mat, ptr1->n, ptr2->m);
		else{
         double** mattemp = (double**)malloc(ptr1->n * sizeof(double*));
         for(int i = 0; i < ptr1->n; i++)
            {
                mattemp[i] = (double*)malloc(ptr1->m * sizeof(double));
         }
            
         cavamarcher(ptr1->mat,mattemp,ptr1->n,ptr1->m);
         
         
			solvesym(mattemp, ptr2->mat, ptr3->mat, ptr1->n, ptr2->m);
         
         
         for(int i = 0; i < ptr1->n; i++)
            {
                free(mattemp[i]);
            }
            free(mattemp);
	}
   }
	return ptr3;
}
