// Calculate P(0|M)

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "structs.h"
#include "mixture.h"

double aposteriori
(
	double **par, // sequence of feature vectors x[t][i]
	int dim,    // dimension of feature vectors
	int nWindows,    // number of feature vectors in x
	struct mixture *l,          // GMMs 
	int nGaussians  // number of Gaussians in the mixture
)
{
    double p; // P(i|X,M)
    double soma; // P(X|M)
    int t; // counter
    	
    soma = 0.0;	
    for (t=0;t<nWindows;t++)	
    {
	    p = mixture(par[t],l,nGaussians,dim);
/*		printf("t=%d\n",t);*/
/*		printf("p=%f\n",p);*/
		soma += log10(p);
	}    
/*	printf("Inside: %f\n",soma);*/
        	
    return soma;
}
