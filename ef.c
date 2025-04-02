//ef.c//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ef.h"
#include "calcul.h"

//fpub:affectation des resultats de F dans les noeuds
void affecterresults(char* F, struct noeud *noeuds,matrices ptr)
   {
	int p;
	//recherche F
	matrices matf;
	matf=recherche(ptr, F);
	//copie des données de F dans les noeuds
	for (p=0; p<matf->n; p++)
	{
		noeuds[p].eff = matf->mat[p][0];
	}
}

//fpub:affichage d'une liste
void affichageliste(int nnoe,struct noeud *noeuds)
{
	int i;
	for (i=0;i<nnoe;i++){
		printf("( (%d) (%d) (%lf) )",noeuds[i].num,noeuds[i].dep,noeuds[i].eff);
		//sauts de lignes pour lisibilité
		printf("\n");
	}
	printf("\n\n");
}

//fpub:construction de K
matrices assemblageK(int nnoe, int nelt, struct element *elements, char* nmK,matrices ptr,char* symp)
{
	int p, i, j;
	matrices K = creation(nnoe,nnoe,nmK,ptr,symp);
	//cas ou K est matrice pleine
	if(!strcmp(symp,"plein")){
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
	else if(!strcmp(symp,"sym")){
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
matrices assemblageU(int nnoe, struct noeud *noeuds, char* nmU,matrices ptr)
   {
	int p;
	matrices U = creation(nnoe,1,nmU,ptr,"plein");
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
		printf("raideur de l element %d (double)",p+1);
		scanf("%lf", &elements[p].raid);
		printf("connections de l element %d",p+1);
		//boucle pour le cas ou l'utilisateur rentre des mauvaises valeurs
		do{
		printf("entrez la premiere connection");
		scanf("%d", &elements[p].k[0]);
		printf("entrez la deuxieme connection");
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
		printf("deplacement du noeud %d",p+1);
		scanf("%d", &noeuds[p].dep);
}
return noeuds;
}

//fpub: entrée par l'utilisateur des données des noeuds (version inconnues)
struct noeud* entrenoeud2(int nnoe, int* r, int* f)
{
	char depeff[20];
	int n=nnoe;
	int p;
	int i,j;
	//creation du tableau noeud vide
	struct noeud* noeuds=NULL;
	noeuds= malloc(n*sizeof(struct noeud));
	i=0;
	j=0;
	//entrée des données des noeuds
	for ( p=0;p<n;p++){
		//demande si on connait les deplacements ou efforts
		printf("connait on le deplacement ou effort du noeud? (d/e)");
		scanf("%s",depeff);
		//boucle pour clarification en cas d'erreur de l'utilisateur
		while (strcmp(depeff,"e")!=0 && strcmp(depeff,"d")!=0){
			printf("tapez e pour effort ou d pour deplacement");
			scanf("%s",depeff);
		}
		noeuds[p].num=p+1;
		//cas ou on demande un deplacement
		if (strcmp(depeff,"d")==0){
		printf("deplacement du noeud %d",p+1);
		scanf("%d", &noeuds[p].dep);
		i=i+1;
		r[i]=p;
		}
		//cas ou on demande un effort
		else{
		printf("effort du noeud %d",p+1);
		scanf("%lf", &noeuds[p].eff);
		j=j+1;
		f[j]=p;
		}
}
return noeuds;
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
