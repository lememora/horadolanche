#include "cenario.h"
 
/*
int colisao( hlcenario_celula_cen* pontper, Personagem* p)
{
	int colide;

	switch(p->dir)
	{
		case'c': if(p->posY/escala);
				break;
		
		case'b': if();
				break;

		case'e': if();
				break;

		case'd': if();
				break;
	}
	
	return(colide);
}
*/

/*
 * cria uma lista "quadruplamente ligada" em forma de matriz 
 */
hlcenario_celula_cen* constroi_Matriz(int lin,int col)
{
	int i,j;
	hlcenario_celula_cen* Matriz = NULL; 
	hlcenario_celula_cen* p = NULL;
	hlcenario_celula_cen* q = NULL; 
	hlcenario_celula_cen* r = NULL;
	hlcenario_celula_cen* s = NULL; 

	Matriz = criahlcenario_celula_cen();  
	p = Matriz;
	q = p;
	r = NULL;
	
	for(j=1;j<col;j++){
			s = criahlcenario_celula_cen();

			s->dir = p->dir;
			p->dir = s;
			s->esq = p;
			p=p->dir; 
	
			if(r!=NULL){
				p->cima = r;
				r->baixo = p;
				if(r->dir!=NULL)r=r->dir;			
			}
		
	} 
		
	for(i=1;i<lin;i++){
		r=q;
		q=criahlcenario_celula_cen();
		q->cima=r;
		r->baixo=q;
		if(r->dir!=NULL) r=r->dir;
		p=q;
		for(j=1;j<col;j++){

			s = criahlcenario_celula_cen();

			s->dir = p->dir;
			p->dir = s;
			s->esq = p;
			p=p->dir; 
	
			if(r!=NULL){
				p->cima = r;
				r->baixo = p;
				if(r->dir!=NULL)r=r->dir;			
			}

		}		
	}
	
	return(Matriz);
}
/*
 * cria um elemento de lista ligada
 */
elem* hlcenario_cria_elem()
{
	elem* p;

	if((p=(elem*)malloc(1*sizeof(elem)))==NULL)
		{
			fprintf (stderr, "\n%s",MSG_ERR_CRIAELEM);
			exit(EXIT_FAILURE);
		}
	p->prox = NULL;

	return(p);	
}


void hlcenario_insere_na_lista(elem* pontp, char simbolo)
{
	elem* pontq = hlcenario_cria_elem();

	pontq->prox = pontp->prox;
	pontp->prox = pontq;
	pontp = pontq;
	pontp->simb = simbolo;		
}

/*
 * Cria uma celula e liga à célula q "da esquerda"
 */
void hlcenario_insere_na_Matriz(hlcenario_celula_cen* pontq,hlcenario_celula_cen* pontr)
{
	hlcenario_celula_cen* pontp = criahlcenario_celula_cen();

	pontp->dir = pontq->dir;
	pontq->dir = pontp;
	pontp->esq = pontq;
	pontq=pontq->dir; 
	
	if(pontr!=NULL){
		pontq->cima = pontr;
		pontr->baixo = pontq;
		if(pontr->dir!=NULL)pontr=pontr->dir;			
	}
}

/*
 * cria um elemento de lista quadruplamente ligada
 */
hlcenario_celula_cen* criahlcenario_celula_cen()
{
	hlcenario_celula_cen* p;

	if((p=(hlcenario_celula_cen*)malloc(1*sizeof(hlcenario_celula_cen)))==NULL)
		{
			fprintf (stderr, "\n %s",MSG_ERR_CRIACELCEN);
			exit(EXIT_FAILURE);
		}

	p->cima =  NULL;	
	p->baixo = NULL;
	p->esq =   NULL;
	p->dir =   NULL;
	p->X = 0;
	p->Y = 0;
	p->tipo = CAMINHO_BLOQUEADO;
		
	return(p);
}



