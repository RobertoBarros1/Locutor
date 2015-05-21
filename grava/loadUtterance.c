#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int loadUtterance
(
	char *utteranceFilename, // file with the training utterances listing
	int dim,                  // dimension of feature vectors
	int *nFrames1,   		  // total number of read frames
	double ***x1              // stores the utterances
)
{
	FILE *ptr;       // file handler
	int size;        // size of each utterance file, in bytes
	double **x;      // stores the utterances
	int nFrames;     // total number of read frames
	int i, frame;           // counters
	size_t t;
	float *temp;    // aux variable for file reading
		
	// allocating memory
	temp = malloc(sizeof(float)*dim);
	
	// Counting the total number of frames
	nFrames = 0;
	ptr=fopen(utteranceFilename,"rb");
	if (ptr != NULL)
	{
		fseek (ptr , 0 , SEEK_END);
    	size = ftell (ptr);
    	nFrames += size/dim/sizeof(float);	
	}
	else
	{
	    printf("Error reading file %s.\n",utteranceFilename);
		exit(1);
	}
/*	printf("Number of frames: %d\n",nFrames);*/
  	
  	// Allocating memory for utterance
  	x = malloc(sizeof(double *)*nFrames);
  	for (i=0;i<nFrames;i++)
  		x[i] = malloc(sizeof(double)*dim);

    // Reading utterance
    rewind(ptr);  	
    frame=0;
	while(!feof(ptr))
	{
		t = fread(temp,sizeof(float),dim,ptr);
		if (t == dim)
		{
			for (i=0;i<dim;i++)
				x[frame][i] = (double)temp[i];
			frame++;
		}
/*		else*/
/*		{*/
/*		    printf("Error reading file %s.\n",utteranceFilename);*/
/*		    exit(1);*/
/*		}*/
	}	
	fclose(ptr);
	
	*nFrames1 = nFrames;
	*x1 = x;  	
  	  	
  	free(temp);
  	return 0;
}
