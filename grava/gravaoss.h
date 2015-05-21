#ifndef GRAVAOSS_H_
#define GRAVAOSS_H_

int open_audio_device 
(
	char *name, 
	int mode,
	int fs
);

long gravaoss 
(
	short *buffer, // stores the recorded signal
	int maxtime,  // maximun recording time
	int fs        // sampling frequency
);

#endif /*GRAVAOSS_H_*/
