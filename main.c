#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

double factorielle(double n)
{
  if (n == 0)
    return 1;
  else
    return(n * factorielle(n-1));
}

void createPoisson(struct Coordonnees *valeurs_graphiques, int n, double p)
{
	valeurs_graphiques->x = malloc(n * sizeof(int));
	valeurs_graphiques->y = malloc(n * sizeof(double));

	double lambda = n*p;

	for(int k=0; k<=n; k++)
	{
		valeurs_graphiques->x[k] = k;
		valeurs_graphiques->y[k] = (exp(-lambda)*pow(lambda, k))/factorielle(k);
		//printf("x: %d y: %f\n", valeurs_graphiques.x[k], valeurs_graphiques.y[k]);
	}
}

void createBinomiale(struct Coordonnees *valeurs_graphiques, int n, double p)
{
	valeurs_graphiques->x = malloc(n * sizeof(int));
	valeurs_graphiques->y = malloc(n * sizeof(double));

	for(int k=0; k<=n; k++)
	{
		valeurs_graphiques->x[k] = k;
		valeurs_graphiques->y[k] = (factorielle(n)/(factorielle(k)*factorielle(n-k)))*pow(p, k)*pow(1-p,n-k);
		//printf("x: %d y: %f\n", valeurs_graphiques->x[k], valeurs_graphiques->y[k]);
	}
}

void sauvegarde(FILE *fp, struct Coordonnees valeurs_graphiques, int taille_tableau)
{
  fp = freopen ("./valeurs_courbes.csv", "a", fp);

  for(int i=0; i<=taille_tableau; i++)
  {
    fprintf(fp, "%d \t %f \n", valeurs_graphiques.x[i],  valeurs_graphiques.y[i]);
  }

  fprintf(fp, "\n\n\n\n");
}

int main(int argc, char *argv[])
{
	if ( argc != 3) { printf(" Usage : %s n p \n", argv[0]); exit(-1); }

	int n = atoi(argv[1]);
	double p = atof(argv[2]);

	FILE *fp;

  	fp = fopen ("./valeurs_courbes.csv", "w");
	/*if ( p >= 0,1 ) { printf(" Usage : p <= 0,1 \n"); exit(-1);}
	if ( n*p >= 15 ) { printf(" Usage : np <= 15 \n"); exit(-1);}
	if ( n <= 30 ) { printf(" Usage : n >= 30 \n"); exit(-1);}*/

	struct Coordonnees valeurs_binomiale;
	struct Coordonnees valeurs_poisson;

	createBinomiale(&valeurs_binomiale, n, p);
	createPoisson(&valeurs_poisson, n, p);
	
	sauvegarde(fp, valeurs_binomiale, n);
	sauvegarde(fp, valeurs_poisson, n);

	fclose(fp);

	free(valeurs_binomiale.x);
	free(valeurs_binomiale.y);
	free(valeurs_poisson.x);
	free(valeurs_poisson.y);
}