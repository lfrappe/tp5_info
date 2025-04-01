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
	//verification que la matrice existe
    if (tab1 == NULL)
   {
		printf("Matrice inexistante\n");
		return;
      }
      
    //verification type matrice
    if (!strcmp(type, "plein"))
   {
		affichage_plein(tab1->mat, tab1->n, tab1->m);
  }
    else if (!strcmp(type, "sym")) {
		affichage_sym(tab1->mat, tab1->n);
  }
     //saut de lignes pour la présentation
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
		//saut de lignes pour la présentation
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
			//espaces et saut de lignes pour la présentation
                printf("         ");
            }
        }
            printf("\n");
    }
}

//fpub:Fonction recherche
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

//fpub:Fonction création matrice
matrices creation(int n, int m, char* nom,matrices ptr,char* type)
{
   //creation matrice 
   matrices temp = malloc(sizeof(struct matrice));
   strcpy( temp->nom,nom);
   temp->n=n, temp->m=m;
   //choix type matrice
   if (!strcmp(type, "plein")) {
        temp-> mat = creation_plein(n, m);
    } else if (!strcmp(type, "sym")) {
        temp-> mat = creation_sym(n);
    }
   //inclusion dans la liste chainée
   temp->next= ptr ;
   ptr = temp;
   
   return temp;
}

//fpriv:creation matrice pleine
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

//fpub:Fonction destruction
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
matrices produit(char* tab1,char* tab2,char* nom,matrices ptr,char* type)
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

//ajouts TD5

//fpub : difference C = A - B 
struct matrice* difference(struct matrice* ptr, char* nom_A, char* nom_B, char* nom_C)
{
	int i,j;
	struct matrice *difference=creation(nom_C,recherche(nom_A)->n,recherche(nom_B)->m,"plein");
	
    for (i=0;i<difference->n;i++)
    {
        for (j=0;j<difference->m;j++)
        {
            difference->composante[i][j]=recherche(nom_A)->composante[i][j]-recherche(nom_B)->composante[i][j];
		}
	}
	difference->next=ptr;
	
	return difference;
}

//fpriv : extraction plein vers plein 
struct matrice *sousmatrice_plein_vers_plein(struct matrice *K,int *r,int nbr_r,int *f,int nbr_f,char *nom2)
{
	int i,j;
	struct matrice *Krf=creation (nom2, nbr_f, nbr_r, "plein");
	
	for(i=0;i<nbr_f;i++)
		{
		for(j=0;j<nbr_r;j++)
			{

				Krf->composante[i][j]=K->composante[f[i]][r[j]];
				
	return Krf;
}}
}


//fpriv : extraction sym vers plein
struct matrice *sousmatrice_sym_vers_plein(struct matrice *K, int *r,int nbr_r,int *f,int nbr_f, char* nom2)
{
	int i,j;
	struct matrice *Krf=creation(nom2, nbr_f, nbr_r, "plein");
	for(i=0;i<nbr_f;i++)
		for(j=0;j<nbr_r;j++)
		{
			if(r[i]<=f[j])
				Krf->composante[i][j]=K->composante[r[j]][f[i]];
			else
				Krf->composante[i][j]=K->composante[f[i]][r[j]];
		}
	
	return Krf;
}


//fpriv : extraction sym
struct matrice *sousmatrice_sym (struct matrice *K,int *f,int nbr_f,char* nom2)
{
	int i,j;
	struct matrice *Kff=creation(nom2, nbr_f, nbr_f, "sym");
	
	for(i=0;i<nbr_f;i++)
		for(j=0;j<nbr_f;j++)
		{
			if(f[i]<=f[j])
				Kff->composante[i][j]=K->composante[f[i]][f[j]];
			else
				Kff->composante[i][j]=K->composante[f[j]][f[i]];
		}
	
	return Kff;

//fpub : sous-matrice
struct matrice* sousmatrice(char *nom1, int *r, int nbr_r, int *f,int nbr_f, char *nom2, char *type)
{
	struct matrice* K = recherche(nom1);
	struct matrice *Krf;
	
	if(!strcmp(type,"plein")&&!strcmp(K->type,"plein"))
		Krf= sousmatrice_plein_vers_plein(K, r, nbr_r, f, nbr_f, nom2);
		
	else if(!strcmp(type,"plein")&&!strcmp(K->type,"sym"))
		Krf = sousmatrice_sym_vers_plein(K, r, nbr_r, f, nbr_f, nom2);
		
	else if (!strcmp(type,"sym"))
		Krf = sousmatrice_sym(K, f, nbr_f, nom2);	
	
	return Krf;
}



//fpub : sous vecteur
struct matrice *sousvecteur(char *nom1, int *r, int nbr, int* f, char *nom2, char* type)
{
	struct matrice *ptr1=recherche(nom1);
	struct matrice *ptr2=creation(nom2, nbr, 1, "plein");
	int i;
	
	for(i=0; i<nbr; i++)
	{
		ptr2->composante[i][0]=ptr1->composante[r[i]][0];
	}
	return ptr2;
}



//fpub : permet la résolution de l'équation AX=B
void resolutioneq(char *nom1, char *nom2, char *nom3)
{
	struct matrice *ptr1= recherche(nom1);
	struct matrice *ptr2=recherche(nom2);
	struct matrice *ptr3=creation(nom3, ptr1->n, 1, "plein");
	if(ptr1!=NULL)
		{
			if (!strcmp(ptr1->type, "plein"))
			solveplein(ptr1->composante, ptr2->composante, ptr3->composante, ptr1->n, ptr2->m);
		else
			solvesym(ptr1->composante, ptr2->composante, ptr3->composante, ptr1->n, ptr2->m);
	}
}
