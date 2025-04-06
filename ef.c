//ef.c//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ef.h"
#include "calcul.h"

//fpub:affectation des resultats de F dans les noeuds
void affecterresults(char* F,char* U, struct noeud *noeuds, matrices ptr)
   {
	int p;
	//recherche F et U
	matrices matf;
   matrices matU;
	matf=recherche(ptr, F);
   matU=recherche(ptr, U);
	//copie des données de F dans les noeuds
	for (p=0; p<matf->n; p++)
	{
		noeuds[p].eff = matf->mat[p][0];
	}
   //copie des données de U dans les noeuds
	for (p=0; p<matU->n; p++)
	{
		noeuds[p].dep = matU->mat[p][0];
	}
   
}

//fpub:affichage d'une liste
void affichageliste(int nnoe,struct noeud *noeuds)
{
	int i;
	for (i=0;i<nnoe;i++){
		printf("( (%d) (%lf) (%lf) )",noeuds[i].num,noeuds[i].dep,noeuds[i].eff);
		//sauts de lignes pour lisibilité
		printf("\n");
	}
	printf("\n\n");
}

//fpub:construction de K
matrices assemblageK(int nnoe, int nelt, struct element *elements, char* nomK, matrices ptr,char* type)
{
	int p, i, j;
	matrices K = creation(nnoe,nnoe,nomK,ptr,type);
	//cas ou K est matrice pleine
	if(!strcmp(type,"plein")){
		for (p=0; p<nelt; p++){
			//definition i et j
			i = elements[p].k[0] - 1;
			j = elements[p].k[1] - 1;
			//calcul matrice K
			K->mat[i][i] += elements[p].raid;
			K->mat[i][j] -= elements[p].raid;
			K->mat[j][i] -= elements[p].raid;
			K->mat[j][j] += elements[p].raid;
}}
	//cas ou K est matrice symetrique
	else if(!strcmp(type,"sym")){
		int min, max;
		for (p=0; p<nelt; p++){
			//definition i et j
			i = elements[p].k[0] - 1;
			j = elements[p].k[1] - 1;
			//definition min et max (en fonction de si i ou j est plus elevé)
			if (i<=j){
				min=i;
				max=j;
		}
			else{ 
				min=j;
				max=i;
		}
			//calcul matrice K
			K->mat[min][0] += elements[p].raid;
			K->mat[min][max-min] -= elements[p].raid;
			K->mat[max][0] += elements[p].raid;
}
}
return K;
}

//fpub:construction de U
matrices assemblageU(int nnoe, struct noeud *noeuds, char* nomU, matrices ptr)
   {
	int p;
	matrices U = creation(nnoe,1,nomU,ptr,"plein");
	//copie données des noeuds dans U
	for (p=0; p<nnoe; p++)
    {
        U->mat[p][0] = noeuds[p].dep;
}
return U;
}

//fpub: entrée par l'utilisateur des données des elements
struct element* entreelmt(int nelt, int nnoe)
{
	int n=nelt;
	int p;
	//creation du tableau element vide
	struct element* elements=NULL;
	elements= malloc(n*sizeof(struct element));
	//entrée des données des elements
	for ( p=0;p<n;p++){
		elements[p].num=p+1;
		printf("raideur de l element %d: ",p+1);
		scanf("%lf", &elements[p].raid);
		printf("connections de l element %d: ",p+1);
		//boucle pour le cas ou l'utilisateur rentre des mauvaises valeurs
		do{
		printf("entrez la premiere connection ");
		scanf("%d", &elements[p].k[0]);
		printf("entrez la deuxieme connection ");
		scanf("%d", &elements[p].k[1]);
		}while (0>=elements[p].k[0] || nnoe<elements[p].k[0] || 0>=elements[p].k[1] || nnoe<elements[p].k[1] );
		printf("\n");
}
return elements;
}
//fpub: entrée par l'utilisateur des données des noeuds (version sans inconnues)
struct noeud* entrenoeud(int nnoe)
{
	int n=nnoe;
	int p;
	//creation du tableau noeud vide
	struct noeud* noeuds=NULL;
	noeuds= malloc(n*sizeof(struct noeud));
	//entrée des données des noeuds
	for ( p=0;p<n;p++){
		noeuds[p].num=p+1;
		printf("deplacement du noeud %d ",p+1);
		scanf("%lf", &noeuds[p].dep);
      printf("\n");
}
return noeuds;
}

//fpub: entrée par l'utilisateur des données des noeuds (version inconnues)
struct noeud* entrenoeud2(int nnoe, struct donnee *RF)
{
	char depeff[20];
	int n=nnoe;
	int p;

	
	//tentative structure r et f 
	int *ftemp= (int*)malloc(nnoe*sizeof(int));
	int *rtemp= (int*)malloc(nnoe*sizeof(int));

	RF->nbr_r=0;
	RF->nbr_f=0;


	
	//creation du tableau noeud vide
	struct noeud* noeuds=NULL;
	noeuds= malloc(n*sizeof(struct noeud));
	//entrée des données des noeuds
	for ( p=0;p<n;p++){
		//demande si on connait les deplacements ou efforts
		printf("connait on le deplacement ou effort du noeud %d? (d/e): ",p+1);
		scanf("%s",depeff);
		//boucle pour clarification en cas d'erreur de l'utilisateur
		while (strcmp(depeff,"e")!=0 && strcmp(depeff,"d")!=0){
			printf("tapez e pour effort ou d pour deplacement du noeud %d: ",p+1);
			scanf("%s",depeff);
		}
		noeuds[p].num=p+1;
		//cas ou on demande un deplacement
		if (strcmp(depeff,"d")==0){
		printf("deplacement du noeud %d ",p+1);
		scanf("%lf", &noeuds[p].dep);
      printf("\n");

		rtemp[RF->nbr_r]=p;
		RF->nbr_r+=1;
		}
		//cas ou on demande un effort
		else{
		printf("effort du noeud %d ",p+1);
		scanf("%lf", &noeuds[p].eff);
      printf("\n");
		noeuds[p].dep=0;

		ftemp[RF->nbr_f]=p;
		RF->nbr_f+=1;
		}
}
	RF->f=ftemp;
	RF->r=rtemp;
return noeuds;
}

//fpub: assemblage Ff
matrices assemblageFf(matrices ptr, int nbr_f, int *f, struct noeud* noeuds)
{int i;
matrices Ff=creation(nbr_f, 1,"Ff",ptr ,"plein");
	for (i=0;i<nbr_f;i++)
{
	Ff->mat[i][0]= noeuds[f[i]].eff;
}
	
	
	
	return Ff;
}	

//fpub: entrée par l'utilisateur de la taille des elements
int tailleelm()
{  
	int n;
	printf("nombre d element");
	scanf("%d", &n);
	return n;
}

//fpub: entrée par l'utilisateur de la taille des noeuds
int taillenoeud()
{  
	int n;
	printf("nombre de noeuds");
	scanf("%d", &n);
	return n;
}

//fpub: construction de U2
matrices assemblageU2(matrices ptr, char *Uf, char *U, int *f, int nbr_f)
{
	matrices ptr1=recherche(ptr, U);
	matrices ptr2=recherche(ptr, Uf);
	matrices ptr3=creation(ptr1->n, ptr1->m, "U2", ptr, ptr1->type);
	int i;
	
	for (i=0;i<ptr1->n;i++)
	{
		ptr3->mat[i][0]=ptr1->mat[i][0];
	}
	
	for (i=0;i<nbr_f;i++)
	{
		ptr3->mat[f[i]][0]=ptr2->mat[i][0];
	}
	return ptr3;
}

//fpub : sous vecteur
matrices sousvecteur(matrices ptr,char *nom1, int *r, int nbr_r, char *nom2)
{
	matrices ptr1=recherche(ptr,nom1);
	matrices ptr2=creation(nbr_r, 1,nom2,ptr ,"plein");
	int i;
	//copie des valeures de nom1,aux indices de r, dans notre vecteur
	for(i=0; i<nbr_r; i++)
	{
		ptr2->mat[i][0]=ptr1->mat[r[i]][0];
	}
	return ptr2;
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
