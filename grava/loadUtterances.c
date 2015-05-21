#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int loadUtterances
(
	char *trainingUtterances, // file with the training utterances listing
	int dim,                  // dimension of feature vectors
	int *nFrames1,   		  // total number of read frames
	double ***x1              // stores the utterances
)
{
	FILE *ptr,*ptr1; // file handlers
	char data[512];  // aux variable for file reading
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
	
	// Opening utterances file
  	ptr = fopen(trainingUtterances,"rt");
	
  	if (ptr == NULL)
  	{
		printf("Error opening file %s.\n",trainingUtterances);
		return 1;
  	}
	
  	// Reading information
  	fgets(data, 500, ptr);
  	
  	// removing control characters (\r \n) frm the end of string
  	while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
  		data[strlen(data)-1] = '\0';

  	while (!feof(ptr))
  	{
  		// Opening file for reading
  		ptr1=fopen(data,"rb");
  		if (ptr1 != NULL)
  		{
  			fseek (ptr1 , 0 , SEEK_END);
        	size = ftell (ptr1);
        	fclose(ptr1);

  	    	nFrames += size/dim/sizeof(float);	
  		}
  		
  		// Reading new entry from file
		if (!feof(ptr))
		{
			fgets(data, 500, ptr);
		
			// removing control characters (\r \n) frm the end of string
			while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
				data[strlen(data)-1] = '\0';
		}
  	} // end of utterances file reading
  	
  	// Allocating memory
  	x = malloc(sizeof(double *)*nFrames);
  	for (i=0;i<nFrames;i++)
  		x[i] = malloc(sizeof(double)*dim);
  	
  	// Reading utterances
  	rewind(ptr);

  	// Reading information
  	fgets(data, 500, ptr);
  	
  	// removing control characters (\r \n) frm the end of string
  	while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
  		data[strlen(data)-1] = '\0';

	frame = 0;
  	while (!feof(ptr))
  	{
  		// Opening file for reading
  		ptr1=fopen(data,"rb");
  		if (ptr1 != NULL)
  		{
  			while(!feof(ptr1))
  			{
  				t = fread(temp,sizeof(float),dim,ptr1);
  				if (t == dim)
  				{
  					for (i=0;i<dim;i++)
  						x[frame][i] = (double)temp[i];
  					frame++;
  				}
  			}
        	fclose(ptr1);
  		}

  		// Reading new entry from file
		if (!feof(ptr))
		{
			fgets(data, 500, ptr);
				
  			// removing control characters (\r \n) frm the end of string
			while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
				data[strlen(data)-1] = '\0';
		}
  	} // end of utterances file reading
	fclose(ptr);
	
	*nFrames1 = nFrames;
	*x1 = x;  	
  	  	
  	free(temp);
  	return 0;
}
