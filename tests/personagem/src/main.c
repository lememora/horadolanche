#include <stdlib.h>
#include <stdio.h>

#include "geral.h"
#include "main.h"
#include "personagem.h"


void imprimePersonagem (Personagem *p);

int main (int argc, char *argv[])
{
	char        a[32];
	FILE       *f = NULL;
	int         c;
	Personagem *p = NULL;
	char        d = MOV_DIR_NULL;
	
	for (c=0; c<argc; c++)
	{
		if (argv[c][0] == '-')
		{
			switch (argv[c][1])
			{
				case 'i' :
					strcpy (a, argv[c+1]);
				break;
			}
		}
	}

	p = personagemCarrega (MAIN_PER_ARQ_INI_1);

	if((f = fopen (a, "r")) == NULL) {
		fprintf (stderr, "%s %s\n", &a, "fopen error");
		exit (EXIT_FAILURE);
	}

	while (!feof(f))
	{
		fscanf (f, "\n%c", &d);
		imprimePersonagem (p);
		personagemMove (p, d);
	}

	imprimePersonagem (p);
	personagemDestroi (p);

	return 0;
}

void imprimePersonagem (Personagem *p)
{
	fprintf (stdout, "x:%d\ty:%d\td:%c\te:%.2f\tm:%d\n", 
		p->posX, p->posY, p->dir, p->energia, personagemMassa(p));
}
