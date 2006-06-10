#include "main.h"
 


/*
 * Cria uma lista "quadruplamente ligada" em forma de matriz 
 * \param lin	argumento para o numero de linhas da matriz
 * \param col	argumento para o numero de colunas da matriz
 * return	ponteiro para a primeira celula da matriz
 */
Cenario* constroi_Matriz(int lin,int col)
{
	int i,j;
	/* 
    * Ponteiros de manipulação que serão úteis durante a 
    * construção da matriz 
    */
	Cenario* Matriz = NULL; 
	Cenario* p = NULL;
	Cenario* q = NULL; 
	Cenario* r = NULL; 
	Cenario* s = NULL; 

	Matriz = criaCenario();  
	p = Matriz;
	q = p;
	r = NULL;
	
	/* 
	 * Cria apenas a primeira linha da matriz 
	 * Esse procedimento ajuda a fazer a 'linkagem' 
	 * com as celulas das próximas linhas
	 */
	for(j=1;j<col;j++){
			s = criaCenario();

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
	
	/* A partir dessa primeira linha criada, cria as demais linhas*/	
	for(i=1;i<lin;i++){
		r=q;
		q=criaCenario();
		q->cima=r;
		r->baixo=q;
		if(r->dir!=NULL) r=r->dir;
		p=q;
		for(j=1;j<col;j++){

			s = criaCenario();

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
 * Cria um elemento de lista quadruplamente ligada
 * \return	ponteiro para uma celula do tipo 'criaCenario'
 */
Cenario* criaCenario()
{
	Cenario* p;

	/* Alocação Dinâmica da célula */
	if((p=(Cenario*)malloc(1*sizeof(Cenario)))==NULL)
		{
			fprintf (stderr, "\n %s",MSG_ERR_CRIACELCEN);
			exit(EXIT_FAILURE);
		}

	/* Por definição, todos os seus apontadores são NULL*/
	p->cima =  NULL;	
	p->baixo = NULL;
	p->esq =   NULL;
	p->dir =   NULL;
	p->X = 0;
	p->Y = 0;
	p->tipo = CAMINHO_BLOQUEADO;
		
	return(p);
}

/** Le um arquivo de entrada e retira as informações necessárias  
 *  para construir uma lista "quadruplamente ligada" em forma de matriz
 * \param arq	nome do arquivo a ser aberto
 * \param linhas	ponteiro para a variavel 'n° de linhas da matriz'
 * \param colunas	ponteiro para a variavel 'n° de colunas da matriz'
 */
void Cenario_leArquivo(char* arq,int *linhas,int *colunas)
{
	/* atributos da celula */	
	char caractere;	

	FILE *fp = NULL; /* Ponteiro para o arquivo de leitura*/			
	
	if((fp=fopen(arq,"r"))==NULL)
	{
		fprintf(stderr, "%s\n", MSG_ERR_FILEIN_CEN);
		exit (EXIT_FAILURE);
	}

	while(!feof(fp)) 
	{
		fscanf(fp,"%c",&caractere);
		switch(caractere){
			/* armazena dimensões da matriz */
			case 'w' : /* (size) */
				fscanf(fp,"\n%d",colunas);				
				break;

			case 'h':
				fscanf(fp,"\n%d",linhas);
				break;
		}	
	}
	
	fclose(fp);
	
}


/** Le um arquivo de entrada com a matriz detentora dos símbolos 
 *  referentes ao conteúdo do cenário (caminhos e paredes e outros
 *  obstaculos) para construir uma lista "quadruplamente ligada"  
 *  em forma de matriz
 * \param arq	nome do arquivo a ser aberto
 * \param matriz	recebe uma matriz prontinha para ser preenchida
 */
void Cenario_leMatriz(char* arq, Cenario* matriz,int num_nivel)
{
	int i = 0; /* contador */
	int j = 0; /* contador */	
	Cenario* p = NULL; /* Ponteiro para manipulação da matriz*/
	Cenario* q = NULL; /* Ponteiro para manipulação da matriz*/
	FILE *fp = NULL; /* Ponteiro para o arquivo de leitura*/
	char caractere;
	
	/*  */
	if((fp=fopen(arq,"r"))==NULL)
	{
		fprintf(stderr, "\n%s\n", MSG_ERR_FILEIN_CEN);
		exit (EXIT_FAILURE);
	}

	/* 
    * Loop que lê a matriz do arquivo de entrada e passa para a lista  
    * quadruplamente ligada. 
    */
	for(q=matriz; q!=NULL; q=q->baixo,i++){
		j=0;
		for(p=q; p!=NULL; p=p->dir,j++){
			fscanf(fp,"%c\n",&caractere);		
			p->tipo = caractere;
			p->X = j;
			p->Y = i;			
		   }				   
		}				

}

Cenario *coordPonteiro(int x,int y,Cenario *cen)
{
 
	while(x!=cen->X)
	{
		if(x>cen->X)
  			cen=cen->dir;
		else
			cen=cen->esq;
	}

	while(y!=cen->Y)
	{
	if(y>cen->Y)
		cen=cen->baixo;
	else
		cen=cen->esq;
	}
	
	return cen;
}
