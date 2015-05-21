#ifndef MIXTURE_H_
#define MIXTURE_H_

// Calculate the a posteriori probabilities
double mixture
(
  double *x,         // feature vector
  struct mixture *l, // GMM models
  int nGaussians,    // number of Gaussians in the mixture
  int dim            // dimension of the acoustic vectors
);

#endif /*MIXTURE_H_*/
