// Function that reads the training utterances from files

#ifndef LOADUTTERANCES_H_
#define LOADUTTERANCES_H_

int loadUtterances
(
	char *trainingUtterances, // file with the training utterances listing
	int dim,                  // dimension of feature vectors
	int *nFrames1,   		  // total number of read frames
	double ***x1              // stores the utterances
);

#endif /*LOADUTTERANCES_H_*/
