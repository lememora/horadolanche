#include <stdlib.h>
#include <stdio.h>

#include "geral.h"
#include "inimigo.h"


/**
 * cria um inimigo
 * \param r			rótulo
 * \return          inimigo
 */
Inimigo *inimigoCria ()
{
        Inimigo *i;

        if((i=(Inimigo*)malloc(sizeof(Inimigo)))==NULL)
        {
                fprintf(stderr, "%s\n", "Inimigo malloc error");
                exit(EXIT_FAILURE);
        }

	i->rotulo  = 0;
	i->posX    = 0;
	i->posY    = 0;
	i->tamX    = 1;
	i->tamY    = 1;
	i->dano    = 0;
	i->veloc   = 0;
	i->trajeto = NULL;

        return (i);
}

/**
 * destrói um inimigo
 * \param p		inimigo
 */
void inimigoDestroi (Inimigo *i)
{	
	if (i->trajeto != NULL)
	{
		inimigoTrajetoDestroi (i->trajeto);
		i->trajeto = NULL;
	}

	if (i != NULL)
	{
		free (i);
	}
}

/**
 * cria uma lista de inimigos
 * \return              lista de inimigos
 */
InimigoLista *inimigoListaCria (Inimigo *i)
{
	InimigoLista *l;
	
	if (!(l = (InimigoLista *) malloc (sizeof(InimigoLista))))
	{
		fprintf (stdout, "InimigoLista malloc error\n");
		exit (EXIT_FAILURE);
	}

	l->inimigo = i;
	l->prox = NULL;

	return l;
}

/**
 * destroi uma lista de inimigos
 * \param l             lista de inimigos
 */
void inimigoListaDestroi (InimigoLista *l)
{
	/* TODO */
}

/**
 * cria um trajeto de inimigo
 * \param d     direção do movimento do trajeto
 * \return      trajeto
 */
InimigoTrajeto *inimigoTrajetoCria ()
{
	InimigoTrajeto *t;

	if((t=(InimigoTrajeto*)malloc(sizeof(InimigoTrajeto)))==NULL)
	{
		fprintf(stderr, "%s\n", "InimigoTrajeto malloc error");
		exit(EXIT_FAILURE);
	}

	t->dir  = MOV_DIR_NULL;
	t->prox = NULL;
	t->cab  = t;

	return (t);
}

/**
 * destrói um trajeto de inimigo
 * \param t     trajeto
 */ 
void inimigoTrajetoDestroi (InimigoTrajeto *t)
{
	InimigoTrajeto *ta;

	while (t!=NULL)
	{
		ta = t;
		t = t->prox;
		free (ta);
	}
}

/**
 * cria uma lista de inimigos a partir de um arquivo de inicialização
 * \parap a		arquivo de inicialização
 * \return		lista de inimigos
 */
InimigoLista *inimigoListaCarrega (char* a)
{
	char c;
	char d = MOV_DIR_NULL;

	FILE *fp = NULL;

	Inimigo        *i  = NULL;
	InimigoTrajeto *ta = NULL;
	InimigoTrajeto *th = NULL;
	InimigoTrajeto *tf = NULL;
	InimigoLista   *l  = NULL;
	InimigoLista   *la = NULL;

	l = inimigoListaCria (NULL);
	
	if ((fp = fopen(a, "r")) == NULL)
	{
		fprintf (stderr, "%s\n", "fopen error");
		exit (EXIT_FAILURE);
	}

	while (!feof(fp))
	{
		fscanf (fp, "$%c", &c);
		switch (c)
		{
			/* rótulo */
			case 'r' :
				i = inimigoCria ();
				la = inimigoListaCria (i);
				la->prox = l;
				l = la;
				fscanf (fp, "=%d\n", &i->rotulo);
			break;
			/* posição em x */
			case 'x' :
				fscanf (fp, "=%d\n", &i->posX);
			break;
			/* posição em y */
			case 'y' :
				fscanf (fp, "=%d\n", &i->posY);
			break;
			/* tamanho em x */
			case 'w' :
				fscanf (fp, "=%d\n", &i->tamX);
			break;
			/* tamanho em y */
			case 'h' :
				fscanf (fp, "=%d\n", &i->tamY);
			break;
			/* dano */
			case 'd' :
				fscanf (fp, "=%d\n", &i->dano);
			break;
			/* velocidade */
			case 'v' :
				fscanf (fp, "=%d\n", &i->veloc);
			break;
			/* trajeto */
			case 't' :
				/* cria stack com trajetos */
				for (fscanf (fp, "=%c", &d); d!='\n'; fscanf (fp, "%c", &d))
				{
					ta = inimigoTrajetoCria();
					ta->dir = d;
					ta->prox = th;
					th = ta;
				}
				/* cria lista de trajetos a partir do stack */
				while (th!=NULL)
				{
					ta = inimigoTrajetoCria();
					ta->dir = th->dir;
					ta->prox = i->trajeto;
					ta->cab = (ta->prox == NULL) ? ta : ta->prox->cab;
					i->trajeto = ta;
					tf = th;
					th = th->prox;
					free (tf);
				}
			break;
		}
	}
	
	return (l);
}

/**
 * coordena a movimentação do inimigo
 * \param p     inimigo
 */
void inimigoMove (Inimigo *i)
{
	switch (i->trajeto->dir) 
	{
		case MOV_DIR_CIMA :
			i->posY -= i->veloc;
		break;
		case MOV_DIR_DIREITA :
			i->posX += i->veloc;
		break;
		case MOV_DIR_BAIXO :
			i->posY += i->veloc;
		break;
		case MOV_DIR_ESQUERDA :
			i->posX -= i->veloc;
		break;
	}
	i->trajeto = (i->trajeto->prox == NULL) 
		? i->trajeto->cab 
		: i->trajeto->prox;
}
