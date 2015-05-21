// program that computes P(O|M) for a given input utterance
// the utterance must be entered as a sequence of acoustic vectors

#include<stdio.h>
#include<stdlib.h>

#include "structs.h"
#include "showgmm.h"
#include "aposteriori.h"
#include "loadconfig.h"
#include "loadUtterance.h"
#include "loadGMM.h"

int main(int argc, char **argv)
{
	struct mixture *l=NULL; // stores the elements of the GMM
	struct mixture *u=NULL; // stores the elements of the UBM
	int nGaussians; // number of gaussians in the mixture
	int nFrames;    // number of frames in x
	int dim;        // dimension of feature vectors
	int i,t;        // counters
	double **x; // sequence of observation vectors
    double p; // P(O|M) for the GMM
    double g; // P(O|M) for the UBM
	char GMMFilename[512]; // file that stores the GMM
	char UBMFilename[512]; // file that stores the UBM
	char utteranceFilename[512]; // file with utterance to be verified

	
    // Reading arguments passed to the program
    if(argc != 2)
    {
    	puts("\nUsage: gmm config.txt\n");
    	puts("where config.txt is a configuration file of the form:\n");
    	puts("Utterance=loc1.mel");
    	puts("GMM file=loc1.gmm");
    	puts("Number of Gaussians=2");
    	puts("Dimension of feature vectors=36");
    	puts("IMPORTANT: LEAVE A BLANK LINE AT THE END OF CONFIGURATION FILE!!!\n");
    	return 1;
    }
	else
		loadconfig(argv[1],&nGaussians,&dim,GMMFilename,UBMFilename,utteranceFilename);

/*	puts("Configuration settings:\n");*/
/*	printf("Configuration file: %s\n",argv[1]);*/
/*	printf("Number of Gaussians in the mixture: %d\n",nGaussians);*/
/*	printf("Dimension of feature vectors: %d\n",dim);*/
/*	printf("GMM file: %s\n",GMMFilename);*/
/*	printf("UBM file: %s\n",UBMFilename);*/
/*	printf("File with utterance: %s\n\n",utteranceFilename);*/

	// Loading GMM (allocates memory for struct l=>MUST DEALLOCATE AT THE END OF THIS FUNCTION!)
	loadGMM(nGaussians,dim,&l,GMMFilename);

	// Loading UBM (allocates memory for struct u=>MUST DEALLOCATE AT THE END OF THIS FUNCTION!)
	loadGMM(nGaussians,dim,&u,UBMFilename);

    // Showing GMM in the screen	
    showgmm(l,nGaussians,dim); 
	
    // Showing UBM in the screen	
/*    showgmm(u,nGaussians,dim); */
	
    // Reading utterance to be verified
	loadUtterance(utteranceFilename,dim,&nFrames,&x);
/*
	printf("Number of frames: %d\n",nFrames);
	for (t=0;t<nFrames;t++)
	{
	    for(i=0;i<dim;i++)
	        printf("%f\t",x[t][i]);
	    puts(" ");
	}
*/

	p = aposteriori(x,dim,nFrames,l,nGaussians);	
	g = aposteriori(x,dim,nFrames,u,nGaussians);
	
	//printf("P(O|GMM)=%f\n",p);
   	// printf("P(O|UBM)=%f\n",g);
   	// printf("P(O|M)=%f\n",p-g);
	printf("%f\n",p-g);

	// Deallocating memory
	// GMM
	for (i=0;i<nGaussians;i++)
	{
	  free(l[i].m);
	  free(l[i].s);
	}
	free(l);
	// UBM
	for (i=0;i<nGaussians;i++)
	{
	  free(u[i].m);
	  free(u[i].s);
	}
	free(u);
	// utterance
	for (t=0;t<nFrames;t++)
	  free(x[t]);
	free(x);

	return 0;
}

