#include <stdio.h>
#include <stdlib.h>

#include "pdi.h"

#define THRESHOLD 0.6f

int main() {

    //Localização das imagens a serem segmentadas.
    char *imagens[5] = {
                        "../imagens/60.bmp" ,
                        "../imagens/82.bmp" , 
                        "../imagens/114.bmp", 
                        "../imagens/150.bmp", 
                        "../imagens/205.bmp" 
                       };
    char name[40] = "";
    Imagem *img, *buffer;

    //Procedimento para cada imagens.
    for(int i = 0; i < 5; i += 1) {

        //Carregando imagem em escala de cinza.
        img = abreImagem(imagens[i], 1);
        sprintf(name, "../resultados/%d1 - Cinza.bmp", i);
        salvaImagem(img, name); 

        //Criando imagens auxiliares, com o mesmo tamanho da imagem carregada.
        buffer = criaImagem(img->largura, img->altura, img->n_canais);

        filtroGaussiano(img, img, 5, 5, NULL);
        sprintf(name, "../resultados/%d2 - Borrada.bmp", i);
        salvaImagem(img, name);

        binariza(img, img, THRESHOLD);
        sprintf(name, "../resultados/%d3 - Binarizada.bmp", i);
        salvaImagem(img, name);

        //Desalocando memória previamente alocada.
        destroiImagem(img);
        destroiImagem(buffer);
    }

    return 0;
}