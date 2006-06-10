#include <stdlib.h>
#include <stdio.h>

#include "geral.h"
#include "personagem.h"


/**
 * cria um personagem
 * \param x		posição x do personagem
 * \param y		posição y do personagem
 * \param d		direção de movimento do personagem
 * \param e		energia do personagem
 * \return		personagem
 */
Personagem *personagemCria (int x, int y, char d, float e)
{
        Personagem *p;

        if((p=(Personagem*)malloc(sizeof(Personagem)))==NULL)
        {
                fprintf(stderr, "%s\n", "Personagem malloc error");
                exit(EXIT_FAILURE);
        }

		p->posX    = x;
		p->posY    = y;
		p->dir     = d;
		p->energia = e;

        return(p);
}

/**
 * destrói um personagem
 * \param p		personagem
 */
void personagemDestroi (Personagem *p)
{	
	if (p != NULL)
	{
		free(p);
	}
}

/**
 * cria um personagem a partir de um arquivo de inicialização
 * \parap a		arquivo de inicialização
 * \return		personagem
 */
Personagem *personagemCarrega (char* a)
{
	int  x = 0;
	int  y = 0;
	char d = MOV_DIR_NULL;
	int  e = 0;

	FILE *fp = NULL;
	char c;

	Personagem *p = NULL;
	
	if ((fp = fopen(a, "r")) == NULL)
	{
		fprintf (stderr, "%s %s\n", &a, "fopen error");
		exit (EXIT_FAILURE);
	}

	while (!feof(fp))
	{
		fscanf (fp, ".%c", &c);
		switch (c)
		{
			case 'x' :
				fscanf (fp, "\n%d", &x);
			break;
			case 'y' :
				fscanf (fp, "\n%d", &y);
			break;
			case 'e' :
				fscanf (fp, "\n%d", &e);
			break;
		}
	}

	p = personagemCria (x, y, d, (float)(e));

	return (p);
}

/**
 * obtém a massa do personagem
 * \param p		personagem
 * \return		massa do personagem em kg
 */
int personagemMassa (Personagem *p)
{
	return (p->energia >= PER_ENERG_DESNUT)
		? p->energia / PER_MASSA_ENERG
		: PER_ENERG_DESNUT / PER_MASSA_ENERG;
}

/**
 * obtém a velocidade do personagem
 * \param p		personagem
 * \return		velocidade do personagem em m/s
 */
int personagemVel (Personagem *p)
{
	return (p->energia <= PER_ENERG_NORMAL) ? PER_VEL_MAX : PER_VEL_MIN;
}

/**
 * retorna saúde do personagem
 * \param p		personagem
 * \return		saúde do personagem (desnutrido, normal ou obeso)
 */
int personagemSaude (Personagem *p)
{
	return (p->energia < PER_ENERG_DESNUT) 
		? PER_SAUDE_DESNUT 
		: (p->energia > PER_ENERG_NORMAL) 
			? PER_SAUDE_OBESO 
			: PER_SAUDE_NORMAL;
}

/**
 * coordena a movimentação do personagem e o consumo de energia
 * deve ser utilizada mesmo quando não há movimento (d == MOV_DIR_NULL)
 * pois realiza o consumo de energia vital
 * \param p		personagem
 * \param d		direção do movimento
 */
void personagemMove (Personagem *p, char d)
{
	int   vel;
	float con;
	int   mas;
	vel    = personagemVel (p);
	con    = 0;
    mas    = personagemMassa (p);
	p->dir = d;

	if (p->energia > 0)
	{
		switch (p->dir) 
		{
			case MOV_DIR_CIMA :
				p->posY -= vel;
			break;
			case MOV_DIR_DIREITA :
				p->posX += vel;
			break;
			case MOV_DIR_BAIXO :
				p->posY += vel;
			break;
			case MOV_DIR_ESQUERDA :
				p->posX -= vel;
			break;
			default :
				p->dir = MOV_DIR_NULL;
			break;
		}
	}

	if (p->dir != MOV_DIR_NULL) 
	{
		con += (float) (mas * vel * PER_CONS_ENERG_MOV);
	}
	con += (float) (mas * PER_CONS_ENERG_REP);

	p->energia = (p->energia > con) ? p->energia - con : 0;
}

/**
 * recupera a energia de um personagem
 * \param p		personagem
 * \param r		energia fornecida para recuperação
 */
void personagemRecupera (Personagem *p, float r)
{
	p->energia = ((p->energia + r) > PER_ENERG_MAX)
		? PER_ENERG_MAX
		: p->energia + r;
}
