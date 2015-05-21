// Generates random numbers from a Gaussian distribution with mean m and variance s
// using the Box & Muller transformation method
#include<stdlib.h>
#include<math.h>

#include "structs.h"

double normrnd(double m, double s)
{
	double u1,u2;
	
	// Generating uniformly distributed random numbers in the (0,1) interval
	u1 = (double)rand()/RAND_MAX;
	u2 = (double)rand()/RAND_MAX;
	
	return (cos(2*PI*u2)*sqrt(-2*log(u1))+m)*sqrt(s);
}