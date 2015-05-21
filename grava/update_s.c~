// Update the mixture coefficients

#include <stdlib.h>

#include "structs.h"
#include "mixture2.h"

void update_s
(
	double **x,        // sequence of feature vectors x[t][i]
	int dim,           // dimension of feature vectors
	int nFrames,       // number of feature vectors in x
	struct mixture *l, // GMMs 
	int nGaussians,    // number of Gaussians in the mixture
	double **m,        // gaussian means m[nGaussians][dim]
	double ***s1       // gaussian variances s[nGaussians][dim]
)
{
	double **s;       // Gaussian variances
	double *num, den, aux; // aux variables
    int i,j,t;          // counters
    double threshold = 0.001; // minimum values allowed for the variances
    	
    s = *s1;
	
	// Allocating memory
	num = malloc(sizeof(double)*dim);
	
	// Updating Gaussian means
    for (i=0;i<nGaussians;i++)
    {
    	den = 0.0;
    	for (j=0;j<dim;j++)
    		num[j] = 0.0;
    		
    	for (t=0;t<nFrames;t++)
    	{
        	aux = mixture2(x[t],i,l,nGaussians,dim);
        	den += aux;
        	
        	for (j=0;j<dim;j++)
	      		num[j] += aux*x[t][j]*x[t][j];

    	}
    	for (j=0;j<dim;j++)
    		s[i][j] = num[j]/den-m[i][j]*m[i][j];	
    }
   
    // Limiting the values of the variances
    for(i=0;i<nGaussians;i++)
    	for(j=0;j<dim;j++)
    		if(s[i][j] < threshold)
    			s[i][j] = threshold;
    			
    // Freeing memory
    free (num);
    
    // Returning updated variances
    *s1 = s;
}
