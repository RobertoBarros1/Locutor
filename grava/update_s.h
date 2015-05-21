#ifndef UPDATE_S_H_
#define UPDATE_S_H_

void update_s
(
	double **x,        // sequence of feature vectors x[t][i]
	int dim,           // dimension of feature vectors
	int nFrames,       // number of feature vectors in x
	struct mixture *l, // GMMs 
	int nGaussians,    // number of Gaussians in the mixture
	double **m,        // gaussian means m[nGaussians][dim]
	double ***s1       // gaussian variances s[nGaussians][dim]
);

#endif /*UPDATE_S_H_*/
