// Function that reads the utterances to be verified

#ifndef LOADUTTERANCE_H_
#define LOADUTTERANCE_H_

int loadUtterance
(
	char *utteranceFilename, // file with the training utterances listing
	int dim,                  // dimension of feature vectors
	int *nFrames1,   		  // total number of read frames
	double ***x1              // stores the utterances
);

#endif /*LOADUTTERANCE_H_*/
