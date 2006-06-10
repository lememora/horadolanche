#include <stdlib.h>
#include <stdio.h>

#include "geral.h"
#include "main.h"
#include "inimigo.h"


void inimigoImprime (Inimigo *i);
void inimigoImprimeLista (InimigoLista *l);


int main (int argc, char *argv[])
{
/*	Inimigo *i;*/
	InimigoLista *l;
/*	InimigoLista *la;*/

/*	int c;*/

	/* cria lista de inimigos a partir de um arquivo */
	l = inimigoListaCarrega (MAIN_INI_ARQ_INI_1);

	/* imprime informação de todos os inimigos e trajetos de cada um */
	fprintf (stdout, "%s\n", "testando lista de inimigos e lista de trajetos");

	inimigoImprimeLista (l);
	fprintf (stdout, "\n");

	return 0;
}


void inimigoImprime (Inimigo *i)
{
	fprintf (stdout, 
		"r:%d\tx:%d\ty:%d\tw:%d\th:%d\td:%d\tv:%d\tt:%c\n", 
		i->rotulo, i->posX, i->posY, i->tamX, i->tamY, 
		i->dano, i->veloc, i->trajeto->dir);
}

void inimigoImprimeLista (InimigoLista *l)
{
	Inimigo *i;
	InimigoLista *la;
	InimigoTrajeto *t;

	/* imprime cada inimigo */
	for (la=l; la->inimigo!=NULL; la=la->prox)
	{
		i = la->inimigo;

		fprintf (stdout, 
			"r:%d\tx:%d\ty:%d\tw:%d\th:%d\td:%d\tv:%d\tt:", 
			i->rotulo, i->posX, i->posY, i->tamX, i->tamY, 
			i->dano, i->veloc);
		t = i->trajeto;
		for (t=i->trajeto; t!=NULL; t=t->prox)
		{
			fprintf (stdout, "%c", t->dir);
		}
		fprintf (stdout, "\n");

	}
}
