// Coomputes a dim-variate Gaussian function
#include <math.h>
#include "structs.h"

// Funcao que implementa uma fdp gaussiana multidimensional
double b
(
  double *x,      // vetor de parametros
  double *media, // vetor com as medias
  double *var,   // vetor com as variancias
  int ordem     // ordem do vetor de parametros
)
{
  // Declaracao das variaveis locais
  double aux=0.0,aux1,aux2 = 0.0; // variaveis auxiliares
  double det; // determinante da matriz de covariancia
  double dif; // var aux p/ o calculo da gaussiana
  int i; // contador
  double prob=0.0; // probabilidade do vetor dada a distribuicao

  // (2*pi)^(ordem/2)
  aux1 = 2.0*PI;
  aux2 = ordem / 2.0;
  aux1 = pow(aux1,aux2);
  //aux1 = exp(aux2*log(aux1));
  
  // Calculando determinante da matriz de covariancia
  det = 1.0;
  for (i=0;i<ordem;i++)
    det *= var[i];

  if (det != 0)
  {
    aux2 = fabs(det);
    aux2 = pow(aux2,0.5);

    for (i=0;i<ordem;i++)
    {
      dif = x[i] - media[i];
      aux += (dif*dif)/var[i];
    }
    aux *= (-0.5);
    aux = exp(aux);

    prob = aux/(aux1*aux2);
  }

  return(prob);

}
