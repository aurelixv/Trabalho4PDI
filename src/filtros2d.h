/*============================================================================*/
/* FILTRAGEM ESPACIAL                                                         */
/*----------------------------------------------------------------------------*/
/* Autor: Bogdan T. Nassu - nassu@dainf.ct.utfpr.edu.br                       */
/*============================================================================*/
/** Tipos e funções para filtragem espacial. */
/*============================================================================*/

#ifndef __FILTROS2D_H
#define __FILTROS2D_H

/*============================================================================*/

#include "imagem.h"
#include "geometria.h"

/*============================================================================*/

// Genéricos.
void filtro1D (Imagem* in, Imagem* out, float* coef, int n, int vertical);

// Suavização e realce.
void blur (Imagem* in, Imagem* out, int altura, int largura, Imagem* buffer);
void filtroGaussiano (Imagem* in, Imagem* out, float sigmax, float sigmay, Imagem* buffer);
void unsharpMasking (Imagem* in, Imagem* out, float sigma, float threshold, float mult, Imagem* buffer);
void filtroMediana8bpp (Imagem* in, Imagem* out, int altura, int largura);
void filtroMedianaBinario (Imagem* in, Imagem* out, int altura, int largura, Imagem* buffer);

// Morfologia.
void maxLocal (Imagem* in, Imagem* out, int altura, int largura, Imagem* buffer);
void minLocal (Imagem* in, Imagem* out, int altura, int largura, Imagem* buffer);
Imagem* criaKernelCircular (int largura);
void dilata (Imagem* in, Imagem* kernel, Coordenada centro, Imagem* out);
void erode (Imagem* in, Imagem* kernel, Coordenada centro, Imagem* out);
void abertura (Imagem* in, Imagem* kernel, Coordenada centro, Imagem* out, Imagem* buffer);
void fechamento (Imagem* in, Imagem* kernel, Coordenada centro, Imagem* out, Imagem* buffer);

/*============================================================================*/
#endif /* __FILTROS2D_H */
