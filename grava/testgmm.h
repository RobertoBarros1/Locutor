#ifndef TESTGMM_H_
#define TESTGMM_H_

double testgmm
(
	double **x, // observation sequence
	int dim, //dimension of feature vectors
	int nFrames, // number of vectors in x
	struct mixture *l, // GMM
	int nGaussians
);

#endif /*TESTGMM_H_*/
