#include <stdlib.h>

#include "par.h"

// Funcao que calcula os parametros de um sinal de entrada 'x'.
// Calcula os coeficientes ate ordem 'ordem' e armazena os resultados em 'par1'.
void calcpar
(
    short *buffer, // contains the utterance to be recognized
    int Nam, // number of samples of x
    short bps, // bits por amostra
    int fs, // frequencia de amostragem do sinal
    int ordem,  // ordem dos vetores de cada um dos parametros
    int nQuadrosAdjacentes, // numero de quadros adjacentes a serem considerados no calculo de parameros delta
    int* Nwindow1,      // numero de quadros com o qual foi analisado o sinal
    double*** par1    // sinal parametrizado
)
{
  	// Declaracao de variaveis locais

  	double CP=0.95; // coeficiente de pre-enfase
  	int i,j,k; // contadores
  	int Lframe; // tamanho de quadro de analise 10 ms
  	int Lwindow; // tamanho da janela de analise 20 ms
  	int M; // M=9 ==> FFT de 512 pontos; M=10 ==> FFT de 1024 pontos
  	double *mod_fft=NULL; // modulo da FFT
  	int N; // numero de pontos da FFT (N=2**M)
  	int Nwindow; //numero de quadros com o qual foi analisado o sinal
  	double **par=NULL; // sinal parametrizado
  	double *x2=NULL; // sinal armazenado em formato double
  	double *xw=NULL; // ams da janela de trabalho (max 60 mseg)
  	double **maux=NULL,**daux=NULL,**ddaux=NULL; // var aux p/ armazenar as componentes do vetor de parametros mdd (mel, delta e delta-delta)
	
  	// Determinando tamanho da janela, quadro de analise
  	Lframe = fs / 100;
  	Lwindow = 2*Lframe;

  	// Definindo numero de pontos da FFT
  	switch(fs)
  	{
    	case 8000:
      		M=9;
      		break;
    	case 11025:
      		M=9;
      		break;
    	default:
      		M=10;
  	}
  	N = 1.0;
  	for (i=0;i<M;i++)
    	N *= 2; // N = 2^M

  	// Determina o numero total de janelas.
  	Nwindow = (int)((Nam-(Lframe)-1) / (Lframe));
  	//if((Nam%Lframe)!=0)
    //	Nwindow++;

  	// Alocando memoria
	x2 = malloc(sizeof(double)*Nam);
	xw = malloc(sizeof(double)*Lwindow);

	par = malloc(sizeof(double *)*Nwindow);
	for (j=0;j<Nwindow;j++)
		par[j] = malloc(sizeof(double)*ordem);

	maux = malloc(sizeof(double *)*Nwindow);
	daux = malloc(sizeof(double *)*Nwindow);
	ddaux = malloc(sizeof(double *)*Nwindow);
	for (i=0;i<Nwindow;i++)
	{
		maux[i] = malloc(sizeof(double)*ORDEM_MEL);
		daux[i] = malloc(sizeof(double)*ORDEM_MEL);
		ddaux[i] = malloc(sizeof(double)*ORDEM_MEL);
	}

	mod_fft = malloc(sizeof(double)*N);

  	// Armazenando sinal em formato double
  	for (i=0;i<Nam;i++)
    	x2[i] = (double)buffer[i];

  	// Retirando nivel DC do sinal
  	removeDC(Nam,x2);

  	// Filtragem de pre-enfase
  	preEnfase(CP,Nam,x2);

  //----------------------------------------------------------------------------
  	// Calculando parametros
  	for(k=0;k<Nwindow;k++)
  	{
    	// Selecionando trecho a ser analisado
    	for(i=0;i<Lwindow;i++)
      		xw[i] = x2[k*Lframe+i];

    	// Janelamento
    	hamming(Lwindow,xw);

    	// Calculando FFT
    	fft(xw,Lwindow,fs,M,N,mod_fft);

    	// Calculando parametros mel cepstrais
   		calcMel(fs,mod_fft,N,ORDEM_MEL,maux[k]);
   		for (i=0;i<ORDEM_MEL;i++)
     		par[k][i] = maux[k][i];
  	}

  //----------------------------------------------------------------------------
  // Calculando parametros delta mel
    calcDelta(nQuadrosAdjacentes,Nwindow,ORDEM_MEL,maux,daux);
    for (k=0;k<Nwindow;k++)
      for (i=0;i<ORDEM_MEL;i++)
        par[k][i+ORDEM_MEL] = daux[k][i];

  // Calculando parametros delta-delta mel
    calcDelta(nQuadrosAdjacentes,Nwindow,ORDEM_MEL,daux,ddaux);
    for (k=0;k<Nwindow;k++)
      for (i=0;i<ORDEM_MEL;i++)
        par[k][i+2*ORDEM_MEL] = ddaux[k][i];

  // Desalocando ponteiros
  //free(x1);
  free(x2);
  free(xw);

  for (i=0;i<Nwindow;i++)
  {
      free(maux[i]);
      free(daux[i]);
      free(ddaux[i]);
  }
  free(maux);
  free(daux);
  free(ddaux);

  free(mod_fft);

  //free(MediaMel);
  /*
  // Salvando parametros em arquivo
  arquivo = fopen("c:\\users\\iog\\continuo\\comum\\perfil.dat","wb");
  for (i=0;i<n_par;i++)
    for (j=0;j<Nwindow;j++)
      for (k=0;k<ordem[i];k++)
        fwrite(&par[i][j][k],sizeof(double),1,arquivo);
  fclose(arquivo);
  */

  // Valores de retorno da funcao
  *par1 = par;
  *Nwindow1 = Nwindow;
}
