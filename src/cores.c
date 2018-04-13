/*============================================================================*/
/* MANIPULAÇÃO DE CORES                                                       */
/*----------------------------------------------------------------------------*/
/* Autor: Bogdan T. Nassu - nassu@dainf.ct.utfpr.edu.br                       */
/*============================================================================*/
/** Tipos e funções para manipulação de cores. */
/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "base.h"
#include "cores.h"

/*============================================================================*/
/* TIPO Cor                                                                   */
/*============================================================================*/
/** Apenas uma função útil para "criar" uma instância do tipo Cor.
 *
 * Parâmetros: float r: valor do canal R.
 *             float g: valor do canal G.
 *             float b: valor do canal B.
 *
 * Valor de retorno: a Cor criada. */

Cor criaCor (float r, float g, float b)
{
    Cor c;
    c.canais [0] = r;
    c.canais [1] = g;
    c.canais [2] = b;
    return (c);
}

/*============================================================================*/
/* CONVERSÕES DE CORES                                                        */
/*============================================================================*/
/** Converte uma imagem de RGB para escala de cinza.
 *
 * Parâmetros: Imagem* in: imagem de entrada de 3 canais.
 *             Imagem* out: imagem de saída de 1 canal, com o mesmo tamanho.
 *
 * Valor de retorno: nenhum. */

void RGBParaCinza (Imagem* in, Imagem* out)
{
    if (in->n_canais != 3)
    {
        printf ("ERRO: RGBParaCinza: a imagem de origem precisa ter 3 canais.\n");
        exit (1);
    }

    if (out->n_canais != 1)
    {
        printf ("ERRO: RGBParaCinza: a imagem de destino precisa ter 1 canal.\n");
        exit (1);
    }

    if (in->largura != out->largura || in->altura != out->altura)
    {
        printf ("ERRO: RGBParaCinza: as imagens precisam ter o mesmo tamanho.\n");
        exit (1);
    }

    /* Percorre a imagem e converte. Usamos aqui os mesmos fatores de conversão
       do OpenCV, o que mantém certas propriedades de percepção (i.e. não são
	   parâmetros "mágicos"). */
    int i, j;
	for (i = 0; i < in->altura; i++)
        for (j = 0; j < in->largura; j++)
            out->dados [0][i][j] = in->dados [0][i][j] * 0.299f + in->dados [1][i][j] * 0.587f + in->dados [2][i][j] * 0.114f;
}

/*----------------------------------------------------------------------------*/
/** Converte uma imagem de escala de cinza para RGB.
 *
 * Parâmetros: Imagem* in: imagem de entrada de 1 canal.
 *             Imagem* out: imagem de saída de 3 canais, com o mesmo tamanho.
 *
 * Valor de retorno: nenhum. */

void cinzaParaRGB (Imagem* in, Imagem* out)
{
    if (in->n_canais != 1)
    {
        printf ("ERRO: cinzaParaRGB: a imagem de origem precisa ter 1 canal.\n");
        exit (1);
    }

    if (out->n_canais != 3)
    {
        printf ("ERRO: cinzaParaRGB: a imagem de destino precisa ter 3 canais.\n");
        exit (1);
    }

    if (in->largura != out->largura || in->altura != out->altura)
    {
        printf ("ERRO: cinzaParaRGB: as imagens precisam ter o mesmo tamanho.\n");
        exit (1);
    }

    /* Percorre a imagem e converte. Simplesmente copia 3 vezes cada valor. */
	int i, j, k;
    for (i = 0; i < 3; i++)
        for (j = 0; j < in->altura; j++)
            for (k = 0; k < in->largura; k++)
                out->dados [i][j][k] = in->dados [0][j][k];
}

/*----------------------------------------------------------------------------*/
/** Conversão RGB -> HSL. Simplesmente segui as fórmulas.
 *
 * Parâmetros: Imagem* in: imagem de entrada.
 *             Imagem* out: imagem de saída. Deve ter o mesmo tamanho da
 *               imagem de entrada.
 *
 * Valor de retorno: nenhum */

void RGBParaHSL (Imagem* in, Imagem* out)
{
    if (in->n_canais != 3 || out->n_canais != 3)
    {
        printf ("ERRO: RGBParaHSL: as imagens precisam ter 3 canais.\n");
        exit (1);
    }

    if (in->largura != out->largura || in->altura != out->altura)
    {
        printf ("ERRO: RGBParaHSL: as imagens precisam ter o mesmo tamanho.\n");
        exit (1);
    }

    float vmax, vmin, croma, r, g, b, h, s, l;
    int row, col;
    for (row = 0; row < in->altura; row++)
        for (col = 0; col < in->largura; col++)
        {
            r = in->dados [0][row][col];
            g = in->dados [1][row][col];
            b = in->dados [2][row][col];

            vmax = MAX (r, MAX (g,b));
            vmin = MIN (r, MIN (g,b));
            croma = vmax - vmin;

            // L
            l = (vmax + vmin)*0.5f;

            // Trata de casos excepcionais.
            if (croma < FLT_EPSILON)
            {
                h = 0;
                s = 0;
            }
            else
            {
                // S
                if (l < 0.5)
                    s = croma/(vmax + vmin);
                else
                    s  = croma/(2-vmax-vmin);

                // H
                if (vmax == r)
                    h = 60*(g-b)/croma;
                else if (vmax == g)
                    h = 120+60*(b-r)/croma;
                else
                    h = 240+60*(r-g)/croma;

                if (h < 0) // Para evitar problemas de arredondamento.
                    h += 360.0f;
            }

            out->dados [0][row][col] = h;
            out->dados [1][row][col] = s;
            out->dados [2][row][col] = l;
        }
}

/*----------------------------------------------------------------------------*/
/** Conversão HSL -> RGB. Simplesmente segui as fórmulas.
 *
 * Parâmetros: Imagem* in: imagem de entrada.
 *             Imagem* out: imagem de saída. Deve ter o mesmo tamanho da
 *               imagem de entrada.
 *
 * Valor de retorno: nenhum */

void HSLParaRGB (Imagem* in, Imagem* out)
{
    if (in->n_canais != 3 || out->n_canais != 3)
    {
        printf ("ERRO: HSLParaRGB: as imagens precisam ter 3 canais.\n");
        exit (1);
    }

    if (in->largura != out->largura || in->altura != out->altura)
    {
        printf ("ERRO: HSLParaRGB: as imagens precisam ter o mesmo tamanho.\n");
        exit (1);
    }

    int row, col;
    float croma, x, m;
    float h, s, l;
    for (row = 0; row < in->altura; row++)
        for (col = 0; col < in->largura; col++)
        {
            s = in->dados [1][row][col];
            l = in->dados [2][row][col];

            if (s < FLT_EPSILON) // Sem saturação = sem cor.
            {
                out->dados [0][row][col] = l;
                out->dados [1][row][col] = l;
                out->dados [2][row][col] = l;
            }
            else
            {
                h = in->dados [0][row][col];

                croma = s * (1 - fabs (2*l-1));
                x = croma * (1 - fabs (fmod (h/60.0f, 2)-1));
                m = l-croma/2;

                if (h < 60)
                {
                    out->dados [0][row][col] = croma + m;
                    out->dados [1][row][col] = x + m;
                    out->dados [2][row][col] = m;
                }
                else if (h < 120)
                {
                    out->dados [0][row][col] = x + m;
                    out->dados [1][row][col] = croma + m;
                    out->dados [2][row][col] = m;
                }
                else if (h < 180)
                {
                    out->dados [0][row][col] = m;
                    out->dados [1][row][col] = croma + m;
                    out->dados [2][row][col] = x + m;
                }
                else if (h < 240)
                {
                    out->dados [0][row][col] = m;
                    out->dados [1][row][col] = x + m;
                    out->dados [2][row][col] = croma + m;
                }
                else if (h < 300)
                {
                    out->dados [0][row][col] = x + m;
                    out->dados [1][row][col] = m;
                    out->dados [2][row][col] = croma + m;
                }
                else
                {
                    out->dados [0][row][col] = croma + m;
                    out->dados [1][row][col] = m;
                    out->dados [2][row][col] = x + m;
                }
            }
        }
}

/*============================================================================*/
/* TRANSFORMAÇÕES DE CORES                                                    */
/*============================================================================*/
/** Inverte as cores de uma imagem, usando o complemento. Supomos pixels com
 * valores no intervalo [0,1].
 *
 * Parâmetros: Imagem* in: imagem de entrada.
 *             Imagem* out: imagem de saída, com o mesmo tamanho e número de
 *               canais.
 *
 * Valor de retorno: nenhum. */

void inverte (Imagem* in, Imagem* out)
{
    if (in->largura != out->largura || in->altura != out->altura || in->n_canais != out->n_canais)
    {
        printf ("ERRO: inverte: as imagens precisam ter o mesmo tamanho e numero de canais.\n");
        exit (1);
    }

	int i, j, k;
    for (i = 0; i < in->n_canais; i++)
        for (j = 0; j < in->altura; j++)
            for (k = 0; k < in->largura; k++)
                out->dados [i][j][k] = 1.0f - in->dados [i][j][k];
}

/*----------------------------------------------------------------------------*/
/** Ajuste simples de brilho e contraste: g(x,y) = (f(x,y)-0.5)*C + 0.5 + B.
 *
 * Parâmetros: Imagem* in: imagem de entrada. Se tiver mais que 1 canal,
 *               processa cada canal independentemente.
 *             Imagem* out: imagem de saída. Deve ter o mesmo tamanho da
 *               imagem de entrada.
 *             float brilho: ajuste do brilho.
 *             float contraste: ajuste do contraste.
 *
 * Valor de retorno: nenhum */

void ajustaBrilhoEContraste (Imagem* in, Imagem* out, float brilho, float contraste)
{
    if (in->largura != out->largura || in->altura != out->altura || in->n_canais != out->n_canais)
    {
        printf ("ERRO: ajustaBrilhoEContraste: as imagens precisam ter o mesmo tamanho e numero de canais.\n");
        exit (1);
    }

    int channel, row, col;
    for (channel = 0; channel < in->n_canais; channel++)
        for (row = 0; row < in->altura; row++)
            for (col = 0; col < in->largura; col++)
                out->dados [channel][row][col] = (in->dados [channel][row][col]-0.5f)*contraste + 0.5f + brilho;
}

/*----------------------------------------------------------------------------*/
/** Ajuste simples de gama: g(x,y) = f(x,y)-^G
 *
 * Parâmetros: Imagem* in: imagem de entrada. Se tiver mais que 1 canal,
 *               processa cada canal independentemente.
 *             Imagem* out: imagem de saída. Deve ter o mesmo tamanho da
 *               imagem de entrada.
 *             float gama: valor do gama.
 *
 * Valor de retorno: nenhum */

void ajustaGama  (Imagem* in, Imagem* out, float gama)
{
    if (in->largura != out->largura || in->altura != out->altura || in->n_canais != out->n_canais)
    {
        printf ("ERRO: ajustaGama: as imagens precisam ter o mesmo tamanho e numero de canais.\n");
        exit (1);
    }

    int channel, row, col;
    for (channel = 0; channel < in->n_canais; channel++)
        for (row = 0; row < in->altura; row++)
            for (col = 0; col < in->largura; col++)
                out->dados [channel][row][col] = powf (in->dados [channel][row][col], gama);
}

/*----------------------------------------------------------------------------*/
/** Ajuste simples de cores no espaço HSL. Consideramos que as imagens já estão
 * neste espaço. Não use imagens RGB aqui!!!
 *
 * Parâmetros: Imagem* in: imagem *HSL* de entrada.
 *             Imagem* out: imagem de saída. Deve ter o mesmo tamanho da
 *               imagem de entrada.
 *             float matiz: offset para o matiz.
 *             float saturacao: multiplicador para a saturação.
 *             float luminancia: constante somada à luminância.
 *
 * Valor de retorno: nenhum */

void ajustaHSL (Imagem* in, Imagem* out, float matiz, float saturacao, float luminancia)
{
    if (in->n_canais != 3 || out->n_canais != 3)
    {
        printf ("ERRO: ajustaHSL: as imagens precisam ter 3 canais.\n");
        exit (1);
    }

    if (in->largura != out->largura || in->altura != out->altura)
    {
        printf ("ERRO: ajustaHSL: as imagens precisam ter o mesmo tamanho.\n");
        exit (1);
    }

    int row, col;
    for (row = 0; row < in->altura; row++)
        for (col = 0; col < in->largura; col++)
        {
            if (matiz == 0.0f)
            {
                if (out != in)
                    out->dados [0][row][col] = in->dados [0][row][col];
            }
            else
                out->dados [0][row][col] = fmod (in->dados [0][row][col] + matiz, 360);

            if (saturacao == 1.0f)
            {
                if (out != in)
                    out->dados [1][row][col] = in->dados [1][row][col];
            }
            else
                out->dados [1][row][col] = in->dados [1][row][col] * saturacao;

            if (luminancia == 0.0f)
            {
                if (out != in)
                    out->dados [2][row][col] = in->dados [2][row][col];
            }
            else
                out->dados [2][row][col] = in->dados [2][row][col] + luminancia;
        }
}

/*============================================================================*/
