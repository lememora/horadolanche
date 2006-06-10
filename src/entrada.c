#include "main.h"

#ifdef FASE1
/*
 * faz a leitura do arquivo de entrada e retorna uma lista de personagens 
 */ 
Personagem* leArquivo (char *arq, int *tempo, int *n)
{
	int i; /* contador */
	char a; /* argumento */ 

	/* atributos do personagem */	
	int posX, posY, massa, rotulo;
	char dir;

	FILE *fp;
	Personagem *lista, *ponta;
	
	if((fp=fopen(arq,"r"))==NULL)
	{
		fprintf(stderr, "%s\n", MSG_ERRO_ARQ_ENTRADA);
		exit (EXIT_FAILURE);
	}

	/* percorre o arquivo */
	while(!feof(fp)) 
	{
		fscanf (fp,".%c",&a);
		switch (a)
		{
			/* armazena tempo */
			case 't' :
				fscanf(fp,"\n%d",tempo);
			break;

			/* cria uma lista de personagens de acordo
			   com a quantidade de personagens */
			case 'n' :
				fscanf(fp,"\n%d",n);
				lista = criaPersonagem();
				ponta = lista;

				for(i=1;i<=*n;i++)
				{
					inserePersonagem (ponta);
					ponta = ponta->prox;
					ponta->rotulo = i;
				}
			break;

			/* armazena a energia e a massa de cada personagem */
			case 'm' :
				fscanf(fp,"%d\n%d",&rotulo,&massa);
				for(ponta=lista->prox;ponta->rotulo!=rotulo;ponta=ponta->prox);
				ponta->energia = (RELACAO_MASSA_ENERGIA*massa);
				ponta->massa = massa;
			break;

			/* armazena as posições x e y de cada personagem */
			case 's' :
				fscanf(fp,"%d\n%d\n%d",&rotulo,&posX,&posY);
				for(ponta=lista->prox;ponta->rotulo!=rotulo;ponta=ponta->prox);
				ponta->posX=posX;
				ponta->posY=posY;
			break;

			/* guarda a direção do personagem */
			case 'd' :
				fscanf(fp,"%d\n%c",&rotulo,&dir);
				for(ponta=lista->prox;ponta->rotulo!=rotulo;ponta=ponta->prox);
				ponta->dir=dir;
			break;
		}
	}
	
	fclose(fp);

	/* retorna a cabeça da lista de personagens */
	return(lista);
}


/*
 * escreve o arquivo de saída a partir de uma lista de personagens
 */
void escreveArquivo (Personagem *lista, char arq[], int tempo, int n) {
	Personagem *p;
	FILE* fp;

	if((fp=fopen(arq,"w"))==NULL)
	{
		fprintf (stderr, "%s\n", MSG_ERRO_ARQ_SAIDA);
		exit(EXIT_FAILURE);
	}
	fprintf(fp,"\n tempo:%d\n Numero de personagens: %d\n\n ",tempo,n);
  
	/* gera saída de cada personagem da lista */  
	for(p=lista;p!=NULL;p=p->prox)
	{
		fprintf(fp,"\n Personagem %d",p->rotulo);
		fprintf(fp,"\n Energia: %.1f", p->energia);
		fprintf(fp,"\n Massa: %d", p->massa);
		fprintf(fp,"\n Posicao: %.1f X   %.1f Y",(p->posX), (p->posY));
		fprintf(fp,"\n Direção: %c ",p->dir);
		fprintf(fp,"\n\n");
	}		

	fclose(fp);
}
# endif

Teclado *tecladoCria ()
{
   Teclado *teclado;
   teclado->thread = SDL_CreateThread (tecladoThread, (void *)(teclado));

   teclado->tecla=4;

   return(teclado);
}

int tecladoThread (void *args)
{
 	Teclado *teclado = (Teclado *)(args);
 	SDL_Event event;
	
	while(1)
	{
  	while( SDL_PollEvent( &event ) )
        {
       
            if( event.type == SDL_KEYDOWN )
            {

                switch( event.key.keysym.sym )
                {
                    case SDLK_UP:
			        teclado->tecla='c';
			        break;

                    case SDLK_DOWN: 
			        teclado->tecla='b';
			        break;

                    case SDLK_LEFT: 
		            teclado->tecla='e';
			        break;

                    case SDLK_RIGHT: 
			        teclado->tecla='d';
			        break;

                    case SDLK_q: exit(EXIT_SUCCESS); 
                    default: break; 
                }
            }
            else if( event.type == SDL_KEYUP )
            {

                switch( event.key.keysym.sym )
                {
                    case SDLK_UP: 
					if(teclado->tecla=='c')
					teclado->tecla='1';
					break;
		
                    case SDLK_DOWN: 
					if(teclado->tecla=='b')
					teclado->tecla='2';
					break;

                    case SDLK_LEFT: 
					if(teclado->tecla=='e')
					teclado->tecla='3';
					break;

                    case SDLK_RIGHT: 
					if(teclado->tecla=='d')
					teclado->tecla='4';
					break;

                    case SDLK_q: exit(EXIT_SUCCESS);  
	 	            default: break;			
                }
            }
            else if(event.type == SDL_QUIT )
            {
               printf("Quit event. Bye.\n");
               exit(0);
            }    
		}        
   }

 	return(0);
}

/**
 * Destroi a estrutura Teclado e o thread relacionado a ele
 * \param t	ponteiro para a estrutura teclado
 */
void tecladoDestroi (Teclado* t)
{


}
