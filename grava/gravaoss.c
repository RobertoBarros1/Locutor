#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/soundcard.h>

#define SAMPLE_FORMAT AFMT_S16_NE 
#define CHANNELS 1

int open_audio_device 
(
	char *name, 
	int mode,
	int fs
)
{
	int tmp, fd;
	int sample_rate;
	
	if ((fd = open (name, mode, 0)) == -1)
    {
      	perror (name);
      	exit (-1);
    }

	//Setup the device. Note that it's important to set the sample format, number of channels and sample rate exactly in this order. Some devices 		depend on the order.

	//Set the sample format

  	tmp = SAMPLE_FORMAT;		/* Native 16 bits */
  	if (ioctl (fd, SNDCTL_DSP_SETFMT, &tmp) == -1)
    {
      	perror ("SNDCTL_DSP_SETFMT");
      	exit (-1);
    }

  	if (tmp != AFMT_S16_NE)
    {
      	fprintf (stderr,"The device doesn't support the 16 bit sample format.\n");
      	exit (-1);
    }

	//Set the number of channels (mono)
	tmp = CHANNELS;
  	if (ioctl (fd, SNDCTL_DSP_CHANNELS, &tmp) == -1)
    {
      	perror ("SNDCTL_DSP_CHANNELS");
      	exit (-1);
    }
  	if (tmp != 1)
    {
      	fprintf (stderr, "The device doesn't support mono mode.\n");
      	exit (-1);
    }

	//Set the sample rate
  	sample_rate = fs;
  	if (ioctl (fd, SNDCTL_DSP_SPEED, &sample_rate) == -1)
    {
      	perror ("SNDCTL_DSP_SPEED");
      	exit (-1);
    }
	//No need for error checking because we will automatically adjust the signal based on the actual sample rate. However most application must check 	the value of sample_rate and compare it to the requested rate.
	//Small differences between the rates (10% or less) are normal and the applications should usually tolerate them. However larger differences may 	cause annoying pitch problems (Mickey Mouse).

  	return fd;
}

long gravaoss 
(
	short *buffer, // stores the recorded signal
	int maxtime,  // maximun recording time
	int fs        // sampling frequency
)
{
  	short *buffer1; // temporary buffers (will be alocated for 200ms recording time)
  	int nSamples;  // number of samples in buffer
  	int i,l,k; // counters
  	int time;
  	long loops;
	int fd_in; 
  	char *name_in = "/dev/dsp";
	int bufferSize;
	long energy; // aux variable to store the "energy" of one buffer (200ms)
	long sum; // aux var to calculate the DC level of the signal
	long energias[50];
	long DCLevel;
	long aux;
	double initThreshold, endingThreshold; // energy thresholds for utterance endpoints detection 
	//long begin, end; // begining and ending frames 
	int stop; // aux variable to control the recording loops
	//short *record;
//	FILE *fp;
//	int tamanho;
	
	// Opening audio device
	fd_in = open_audio_device (name_in, O_RDONLY,fs);
	
	// Allocating temporary buffer
  	nSamples = (int)(0.2*fs); // 200ms
  	bufferSize = nSamples*sizeof(short); // each sample has 16 bits
   	buffer1 = malloc(bufferSize); 
    
    	loops = (long)(maxtime * fs / nSamples);

/*
   	printf("PERIOD_TIME = %d\n",maxtime);
   	printf("SAMPLE_RATE=%d\n",fs);
   	printf("loops=%ld\n",loops);
   	printf("nSamples=%d\n",nSamples);
	printf("bufferSize=%d\n",bufferSize);
*/
    // First 200ms always have undesired noises
    if ((l = read (fd_in, buffer1, bufferSize)) == -1)
    {
    	perror ("Audio read");
    	exit (-1);		/* Or return an error code */
	printf("Ocorreu um erro fale novamente");
    }
    
	// Getting silence statistics (200ms at the begining)
  	if ((l = read (fd_in, buffer1, bufferSize)) != -1)
  	{
  		sum=0;
  		for(i=0;i<nSamples;i++)
  			sum += buffer1[i];
  	}
  	else
    {
    	perror ("Audio read");
    	exit (-1);		/* Or return an error code */
    }
    DCLevel = (long)((float)sum/(float)nSamples);
    
    energy = 0;
	for(i=0;i<nSamples;i++)
		energy += abs(buffer1[i]-DCLevel);
    
   // printf("Silence energy: %ld\n",energy);
   // printf("DC level: %ld\n",DCLevel);
  
    initThreshold = 1.5*energy;
    endingThreshold = 1.2*energy;
    
    //printf("Init threshold: %f\n",initThreshold);
    //printf("Ending threshold: %f\n",endingThreshold);
       
    // Waiting for the utterance to start
    k=0;
	time = 0;
	stop = 0;
	do
   	{
   		// reading and filling buffer1
  		if ((l = read (fd_in, buffer1, bufferSize)) != -1)
  		{
  			energias[time]=0;
  			for(i=0;i<nSamples;i++)
  			{
  				aux = buffer1[i]-DCLevel;
  				buffer[k++] = aux;
  			    energias[time] += abs(aux);
  			}	
  		}
  		else
    	{
      		perror ("Audio read");
      		exit (-1);		/* Or return an error code */
		printf("Ocorreu um erro fale novamente");
    	}
    	if(energias[time]>initThreshold)
    	{
    		//begin = time;
    		stop = 1;
    	}
    	time++;
	} while((time<loops) && (stop==0));
	
	// Recording utterance
	stop = 0;
	do
   	{
   		// reading and filling buffer1
  		if ((l = read (fd_in, buffer1, bufferSize)) != -1)
  		{
  			energias[time]=0;
  			for(i=0;i<nSamples;i++)
  			{
  				aux = buffer1[i]-DCLevel;
  				buffer[k++] = aux;
  			    energias[time] += abs(aux);
  			}	
  		}
  		else
    	{
      		perror ("Audio read");
      		exit (-1);		// Or return an error code 
		printf("Ocorreu um erro fale novamente");
    	}
    	if(energias[time]<endingThreshold)
    	{
    		//end = time;
    		stop = 1;
    	}

    	time++;
	} while((time<loops) && (stop==0));

    // Recording the end of utterance (if any)
    while(time<loops)
   	{
   		// reading and filling buffer1
  		if ((l = read (fd_in, buffer1, bufferSize)) != -1)
  		{
  			energias[time]=0;
  			for(i=0;i<nSamples;i++)
  			{
  				aux = buffer1[i]-DCLevel;
  				buffer[k++] = aux;
  			    energias[time] += abs(aux);
  			}	
  		}
  		else
    	{
      		perror ("Audio read");
      		exit (-1);		// Or return an error code 
		printf("Ocorreu um erro fale novamente");
    	}
 
    	time++;
	} 
    
	// Saving selected portion
//	end+=2;
	//record = buffer+begin*nSamples;
	//tamanho = (end-begin)*nSamples;
	/*
	if ((fp = fopen("voice.raw", "wb"))==NULL)
    {
   	printf("Cannot open file \n");
        exit(1);
    }
    if (fwrite(record, sizeof(short), tamanho, fp) !=tamanho)
    {
    	printf("Write error occurred");
        exit(1);
	printf("Ocorreu um erro fale novamente");
    }
    fclose(fp);
*/ 

	
 	
   	//puts("Frame energies:");

   	//for (time=0;time<loops;time++)

   		//printf("Frame: %d, Energy = %ld\n",time,energias[time]);



   		
   	//printf("Begining buffer: %ld\n",begin);
    //printf("Ending buffer:s %ld\n",end);
 		
	// Freeing memory
   	free(buffer1);
   	   		
   	return k;
}
