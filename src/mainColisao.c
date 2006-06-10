#include "main.h"

int cenarioCelulaLivre(Personagem *personagem,Cenario *cenario,char direcao)
{
	int x,y;
	Cenario *posicaoPersMov;/* apontador para a celula para onde o personagem quer ir */
	
	x=personagem->posX;
	y=personagem->posY;
	switch (direcao) 
		{
			case 'c':
				y -= 1;
			break;
			case 'd' :
				x += 1;
			break;
			case 'b' :
				y += 1;
			break;
			case 'e' :
				x -= 1;
			break;
			default :
			break;
		}
	posicaoPersMov = coordPonteiro(x,y,cenario);
 	
	switch(posicaoPersMov->tipo)
	{
		case CAMINHO_LIVRE:
		return LIVRE;
		case CAMINHO_BLOQUEADO:
		return BLOQUEADO;
		case SAIDA:
		return SAIDA;
 	}
	return(0);
}

int colisaoInimigo ( Inimigo *inimigo,Personagem *personagem)
{
	
	if( (inimigo->posX == personagem->posX) && (inimigo->posY == personagem->posY) )
		return TRUE;
	else
		return FALSE;
}
	





