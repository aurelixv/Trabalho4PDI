#include <stdio.h>
#include <stdlib.h>

#include "pdi.h"

#define THRESHOLD 0.6f

//Novas funções
void mascara(Imagem *original, Imagem *mascara, Imagem *saida);

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
    Imagem *original, *entrada, *saida, *buffer;
    Imagem *kernel = criaKernelCircular(7);
    ComponenteConexo *componente;

    //Procedimento para cada imagens.
    for(int i = 0; i < 5; i += 1) {

        //Carregando imagem em escala de cinza.
        original = abreImagem(imagens[i], 1);
        sprintf(name, "../resultados/%d1 - Cinza.bmp", i + 1);
        salvaImagem(original, name); 

        //Criando imagens auxiliares, com o mesmo tamanho da imagem carregada.
        entrada = criaImagem(original->largura, original->altura, original->n_canais);
        copiaConteudo(original, entrada);
        saida = criaImagem(original->largura, original->altura, original->n_canais);
        buffer = criaImagem(original->largura, original->altura, original->n_canais);

        filtroGaussiano(entrada, saida, 5, 5, buffer);
        sprintf(name, "../resultados/%d2 - borrada.bmp", i + 1);
        salvaImagem(saida, name);
        copiaConteudo(saida, entrada);

        normalizaSemExtremos8bpp(entrada, saida, 0, 1, 0.01f);
        sprintf(name, "../resultados/%d3 - normalizada.bmp", i + 1);
        salvaImagem(saida, name);
        copiaConteudo(saida, entrada);

        binarizaAdapt(entrada, saida, 101, 0.2, buffer);
        sprintf(name, "../resultados/%d4 - binAdapt.bmp", i + 1);
        salvaImagem(saida, name);
        copiaConteudo(saida, entrada);

        dilata(entrada, kernel, criaCoordenada(4, 4), saida);
        sprintf(name, "../resultados/%d5 - dilata.bmp", i + 1);
        salvaImagem(saida, name);
        copiaConteudo(saida, entrada);

        mascara(original, entrada, saida);
        sprintf(name, "../resultados/%d6 - mascara.bmp", i + 1);
        salvaImagem(saida, name);
        copiaConteudo(saida, entrada);

        binariza(entrada, saida, 0.7f);
        sprintf(name, "../resultados/%d7 - binarizada.bmp", i + 1);
        salvaImagem(saida, name);
        copiaConteudo(saida, entrada);
        
        erode(entrada, kernel, criaCoordenada(4, 4), saida);
        sprintf(name, "../resultados/%d8 - Erode.bmp", i + 1);
        salvaImagem(saida, name);
        copiaConteudo(saida, entrada);

        printf("Numero de graos na imagem %d: %d\n", i + 1,rotulaFloodFill(entrada, &componente, 2, 2, 5));
        

        /* filtroGaussiano(original, saida, 5, 5, NULL);
        sprintf(name, "../resultados/%d2 - Borrada.bmp", i);
        salvaImagem(saida, name);

        
        Imagem *kernel = criaKernelCircular(11);
        salvaImagem(kernel, "kernel.bmp");
        erode(img, kernel, criaCoordenada(6, 6), buffer);
        sprintf(name, "../resultados/%d3 - Erode.bmp", i);
        salvaImagem(buffer, name);

        binariza(buffer, buffer, THRESHOLD);
        sprintf(name, "../resultados/%d4 - Binarizada.bmp", i);
        salvaImagem(buffer, name); */

        //Desalocando memória previamente alocada.
        destroiImagem(original);        
        destroiImagem(entrada);        
        destroiImagem(saida);
        destroiImagem(buffer);
    }

    return 0;
}

//Função para subtrair a imagem original da mascara, colocando o resultado na saida.
void mascara(Imagem *original, Imagem *mascara, Imagem *saida) {

    for(int y = 0; y < original->altura; y += 1) {
        for(int x = 0; x < original->largura; x += 1) {
            if(mascara->dados[0][y][x] == 1.0f)
                saida->dados[0][y][x] = original->dados[0][y][x];
            else
                saida->dados[0][y][x] = 0.0f;
        }
    }

}