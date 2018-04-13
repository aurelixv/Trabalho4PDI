/*============================================================================*/
/* TIPOS E FUNÇÕES BÁSICOS                                                    */
/*----------------------------------------------------------------------------*/
/* Autor: Bogdan T. Nassu - nassu@dainf.ct.utfpr.edu.br                       */
/*============================================================================*/
/** Tipos e funções básicos, úteis para diversos problemas envolvendo
 * manipulação de imagens. */
/*============================================================================*/

#ifndef __BASE_H
#define __BASE_H

/*============================================================================*/

#include "imagem.h"

/* O básico do básico... */
#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a>b)?a:b)
unsigned char float2uchar (float x);

void soma (Imagem* in1, Imagem* in2, float mul1, float mul2, Imagem* out);

/* Normalização */
void normaliza (Imagem* in, Imagem* out, float min, float max);
void normalizaSemExtremos8bpp (Imagem* in, Imagem* out, float min, float max, float descartados);
void normLocalSimples (Imagem* in, Imagem* out, float min, float max, int largura);

/* Histogramas */
void criaHistograma8bpp1c (Imagem* in, int canal, int histograma [256]);
void criaHistograma8bpp1cNorm (Imagem* in, int canal, float histograma [256]);

/*============================================================================*/
#endif /* __BASE_H */
