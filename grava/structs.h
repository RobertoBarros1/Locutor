#ifndef STRUCTS_H_
#define STRUCTS_H_

#define PI 2*asin(1)

#define INF 1.5e308
struct mixture
{
	double p;   // mixture weight
	double *m;  // gaussian mean
	double *s; // covariance matrix (only the diagonal elements are stored)
};

#endif /*STRUCTS_H_*/
