// Funcao que calcula parametros delta
void calcDelta
(
  int delta, // numero de janelas adjacentes a serem utilizadas no calculo dos parametros delta
  int n_quadros, // numero de quadros do sinal
  int ordem, // ordem os vetores de parametros
  double **param, // parametros dos quais se deseja calcular os parametros delta
  double **par_delta // armazena os parametros delta
)
{
  int register i,j,k; // contadores

  for (i=0;i<n_quadros;i++)
    for (j=0;j<ordem;j++)
      par_delta[i][j]=0.0;

  // Calculando parametros delta
  for (i=0;i<n_quadros;i++)
  {
    for (j=-delta;j<=delta;j++)
      if (((i+j)>=0) && ((i+j)<n_quadros))
        for (k=0;k<ordem;k++)
          par_delta[i][k] += -(double)j*param[i+j][k];
  }
  for (i=0;i<n_quadros;i++)
    for (j=0;j<ordem;j++)
      par_delta[i][j] /= (2.0*(double)delta+1.0);

}

