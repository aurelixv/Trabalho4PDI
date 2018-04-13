#include "pdi.h"

int main() {

    //Localização das imagens a serem segmentadas.
    char *imagens[5] = {
                        "../imagens/60.bmp" ,
                        "../imagens/82.bmp" , 
                        "../imagens/114.bmp", 
                        "../imagens/150.bmp", 
                        "../imagens/205.bmp" 
                       };

    Imagem *img, *buffer;

    //Procedimento para cada imagens.
    for(int i = 0; i < 5; i += 1) {

        //Carregando imagem em escala de cinza.
        img = abreImagem(imagens[i], 1);

        //Criando imagens auxiliares, com o mesmo tamanho da imagem carregada.
        buffer = criaImagem(img->largura, img->altura, img->n_canais);


        //Desalocando memória previamente alocada.
        destroiImagem(img);
        destroiImagem(buffer);
    }

    return 0;
}