#include <stdlib.h>
#include <stdio.h>
#include "video.h"


int main () 
{
	Video    *v  = NULL; /* janela */
	VideoObj *bg = NULL; /* objeto p/ imagem de fundo */
	VideoObj *p  = NULL; /* objeto p/ imagem de personagem */

	int  x, y; /* posições x e y */
	char d;    /* direção (c, d, b, e) */ 


	/* inicializa janela */
	v = videoCria (800, 600, 16);

	/* define imagem de fundo */
	bg = videoObjCria ("./var/bg.png", 800, 600);
	videoFundo (v, bg); 

	/* define posições e direção inicial */
	x = 100;
	y = 100;
	d = 'd';

	/* adiciona imagem do personagem */
	p = videoObjCria ("./var/pers.png", 48, 62);
	videoAdcObj (v, p, x, y);

	/* define cor de transparência */
	videoObjTrans (p, 0x20, 0x9C, 0x00);

	/* define delay da animação do personagem */
	videoObjAniDelay (p, 250);

	/* define intervalo de quadros da animação */
	videoObjAniIntervalo (p, 0, 2);

	/* inicializa animação */
	videoObjAniInicia (p);


	while (1)
	{
		/* define caminho em um retângulo e direção do movimento */
		if (x < 700 && y == 100) {
			x += 5;
			d = 'd';
		} 
		if (x == 700 && y >= 100) {
			y+= 5;
			d = 'b';
		}
		if (x >= 100 && y == 500) {
			x-= 5;
			d = 'e';
		}
		if (x == 100 && y >= 100) {
			y-= 5;
			d = 'c';
		}

		/* define condição de quebra do loop */
		if (x == 100 && y == 100) {
			break;
		}

		/* define um intervalo de animação diferente para cada direção */
		switch (d) {
			case 'c' :
				videoObjAniIntervalo (p,  0,  3);
			break;
			case 'd' :
				videoObjAniIntervalo (p,  4,  7);
			break;
			case 'b' :
				videoObjAniIntervalo (p,  8, 11);
			break;
			case 'e' :
				videoObjAniIntervalo (p, 12, 15);
			break;
		}

		/* movimenta o personagem */
		videoMovObj (v, p, x, y);

		fprintf (stdout, 
			"x:%d\ty:%d\ti:%d\tq.x%d\tq.y%d\tq.w%d\tq.h%d\n", 
			p->posX, p->posY, p->indice,
			p->quadro.x, p->quadro.y, p->quadro.w, p->quadro.h
		);

		/* exibe saída no vídeo */
		videoImprime (v);

		/* delay p/ atualização do vídeo */
		SDL_Delay (30);
	}

	SDL_Delay (1000);

	/* destrutores */
	videoDestroi (v);
	videoObjDestroi (p);
	videoObjDestroi (bg);

	return 0;
}
