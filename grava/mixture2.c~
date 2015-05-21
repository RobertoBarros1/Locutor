// Calculate the a posteriori probabilities

#include "structs.h"
#include "b.h"

double mixture
(
  double *x,         // feature vector
  int i,             // id of Gaussian under analysis
  struct mixture *l, // GMM models
  int nGaussians,    // number of Gaussians in the mixture
  int dim            // dimension of the acoustic vectors
)
{
	double num, den; // aux variables 
	int j;           // counter
	
	num = l[i].p*b(x,l[i].m,l[i].s,dim);

    den = 0.0;
    for (j=0;j<nGaussians;j++)
      den += l[j].p * b(x,l[j].m,l[j].s,dim);

    return num/den;
}