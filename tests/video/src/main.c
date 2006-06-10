#include <stdlib.h>
#include <stdio.h>
#include "video.h"


int main () 
{
	Video    *v  = NULL; /* janela */
	VideoObj *bg = NULL; /* objeto p/ imagem de fundo */
	VideoObj *p  = NULL; /* objeto p/ imagem de personagem */

	int  x, y; /* posi��es x e y */
	char d;    /* dire��o (c, d, b, e) */ 


	/* inicializa janela */
	v = videoCria (800, 600, 16);

	/* define imagem de fundo */
	bg = videoObjCria ("./var/bg.png", 800, 600);
	videoFundo (v, bg); 

	/* define posi��es e dire��o inicial */
	x = 100;
	y = 100;
	d = 'd';

	/* adiciona imagem do personagem */
	p = videoObjCria ("./var/pers.png", 48, 62);
	videoAdcObj (v, p, x, y);

	/* define cor de transpar�ncia */
	videoObjTrans (p, 0x20, 0x9C, 0x00);

	/* define delay da anima��o do personagem */
	videoObjAniDelay (p, 250);

	/* define intervalo de quadros da anima��o */
	videoObjAniIntervalo (p, 0, 2);

	/* inicializa anima��o */
	videoObjAniInicia (p);


	while (1)
	{
		/* define caminho em um ret�ngulo e dire��o do movimento */
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

		/* define condi��o de quebra do loop */
		if (x == 100 && y == 100) {
			break;
		}

		/* define um intervalo de anima��o diferente para cada dire��o */
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

		/* exibe sa�da no v�deo */
		videoImprime (v);

		/* delay p/ atualiza��o do v�deo */
		SDL_Delay (30);
	}

	SDL_Delay (1000);

	/* destrutores */
	videoDestroi (v);
	videoObjDestroi (p);
	videoObjDestroi (bg);

	return 0;
}
