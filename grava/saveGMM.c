#include <stdio.h>

#include "structs.h"

void saveGMM
(
	int nGaussians,
	int dim,
	struct mixture *l
	
)
{
	FILE *ptr;
	int i,j;
		
	ptr = fopen("Robertogmm.dat","wb");
	fwrite(&nGaussians,sizeof(int),1,ptr);
	fwrite(&dim,sizeof(int),1,ptr);
	for (i=0;i<nGaussians;i++)
	{
		fwrite(&l[i].p,sizeof(double),1,ptr);
		for (j=0;j<dim;j++)
			fwrite(&l[i].m[j],sizeof(double),1,ptr);
		for (j=0;j<dim;j++)
			fwrite(&l[i].s[j],sizeof(double),1,ptr);	
	}
	fclose(ptr);
}
