/*============================================================================*/
/* MANIPULAÇÃO DE CORES                                                       */
/*----------------------------------------------------------------------------*/
/* Autor: Bogdan T. Nassu - nassu@dainf.ct.utfpr.edu.br                       */
/*============================================================================*/
/** Tipos e funções para manipulação de cores. */
/*============================================================================*/

#ifndef __CORES_H
#define __CORES_H

/*============================================================================*/

#include "imagem.h"

/*============================================================================*/
/* Uma cor. */

typedef struct
{
    float canais [3]; // Valores para os 3 canais (R,G,B). Em imagens em escala de cinza, usa apenas o primeiro valor.
} Cor;

Cor criaCor (float r, float g, float b);

/*============================================================================*/
/* Conversões de cores. */

void RGBParaCinza (Imagem* in, Imagem* out);
void cinzaParaRGB (Imagem* in, Imagem* out);
void RGBParaHSL (Imagem* in, Imagem* out);
void HSLParaRGB (Imagem* in, Imagem* out);

/*============================================================================*/
/* Transformações de cores. */

void inverte (Imagem* in, Imagem* out);
void ajustaBrilhoEContraste (Imagem* in, Imagem* out, float brilho, float contraste);
void ajustaGama  (Imagem* in, Imagem* out, float gama);
void ajustaHSL (Imagem* in, Imagem* out, float matiz, float saturacao, float luminancia);

/*============================================================================*/
#endif /* __CORES_H */
