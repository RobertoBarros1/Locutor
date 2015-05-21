//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------------------------
// Estrutura que armazena o cabecalho de arquivo .wav
struct soundhdr {
char riff[4]; /* "RIFF" */
int flength; /* ChunkSize in bytes */
char wave[4]; /* "WAVE" */
char fmt[4]; /* "fmt " */
int Subchunk1Size; /* in bytes (generally 16) */
short AudioFormat; /* 1=PCM, 257=Mu-Law, 258=A-Law, 259=ADPCM */
short num_chans; /* 1=mono, 2=stereo */
int srate; /* Sampling rate in samples per second */
int bytes_per_sec; /* bytes per second */
short bytes_per_samp; /* 2=16-bit mono, 4=16-bit stereo */
short bits_per_samp; /* Number of bits per sample */
char data[4]; /* "data" */
int dlength; /* data length in bytes (filelength - 44) */
};

//---------------------------------------------------------------------------
// Funcao que abre um arquivo wav de 16 bits e devolve um ponteiro contendo
// os dados, bem como o numero de amostras
void leWav
(
  short *bps1, // numero de bytes por amostra
  int *fs1, // frequencia de amostragem
  char *nome_arquivo, // nome do arquivo a ser lido
  int *nSamples, // number of samples
  short **x1 // samples of the audio file
)
{
  FILE *arquivo; // handle para leitura do arquivo wav
  short bps; // numero de bytes por amostra
  struct soundhdr cabecalho; // cabecalho do arquivo wav
  int fs; // frequencia de amostragem
  int tamanho; // numero de amostras do sinal
  short *x; // buffer onde sera armazenado o sinal
  //int nLidos;
  //int tam;
	
//    puts("Rodando leWav");
    
  // Abrindo arquivo
	arquivo = fopen(nome_arquivo,"rb");
	
	if (arquivo == NULL)
	{
		printf("Error opening file %s.\n",nome_arquivo);
		exit(1);
	}

  // Lendo tamanho do arquivo (sem o cabecalho) e alocando vetor de dados
  fseek (arquivo,0,SEEK_END);
  tamanho = ftell(arquivo);
  tamanho -= 44;
  tamanho /= sizeof(short);
  x = malloc(sizeof(short)*tamanho);

  // Posicionando ponteiro no inicio o cabecalho
  rewind(arquivo);

  // Lendo cabecalho
	//nLidos = fread(&cabecalho,sizeof(struct soundhdr),1,arquivo);
	fread(&cabecalho,sizeof(struct soundhdr),1,arquivo);
    //tam = sizeof(struct soundhdr);
  
  // Informacoes sobre frequencia de amostragem e no. de bytes por amostra
  bps = cabecalho.bytes_per_samp;
  fs = cabecalho.srate;
	    
  // Posicionando ponteiro no inicio dos dados
	fseek(arquivo,44,SEEK_SET);

  // Lendo dados
	//nLidos = fread(x,sizeof(short),tamanho,arquivo);
  fread(x,sizeof(short),tamanho,arquivo);
    
  // Fechando handle do arquivo
  fclose(arquivo);

//    puts("Inside");
//    printf("tam = %d\n",tam);
//    printf("Arquivo: %s\n",nome_arquivo);
//    printf("Sampling frequency: %d\n",fs);
//    printf("Bytes per sample: %d\n",bps);
//    printf("nSamples = %d\n",tamanho);  
//    printf("sizeof(char) = %d\n",sizeof(char));
//    printf("sizeof(short) = %d\n",sizeof(short));
//    printf("sizeof(int) = %d\n",sizeof(int));
//    printf("sizeof(long) = %d\n",sizeof(long));
//    printf("sizeof(soundhdr) = %d\n",sizeof(struct soundhdr));
    
  // Valores de retorno da funcao
  *bps1 = bps;
  *fs1 = fs;
  *nSamples = tamanho;
  *x1 = x;

}
