// Update the mixture coefficients

#include <stdlib.h>

#include "structs.h"
#include "mixture2.h"

void update_p
(
	double **x, // sequence of feature vectors x[t][i]
	int dim,    // dimension of feature vectors
	int nFrames,    // number of feature vectors in x
	struct mixture *l,          // GMMs 
	int nGaussians,  // number of Gaussians in the mixture
	double *p
)
{
    int i,t; // counters
    	
	// Updating mixture coefficients
	for (i=0;i<nGaussians;i++)
		p[i] = 0;

    for (i=0;i<nGaussians;i++)
    {
		for (t=0;t<nFrames;t++)
        	p[i] += mixture2(x[t],i,l,nGaussians,dim);
  		p[i] /= (double)nFrames;
    }
}
