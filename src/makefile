all:
	gcc -o trabalho4 main.c base.c cores.c desenho.c filtros2d.c geometria.c imagem.c segmenta.c -lm

fast:
	gcc -o trabalho4 main.c base.c cores.c desenho.c filtros2d.c geometria.c imagem.c segmenta.c -lm -Ofast
	clear
	./trabalho4

debug:
	gcc -g -o trabalho4 main.c base.c cores.c desenho.c filtros2d.c geometria.c imagem.c segmenta.c -lm -Wall -Wextra

clean:
	rm trabalho4 ../resultados/*.bmp
