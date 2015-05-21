#ifndef APOSTERIORI_H_
#define APOSTERIORI_H_

// Calculate the a posteriori probabilities
double aposteriori
(
	double **x, // sequence of feature vectors x[t][i]
	int dim,    // dimension of feature vectors
	int nFrames,    // number of feature vectors in x
	struct mixture *l,          // GMMs 
	int nGaussians  // number of Gaussians in the mixture
);

#endif /*APOSTERIORI_H_*/
