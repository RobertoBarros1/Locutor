// Calculate P(x[t]|M)

#include "structs.h"
#include "b.h"

double mixture
(
  double *par,         // feature vector
  struct mixture *l, // GMM models
  int nGaussians,    // number of Gaussians in the mixture
  int dim            // dimension of the acoustic vectors
)
{
	double p; // P(O|M)
	int j;    // counter
	
    p = 0.0;
    for (j=0;j<nGaussians;j++)
      p += l[j].p * b(par,l[j].m,l[j].s,dim);

    return p;
}
