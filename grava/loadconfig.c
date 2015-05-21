// Loads the training setup from a configuration file

#include <stdio.h>
#include <string.h>

int loadconfig
(
  char *configFile,
  int *nGaussians,
  int *dim,
  char *GMMFilename,
  char *UBMFilename,
  char *utteranceFilename
)
{
	// Local variables
  	FILE *ptr; // file handler
  	char data[512]; // aux variables for file reading

  	// Opening configuration file
  	ptr = fopen(configFile,"rt");
	
  	if (ptr == NULL)
  	{
		printf("Error opening file %s.\n",configFile);
		return 1;
  	}
	
  	// Reading informations
  	fgets(data, 500, ptr);

  	// removing control characters (\r \n) frm the end of string
  	while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
  		data[strlen(data)-1] = '\0';

  	while (!feof(ptr))
  	{
  	    // File with the utterance to be verified
    	if (strstr(data,"Utterance") != NULL)
	  		sscanf(data,"Utterance=%s",utteranceFilename);
	  	
	  	// File with the GMM
    	if (strstr(data,"GMM file=") != NULL)
	  		sscanf(data,"GMM file=%s",GMMFilename);
	  		
	  	// File with the UBM
    	if (strstr(data,"UBM file=") != NULL)
	  		sscanf(data,"UBM file=%s",UBMFilename);
	  			
  		// Number of Gaussians in the mixture
        if (strstr(data,"Number of Gaussians=") != NULL)
	  		sscanf(data,"Number of Gaussians=%d",nGaussians);

		// Dimension of feature vectors
		if (strstr(data,"Dimension of feature vectors=") != NULL)
	  		sscanf(data,"Dimension of feature vectors=%d",dim);

		// Reading new entry from file
		if (!feof(ptr))
			fgets(data, 500, ptr);
		//fscanf(ptr,"%s",data);
		
  		// removing control characters (\r \n) frm the end of string
		while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
			data[strlen(data)-1] = '\0';
	} // end of configuration file reading

	fclose(ptr);
	
  return (0);
}
