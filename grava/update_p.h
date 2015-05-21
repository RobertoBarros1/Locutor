#ifndef UPDATE_P_H_
#define UPDATE_P_H_

void update_p
(
	double **x, // sequence of feature vectors x[t][i]
	int dim,    // dimension of feature vectors
	int nFrames,    // number of feature vectors in x
	struct mixture *l,          // GMMs 
	int nGaussians,  // number of Gaussians in the mixture
	double *p
);

#endif /*UPDATE_P_H_*/
