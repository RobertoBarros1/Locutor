#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//calcpar
#include "gravaoss.h"
#include "wav.h"
#include "par.h"
//gmmadapt
#include "structs.h"
#include "showgmm.h"
#include "b.h"
#include "mixture.h"
#include "update_p.h"
#include "aposteriori.h"
#include "update_m.h"
#include "update_s.h"
#include "normrnd.h"
#include "testgmm.h"
#include "loadconfig.h"
#include "loadUtterances.h"
#include "saveGMM.h"
#include "lbg.h"
#include "loadGMM.h"


int main (int argc, char *argv[])
{
/*************************calcpar e gravaoss***********************************************************/
	short *buffer;
	FILE *fp;
	long tamanhoOss;
	int maxtime=2; // maximun recording time (in seconds)
	int fs=11025;
 	//short *y=NULL; // contains the utterance to be recognized
    	short bps=16; // bits por amostra
    	//int Samples; // size of audio file 
    	//int tamanho;
    	int dim=36;  // ordem dos vetores de cada um dos parametros
    	int d=1; // numero de quadros adjacentes a serem considerados no calculo de parameros delta
  	int nWindows=0;      // numero de quadros com o qual foi analisado o sinal
    	double** par=NULL;    // sinal parametrizado
    	//FILE *arquivo;	
    //	int i,j; // counters
    	//float aux;

/*********************************************************************************************Speakerid*/

	struct mixture *l; // stores the elements of the GMM
    	int initializationMode = 0; //0=Segmental K-Means, 1=load a pre-trained model as initialization
    	//char preTrained[512]; // pre-trained GMM loaded as initilization of current training session
	int nGaussians = 8; // number of gaussians in the mixture
	//int nFrames;    // number of frames in x
	//int dim;        // dimension of feature vectors
	int i,j,t;            // counters
	//double **x; // sequence of observation vectors
	double *p; // aux var to store the mixture coefficients during updating p[nGaussians]
	double **m; // aux var to store the Gaussian means during updating m[nGaussians][dim]
	double **s; // aux var to store the Gaussian variances during updating s[nGaussians][dim]
	int epoch;  // counter
	double dist,p_old, p_new; // aux variables for convergence verification
	//char GMMFilename[512]; // file that will store the trained GMM
	//char trainingUtterances[512]; // file with training utterances listing
	double **codebook; // aux var for mean initialization
	time_t t_inic,t_final; // instantes inicial e final
	//	int decorrido;

/***********************************************************Verificação********************************************/
	struct mixture *q=NULL; // stores the elements of the GMM
	struct mixture *u=NULL; // stores the elements of the UBM
	//int nGaussians; // number of gaussians in the mixture
	//int nFrames;    // number of frames in x
	//int dim;        // dimension of feature vectors
	//int i,t;        // counters
	//double **o; // sequence of observation vectors
    	double gmm; // P(O|M) for the GMM
    	double ubm; // P(O|M) for the UBM
	char GMMFilename[512]; // file that stores the GMM
	char UBMFilename[512]; // file that stores the UBM
	char utteranceFilename[512]; // file with utterance to be verified


/*******************************************************************************************/
	// Gravando locução a ser reconhecida
	buffer=(short *)malloc(maxtime*sizeof(short)*fs); // maxtime*2bytes*fs
	
	tamanhoOss = gravaoss(buffer,maxtime,fs);
//	printf("tamanho total = %ld\n",tamanhoOss);
	
    // Saving recorded utterance in file 
    	if ((fp = fopen("sound.raw", "wb"))==NULL)
    	{
    		printf("Cannot open file \n");
        	exit(1);
    	}
    	if (fwrite(buffer, sizeof(short), tamanhoOss, fp) != tamanhoOss)
    	{
    		printf("Write error occurred");
        	exit(1);
		printf("Ocorreu um erro fale novamente");
    	}
    	fclose(fp); 

    	

    	//arquivo = fopen("sound.raw","rb");
    	//fseek(arquivo, 0, SEEK_END); // seek to end of file
    	//tamanho = ftell(arquivo); // get current file pointer
    	//fseek(arquivo, 0, SEEK_SET); // seek back to beginning of file

    //	y = malloc(sizeof(char)*tamanho);
    //	fread(y,sizeof(char),tamanho,arquivo);
    //	fclose(arquivo);

    	//Samples = tamanhoOss/sizeof(short);
    
        
    	// Calculating acoustic parameters
    	calcpar(buffer,tamanhoOss,bps,fs,dim,d,&nWindows,&par);

	

/*    	printf("Number of analysis windows: %d\n",nWindows);   */
  

  /*
    // Saving parameters in output file
    	arquivo = fopen("roberto.mfc","wb");
         
    	for (i=0;i<nWindows;i++) 
        	for (j=0;j<dim;j++)
        	{	
           		aux = (float)par[i][j];
           		fwrite(&aux,sizeof(float),1,arquivo);
        	}
    	fclose(arquivo);
    */
    // Releasing allocated memory
    //free(y);
    //for (i=0;i<nWindows;i++)
       // free(par[i]);
    //free(par);
    



/***************************************************************************************Speakerid*/
	
	
	
    // Reading arguments passed to the program
    
	// Reading training utterances
	//loadUtterances(trainingUtterances,dim,&nFrames,&x);
	
	//printf("Number of frames: %d\n",nFrames);
	
//	for (t=0;t<nFrames;t++)
//	{
//	    for(i=0;i<dim;i++)
//	        printf("%f\t",x[t][i]);
//	    puts(" ");
//	}
/*	
	for (t=0;t<nFrames/2;t++)
	{
		x[t][0] = normrnd(1,1);
		x[t][1] = normrnd(3,1);
	}	
	for (t=nFrames/2;t<nFrames;t++)
	{
		x[t][0] = normrnd(5,1);
		x[t][1] = normrnd(7,1);
	}
*/	

	// Allocating memory
	p = malloc(sizeof(double)*nGaussians);
	m = malloc(sizeof(double *)*nGaussians);
	for (i=0;i<nGaussians;i++)
		m[i] = malloc(sizeof(double)*dim);
	s = malloc(sizeof(double *)*nGaussians);
	for (i=0;i<nGaussians;i++)
		s[i] = malloc(sizeof(double)*dim);
	codebook = malloc(sizeof(double)*nGaussians);
	for (i=0;i<nGaussians;i++)
		codebook[i] = malloc(sizeof(double)*dim);

/*
	x = malloc(sizeof(double *)*nFrames);
	for (t=0;t<nFrames;t++)
	  x[t] = malloc(sizeof(double)*dim);
*/	
    // Initializing GMMs
    
    if (initializationMode==0)
    {
		// Allocating memory for GMMs
		l = malloc(sizeof(struct mixture)*nGaussians);
		for (i=0;i<nGaussians;i++)
		{
		  l[i].m = malloc(sizeof(double)*dim);
		  l[i].s = malloc(sizeof(double)*dim);
		}

		// Initializing gaussian weights and variances
		for (i=0;i<nGaussians;i++)
		{	
			l[i].p = 1.0/nGaussians;
			for (j=0;j<dim;j++)
			{
				//l[i].m[j] = normrnd(1,2);
				//l[i].m[j] = i+j;
				l[i].s[j] = 1.0;
			}
		}
		
		// Initializing means via Segmental K-Means
		//puts("Initializing means via Segmental K-Means");
		lbg(&codebook,nGaussians,nWindows,dim,par);
		for (i=0;i<nGaussians;i++)
			for (j=0;j<dim;j++)
				l[i].m[j] = codebook[i][j];
		
		// Saving trained model
		saveGMM(nGaussians,dim,l);
	}
	else
	//{
		// Loading GMM (allocates memory for struct l=>MUST DEALLOCATE AT THE END OF THIS FUNCTION!)
		//loadGMM(nGaussians,dim,&l);
		//showgmm(l,nGaussians,dim); 
	//}
/*
	for (j=0;j<dim;j++)
	{
		for (i=0;i<nGaussians;i++)
			printf("%f\t",codebook[i][j]);
		puts(" ");
	}		
*/
	// Training models
	puts("Training models ...");
	p_old = -INF;
	dist = 1.0;
	epoch = 0;
	while(dist > 1e-5)
	{
		// Iniciando contagem de tempo de processamento
        time(&t_inic);
		
	    // Updating mixture coefficients
	    update_p(par,dim,nWindows,l,nGaussians,p);	
	    
		// Updating gaussian means
	    update_m(par,dim,nWindows,l,nGaussians,&m);

	    // Updating gaussian variances
	    update_s(par,dim,nWindows,l,nGaussians,m,&s);
	    
	    // Copying updated values for the model
	    for (i=0;i<nGaussians;i++)
	    {
	    	l[i].p = p[i];
	    	for (j=0;j<dim;j++)
	    	{
	    		l[i].m[j] = m[i][j];
	    		l[i].s[j] = s[i][j];
	    	}
	    }
	    
	    // Verifying convergence
	    p_new = testgmm(par,dim,nWindows,l,nGaussians);
	    dist = -(p_new-p_old)/p_new;
	    
		// Showing results
		/*
		printf("Results after %d training epochs.\n",epoch+1);
		printf("P(X|M) = %f\n",p_new);
		printf("distortion: %f\n\n",dist);
		*/
		// Parando cronometragem
    	time(&t_final);

    	// Calculando tempo decorrido
    	//decorrido = (int) difftime(t_final,t_inic);
		
		//printf("Tempo: %d segundos\n",decorrido);
		
		// Updating p_old for the next training epoch
		p_old = p_new;
		epoch++;		
		//showgmm(l,nGaussians,dim); 

		// Saving trained model
		saveGMM(nGaussians,dim,l);
	}

    //showgmm(l,nGaussians,dim); 
    
	// Deallocating memory
	for (i=0;i<nGaussians;i++)
	{
	  free(l[i].m);
	  free(l[i].s);
	}
	free(l);
	//for (t=0;t<nWindows;t++)
	//  free(par[t]);
	//free(par);
	for (i=0;i<nGaussians;i++)
		free(m[i]);
	free(m);
	for (i=0;i<nGaussians;i++)
		free(s[i]);
	free(s);
	for (i=0;i<nGaussians;i++)
		free(codebook[i]);
	free(codebook);

   	free(buffer);


/**********************************************************************************/

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
	loadGMM(nGaussians,dim,&q,GMMFilename);

	// Loading UBM (allocates memory for struct u=>MUST DEALLOCATE AT THE END OF THIS FUNCTION!)
	loadGMM(nGaussians,dim,&u,UBMFilename);

    // Showing GMM in the screen	
    
	/*showgmm(q,nGaussians,dim);*/ 
	
    // Showing UBM in the screen	
/*    showgmm(u,nGaussians,dim); */
	
    // Reading utterance to be verified
	//loadUtterance(utteranceFilename,36,&nFrames,&x);
/*
	printf("Number of frames: %d\n",nFrames);
	for (t=0;t<nFrames;t++)
	{
	    for(i=0;i<dim;i++)
	        printf("%f\t",x[t][i]);
	    puts(" ");
	}
*/

	gmm = aposteriori(par,dim,nWindows,q,nGaussians);	
	ubm = aposteriori(par,dim,nWindows,u,nGaussians);
	
	//printf("P(O|GMM)=%f\n",p);
   	// printf("P(O|UBM)=%f\n",g);
   	// printf("P(O|M)=%f\n",p-g);
	printf("%f\n",gmm-ubm);

	if(gmm-ubm >= 490 ){
		printf("entrou!!!");
	}

	// Deallocating memory
	// GMM
	for (i=0;i<nGaussians;i++)
	{
	  free(q[i].m);
	  free(q[i].s);
	}
	free(q);
	// UBM
	for (i=0;i<nGaussians;i++)
	{
	  free(u[i].m);
	  free(u[i].s);
	}
	free(u);
	// utterance
	for (t=0;t<nWindows;t++)
	  free(par[t]);
	
	free(par);
	free(p);

    	return 0;
}







/*if(argc != 2)
    {
    	puts("\nUsage: gmm config.txt\n");
    	puts("where config.txt is a configuration file of the form:\n");
		puts("Inicialization=SegmentalKMeans");
		puts("or");
		puts("Inicialization=PreTrainedGMM");
		puts("Pre-trained GMM=gmm.dat");
    	puts("Number of Gaussians=2");
    	puts("Dimension of feature vectors=36");
    	puts("Output filename=gmm1.dat");
    	puts("Training utterances=names.txt\n");
    	puts("IMPORTANT: LEAVE A BLANK LINE AT THE END OF CONFIGURATION FILE!!!\n");
    	return 1;
    }
	else
		loadconfig(argv[1],&initializationMode,preTrained,&nGaussians,&dim,GMMFilename,trainingUtterances);



	puts("Configuration settings:\n");
	if (initializationMode==0)
		puts("Initialization Mode: Segmental K-Means");
    	else
	{
		puts("Initialization Mode: pre-trained GMM");
    	printf("File with initial GMM: %s\n",preTrained);
	}
	printf("Configuration file: %s\n",argv[1]);
	printf("Number of Gaussians in the mixture: %d\n",nGaussians);
	printf("Dimension of feature vectors: %d\n",dim);
	printf("Output file: %s\n",GMMFilename);
	printf("File with training utterances: %s\n\n",trainingUtterances);
    */
