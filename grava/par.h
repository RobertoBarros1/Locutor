#ifndef PAR_H_
#define PAR_H_

#define ORDEM_MEL 12 // ordem dos parametros mel-cepstrais (tb delta e delta-delta)

// Funcao que calcula os parametros de um sinal de entrada 'x'.
// Calcula os coeficientes ate ordem 'ordem' e armazena os resultados em 'par1'.
void calcpar
(
    short *x, // contains the utterance to be recognized
    int tamanho, // number of samples of x
    short bps, // bits por amostra
    int fs, // frequencia de amostragem do sinal
    int ordem,  // ordem dos vetores de cada um dos parametros
    int nQuadrosAdjacentes, // numero de quadros adjacentes a serem considerados no calculo de parameros delta
  	int* Nwindow1,      // numero de quadros com o qual foi analisado o sinal
    double*** par1    // sinal parametrizado
);
	
// Funcao que calcula parametros delta
void calcDelta
(
	  int delta, // numero de janelas adjacentes a serem utilizadas no calculo dos parametros delta
	  int n_quadros, // numero de quadros do sinal
	  int ordem, // ordem os vetores de parametros
	  double **param, // parametros dos quais se deseja calcular os parametros delta
	  double **par_delta // armazena os parametros delta
);

// Calcula a energia de um frame
double calcEnergia
(
    double *xw,  // sinal a ser analisado
    int Lwindow // numero de amostras do sinal
);

// Funcao que calcula parametros delta e delta-delta p/ os parametros log energia normalizada
void CalculaDeltaEnergia
(
    double **energia, // vetor com os parametros log-energia, delta e delta-delta
    int n_quadros, // numero de quadros na locucao
    int delta // janelas a esquerda e a direita a serem consideradas para o calculo dos parametros delta
);

//---------------------------------------------------------------------------
// Calculo da FFT de N pontos do vetor xw[]. Usa-se o algoritmo proposto no
// Prob 6.4, pagina 333, do livro "Digital Signal Processing" de Oppenheim &
// Schaffer. Nomenclatura usada no livro e aqui: LE= n1, LE1= n2, NV2= n3.
// Retorna o modulo da FFT em mod_fft.
void fft
(
  double *xw, // janela de analise
  int Lwindow, // tamanho da janela de analise 20 ms
  int fs, // frequencia de amostragem do sinal
  int M, // M=9 ==> FFT de 512 pontos; M=10 ==> FFT de 1024 pontos
  int N, // numero de pontos da FFT (N=2**M)
  double *mod_fft // modulo da FFT
);

// Calculo dos paramentros LPC, através do algoritmo de Durbin.
int calcLPC
(
  double *xw, // amostras do sinal
  int Lwindow, // numero de amostras de xw
  int ordem,   // ordem dos parametros
  double *lpc // ponteiro onde serao armazenados os parametros calculados
);

// Função para cálculo da função de autocorrelação
void autoCorrelate
(
  double *xw, // amostras do sinal
  double *r, // vetor de autocorrelacao
  int order, // ordem da analise lpc
  int Lwindow // numero de amostras de xw
);

// Normalize r's to prevent round off error
int normalize_corr
(
  double *r, // vetor de autocorrelacao
  int order // ordem da analise lpc
);

//--------------------------------------------------------------------------+
//  Funcao para calculo dos coeficientes mel-cepstrais
//  Os coef mel-cepstrais sao obtidos segundo o algoritmo de Mermelstein;
//  os passos a seguir sao:
//
//  - Calculo da FFT das am's pertencentes a janela de analise.
//  - Calculo do quadrado do modulo da FFT (equivale a energia).
//  - Filtragem do modulo acima pelo banco de filtros na escala mel,
//    obtendo-se a energia por filtro.
//  - Calculo do log da energia por filtro.
//  - Calculo da transformada inversa, obtendo-se os coef's mel-cepstrais
//    (esto e' implementado calculando-se a DCT: discrete cosine transform)
//
//  OBS: Lwindow: num de ams/janela; xw: am's janeladas
// +------------------------------------------------------------------------+
void calcMel
(
  int fs,          // frequencia de amostragem do sinal
  double *mod_fft, // modulo ao quadrado da FFT (energia)
  int N,           // numero de pontos da FFT
  int ordem,       // numero de parametros mel a serem calculados
  double *Mel_ceps // ponteiro onde serao armazenados os parametros calculados
);

// Funcao para calculo de perfis de energia
void calcPerfilEnergia
(
  int fs,          // frequencia de amostragem do sinal
  double *mod_fft, // modulo da FFT do sinal
  int N,           // numero de pontos da FFT
  int nPerfis,     // numero de perfis desejado (ordem do parametro)
  double *Perfis   // retorna os perfis de energia
);

// Dados dois pontos (x1,y1) e (x2,y2), calcula o valor de x, que passa pela reta
// dada por estes pontos, na posicao intermediaria y.
double InterpLinear
(
  double x1, // componente x do ponto 1
  double y1, // componente y do ponto 1
  double x2, // componente x do ponto 2
  double y2, // componente y do ponto 2
  double y // componente y do ponto intermediario
);

// Funcao que remove a componente DC de um sinal de voz
void removeDC
(
  int Nam,
  double *x
);

// Implementa filtro de pre-enfase de primeira ordem
void preEnfase
(
  double CP, // coeficiente de pre-enfase
  int tamanho, // numero de amostras de x
  double *x // sinal a ser pre-enfatizado
);

// Aplica uma janela de Hamming ao sinal
void hamming
(
  int tamanho, // numero de amostras do sinal
  double *x // sinal a ser janelado
);

#endif /*PAR_H_*/
