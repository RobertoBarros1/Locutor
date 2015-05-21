#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

void loadGMM
(
	int nGaussians,
	int dim,
	struct mixture **l1,
	char *GMMFilename
)
{
	FILE *ptr;
	int i,j;
	struct mixture *l;
		
	ptr = fopen(GMMFilename,"rb");
	fread(&nGaussians,sizeof(int),1,ptr);
	fread(&dim,sizeof(int),1,ptr);
	
	// Allocating memory for GMMs
	l = malloc(sizeof(struct mixture)*nGaussians);
	for (i=0;i<nGaussians;i++)
	{
	  l[i].m = malloc(sizeof(double)*dim);
	  l[i].s = malloc(sizeof(double)*dim);
	}
	
	for (i=0;i<nGaussians;i++)
	{
		fread(&l[i].p,sizeof(double),1,ptr);
		for (j=0;j<dim;j++)
			fread(&l[i].m[j],sizeof(double),1,ptr);
		for (j=0;j<dim;j++)
			fread(&l[i].s[j],sizeof(double),1,ptr);	
	}
	fclose(ptr);
	
	*l1 = l;
}
