// Function that calculates the a posteriori probability of an observation, given the GMM

#include <math.h>

#include "structs.h"
#include "b.h"

double testgmm
(
	double **x, // observation sequence
	int dim, //dimension of feature vectors
	int nFrames, // number of vectors in x
	struct mixture *l, // GMM
	int nGaussians
)
{
	int i,t; // counters
	double p = 0.0; // a posteriori probability
	double aux;
	
	for (t=0;t<nFrames;t++)
	{
		aux = 0.0;
		for (i=0;i<nGaussians;i++)
			aux += l[i].p*b(x[t],l[i].m,l[i].s,dim);
		p += log(aux);	
	}
	return p;	
}  
