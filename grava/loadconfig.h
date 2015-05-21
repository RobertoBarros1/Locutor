#ifndef LOADCONFIG_H_
#define LOADCONFIG_H_

int loadconfig
(
  char *configFile,
  int *nGaussians,
  int *dim,
  char *GMMFilename,
  char *UBMFilename,
  char *utteranceFilename
);

#endif /*LOADCONFIG_H_*/
