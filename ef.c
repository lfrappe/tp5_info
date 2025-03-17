//ef.c//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ef.h"
#include "calcul.h"


void affecterresults(char* F, struct noeud *noeuds,matrices ptr)
   {
      int p;
      matrices matf;
    matf=recherche(ptr, F);

    for (p=0; p<matf->n; p++)
    {
         noeuds[p].eff = matf->mat[p][0];

}
}

void affichageliste(int nnoe,struct noeud *noeuds)
{
   int i;
   for (i=0;i<nnoe;i++){
      printf("( (%d) (%d) (%lf) )",noeuds[i].num,noeuds[i].dep,noeuds[i].eff);
      printf("\n");
}
printf("\n\n");
}

matrices assemblageK(int nnoe, int nelt, struct element *elements, char* nmK,matrices ptr,char* symp)
   {
      int p, i, j;
      matrices K = creation(nnoe,nnoe,nmK,ptr,symp);
     
      if(!strcmp(symp,"plein")){

      for (p=0; p<nelt; p++){
     
       i = elements[p].k[0] - 1;
       j = elements[p].k[1] - 1;

       K->mat[i][i] += elements[p].raid;
       K->mat[i][j] -= elements[p].raid;
       K->mat[j][i] -= elements[p].raid;
       K->mat[j][j] += elements[p].raid;
}
}
      else if(!strcmp(symp,"sym")){
         int min, max;
         
      for (p=0; p<nelt; p++){
                  
       i = elements[p].k[0] - 1;
       j = elements[p].k[1] - 1;


      if (i<=j){
         min=i;
         max=j;
      }
      else{ 
         min=j;
         max=i;
      }

       K->mat[min][0] += elements[p].raid;
       K->mat[min][max-min] -= elements[p].raid;
       K->mat[max][0] += elements[p].raid;
}
         
         
         
}
return K;
}

matrices assemblageU(int nnoe, struct noeud *noeuds, char* nmU,matrices ptr)
   {
      int p;
    matrices U = creation(nnoe,1,nmU,ptr,"plein");

    for (p=0; p<nnoe; p++)
    {
        U->mat[p][0] = noeuds[p].dep;

}
return U;
}

struct element* entreelmt(int nelt, int nnoe)
{
   int n=nelt;
   int p;
   struct element* elements=NULL;
   elements= malloc(n*sizeof(struct element));
   for ( p=0;p<n;p++){

      elements[p].num=p+1;
      printf("raideur de l element %d (double)",p+1);
      scanf("%lf", &elements[p].raid);
      printf("connections de l element %d",p+1);
      do{
      scanf("%d", &elements[p].k[0]);
      scanf("%d", &elements[p].k[1]);
}while (0>=elements[p].k[0] || nnoe<elements[p].k[0] || 0>=elements[p].k[1] || nnoe<elements[p].k[1] );
}
return elements;
}

struct noeud* entrenoeud(int nnoe)
{
   int n=nnoe;
   int p;
   struct noeud* noeuds=NULL;

   noeuds= malloc(n*sizeof(struct noeud));
   for ( p=0;p<n;p++){

      noeuds[p].num=p+1;
      printf("deplacement du noeud %d",p+1);
      scanf("%d", &noeuds[p].dep);

}
return noeuds;
}

int tailleelm()
{  
   int n;
   printf("nombre d element");
   scanf("%d", &n);
   return n;
}

int taillenoeud()
{  
   int n;
   printf("nombre de noeuds");
   scanf("%d", &n);
   return n;
}
