#ifndef UPDATE_M_H_
#define UPDATE_M_H_

void update_m
(
	double **x,        // sequence of feature vectors x[t][i]
	int dim,           // dimension of feature vectors
	int nFrames,       // number of feature vectors in x
	struct mixture *l, // GMMs 
	int nGaussians,    // number of Gaussians in the mixture
	double ***m1       // gaussian means m[nGaussians][dim]
);

#endif /*UPDATE_M_H_*/
