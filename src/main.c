#include "main.h"

/**
 * método principal
 */
int main ()
{
	/* construtures */
	Video *video = NULL;
	Teclado *teclado = NULL;
	NivelObjLista *nivelObjLista = NULL; 
	atexit(SDL_Quit);
	VideoObj* cen;

	/* inicializa vídeo e teclado */
	video = videoCria (VIDEOX, VIDEOY, COLOR_PALLETE);
	teclado = tecladoCria ();

	/* carrega lista de objetos nível com todos
	 * os níveis utilizados durante o jogo 
    */
	nivelObjLista = NivelObjListaCarrega (video);
	cen = videoObjCria ("./var/cen/img/bg.png",600,600);
	

	while(1){ videoFundo(video,cen);}
videoImprime(video);

	/* exibe cada uma das etapas de apresentação */
	inicio (video, teclado);
	jogo (video, teclado, nivelObjLista);
	fim (video, teclado);

	/* destrutores */
	tecladoDestroi (teclado);
	videoDestroi (video);	
	NivelObjListaDestroi (nivelObjLista);
	return(0);
}

/**
 * tela de jogo
 */
void jogo (Video *video, Teclado *teclado, NivelObjLista* nivelObjLista)
{
	int       		jogoConcluido;	
	NivelObj 			*nivelObj;
	int       		sdlTicksIni;
	int       		sdlTicksFim;
	InimigoObjLista	*inimigoAux;
/*	Alimento 			*alimentoAux;*/

	jogoConcluido = 0;
	
	nivelObj = nivelObjLista->nivelObj;

	/* loop principal */
	do 
	{
		/* obtém o tick inicial */
		sdlTicksIni = SDL_GetTicks();		

		/* movimentação do personagem */
		if (PersonagemObjSinc (video,nivelObj->personagemObj))
		{
			if (cenarioCelulaLivre(
				nivelObj->personagemObj->personagem, 
				nivelObj->cenarioObj->cenario,
				teclado->tecla)==0)
			{
				
				personagemMove (
					nivelObj->personagemObj->personagem, 
					teclado->tecla);
				for (
				inimigoAux=nivelObj->inimigoObjLista;
				inimigoAux!=NULL;
				inimigoAux=inimigoAux->prox)
				{
					if(colisaoInimigo(
						inimigoAux->inimigoObj->inimigo,
						nivelObj->personagemObj->personagem)==1)
							dano(
							inimigoAux->inimigoObj->inimigo->dano,
							nivelObj->personagemObj->personagem);
				}
			}
			else if(cenarioCelulaLivre(
				nivelObj->personagemObj->personagem, 
				nivelObj->cenarioObj->cenario,
				teclado->tecla)==SAIDA)
			{
				/*muda de nivel*/
			}
		
		}

		/* movimentação do inimigo */
		for (
			inimigoAux=nivelObj->inimigoObjLista;
			inimigoAux!=NULL;
			inimigoAux=inimigoAux->prox)
		{
			if (InimigoObjSinc (inimigoAux->inimigoObj))
			{
				inimigoMove (inimigoAux->inimigoObj->inimigo);
			}
		}

		/* define um quadro de animação para os objetos de video*/
		/*defineInterAni(nivelObj);*/

		/* exibe conteúdo do vídeo */
		videoImprime (video);

		/* obtém o tick final */
		sdlTicksFim = SDL_GetTicks();

		/* calcula delay de vídeo levando em consideração
		 * o intervalo de ticks (tempo de processamento) */
		if (sdlTicksFim < sdlTicksIni + (1000 / FPS))
		{
			SDL_Delay (sdlTicksIni + (1000 / FPS) - sdlTicksFim);
		}

	/* executa loop principal
	 * enquanto a condição de jogo não terminar */
	} while (jogoConcluido == 0);
	
}

/**
 * tela inicial
 */
void inicio (Video *video, Teclado *teclado)
{
}

/**
 * tela final
 */
void fim (Video *video, Teclado *teclado)
{
}

/**
 * sincroniza a verossimilhança entre as informações
 * de vídeo e dados da estrutura de objeto personagem
 */
int PersonagemObjSinc (Video* v,PersonagemObj *o)
{
	int sincX;
	int sincY;
	int videoX;
	int videoY;
	int personagemX;
	int personagemY;
	int personagemvel;
	int move;

	/* obtém a posição do objeto de vídeo */
	videoX = o->videoObj->posX;
	videoY = o->videoObj->posY;

	/* obtém a posição e velocidade do objeto de dados */
	personagemX = o->personagem->posX * CENARIO_CEL_TAM_PIXEL ;
	personagemY = o->personagem->posY * CENARIO_CEL_TAM_PIXEL;
	personagemvel = personagemVel (o->personagem);

	/* verifica sincronia */
	sincX = (personagemX == videoX) ? TRUE : FALSE;
	sincY = (personagemY == videoY) ? TRUE : FALSE;

	/* verifica quantidade em pixels para o movimento
	 * de sincronização durante a atualização de um frame */
	move = CENARIO_CEL_TAM_PIXEL / (FPS / personagemvel);
	move = (move <= 1) ? 1 : move;

	/* sincroniza em x */
	if (sincX == FALSE)
	{
		videoX = ((videoX + move) > personagemX) 
			? personagemX 
			: videoX + move;
	}

	/* sincroniza em y */
	if (sincY == FALSE)
	{
		videoY = ((videoY + move) > personagemY) 
			? personagemY 
			: videoY + move;
	}
	
	/* move objeto de vídeo */
	if (sincX == FALSE || sincY == FALSE)
	{
		videoObjMove (v,o->videoObj, videoX, videoY);
	}

	/* verifica novamente a sincronia */
	sincX = (personagemX == videoX) ? TRUE : FALSE;
	sincY = (personagemY == videoY) ? TRUE : FALSE;

	return (sincX == TRUE || sincY == TRUE) ? TRUE : FALSE;
}

/**
 * sincroniza a verosimilhança entre as informações
 * de vídeo e dados da estrutura de objeto inimigo 
 */
int InimigoObjSinc (InimigoObj *o)
{
	return 0;
}

/**
 * sincroniza a verosimilhança entre as informações
 * de vídeo e dados da estrutura de objeto alimento 
 */
int alimentoObjSinc (AlimentoObj *o)
{
	return 0;
}

/**
 * cria um objeto cenário
 * \param
 * \return 
 */
CenarioObj* CenarioObjCria (Video* v, int nivel)
{
	int linhas,colunas;/*variaveis p/ as linhas e colunas da matriz cenario*/
	CenarioObj* p;
	char arqDef[100];
	char arqMat[100];
	char arqImg[100];	
	
	/* Define o caminho para o acesso do arquivo de leitura 'def.txt' */
	sprintf(arqDef,"%sdef.txt",FILES_CEN_PATH);

	/* 
	 * Define o caminho para o acesso do arquivo de leitura da matriz 
	 * dependendo do nivel do cenario
	 */
	sprintf(arqMat,"%s%d.txt",FILES_CEN_PATH,nivel);

	/* 
	 * Define o caminho para o acesso do arquivo de imagens de background 
	 * dependendo do nivel do cenario
	 */
	sprintf(arqImg,"%s%d.png",IMG_CEN_PATH,nivel);
	
	if((p=(CenarioObj*)malloc(1*sizeof(CenarioObj)))==NULL)
		{
			fprintf (stderr, "\n %s",MSG_ERR_CenarioObjCria);
			exit(EXIT_FAILURE);
		}

	/* Cria a matriz do cenario da estrutura CenarioObj */
	Cenario_leArquivo(arqDef,&linhas,&colunas);

	p->cenario = constroi_Matriz(linhas,colunas);

	Cenario_leMatriz(arqMat,p->cenario,nivel);

	/* Cria a imagem de fundo do cenario da estrutura CenarioObj */
	p->videoObj = videoObjCria (arqImg,VIDEOX, VIDEOY);
	
	/* Adiciona a imagem de fundo à estrutura Video */
	videoFundo (v,p->videoObj);	
	
	return(p);
}

/**
 * destroi um objeto cenário
 */
void CenarioObjDestroi (CenarioObj *o)
{
}


/**
 * cria um objeto personagem
 * \param
 * \return 
 */
PersonagemObj* PersonagemObjCria(Video* v)
{		
	int VideoX = 0;
	int VideoY = 0;	
	PersonagemObj* p = NULL;
	
	if((p=(PersonagemObj*)malloc(1*sizeof(PersonagemObj*)))==NULL)
		{
			fprintf (stderr, "\n %s",MSG_ERR_PersonagemObjCria);
			exit(EXIT_FAILURE);
		}
	
	/* Ajusta os dados sobre o personagem e sua posição na tela */	
	p->personagem = personagemCarrega (PER_FILES_PATH);

	VideoX = p->personagem->posX * CENARIO_CEL_TAM_PIXEL;
	VideoY = p->personagem->posY * CENARIO_CEL_TAM_PIXEL;

	/* 
	 * Ajusta os atributos das imagens das posições do personagem a 
    * partir de uma  figura a ser carregada no disco rígido. Esta imagem
	 * já contem o personagem gordo e magro.
	 */
	p->videoObj = VideoObjSetaAtributos_IMG(PER_IMG_PATH);

	/* Adiciona a imagem do personagem à estrutura Video */
	videoAdcObj (v,p->videoObj,VideoX,VideoY);
	
	return(p);
}

/**
 * destroi um objeto personagem
 */
void PersonagemObjDestroi (PersonagemObj *o)
{
	PersonagemObj* aux;

	personagemDestroi(aux->personagem);
	videoObjDestroi(aux->videoObj);
	free(aux);	
}

/**
 * cria uma celula do tipo 'InimigoObj' 
 * \param
 * \return	ponteiro para a celula InimigoObj
 */
InimigoObj* InimigoObjCria(Video* v,int nivel,Inimigo* inim)
{
	InimigoObj* p = NULL;
	char arqImg[100];	

	if((p=(InimigoObj*)malloc(1*sizeof(InimigoObj)))==NULL)
		{
			fprintf (stderr, "\n %s",MSG_ERR_PersonagemObjCria);
			exit(EXIT_FAILURE);
		}

	p->inimigo = inim;

	sprintf(arqImg,"%s%d/Inimigo%d.png",INI_IMG_PATH,nivel,inim->rotulo);

	p->videoObj = VideoObjSetaAtributos_IMG (arqImg);
	videoAdcObj (v,p->videoObj,
               (p->inimigo->posX*CENARIO_CEL_TAM_PIXEL),
               (p->inimigo->posY*CENARIO_CEL_TAM_PIXEL));					


	return(p);
}

/**
 * libera a memoria ocupada por uma celula da lista de objetos inimigo
 * \param o	celula da estutura Inimigo 
 */
void InimigoObjDestroi(InimigoObj* o)
{
	InimigoObj* aux;

	videoObjDestroi(aux->videoObj);
	inimigoDestroi(aux->inimigo);

	free(aux);
}
 
 /**
 * cria uma celula da lista de objetos inimigo
 * \param
 * \return 
 */
InimigoObjLista* InimigoObjListaCria (Video* v,int num_nivel,Inimigo* ini)
{
	InimigoObjLista* p = NULL;	
	
	if((p=(InimigoObjLista*)malloc(1*sizeof(InimigoObjLista)))==NULL)
		{
			fprintf (stderr, "\n %s",MSG_ERR_PersonagemObjCria);
			exit(EXIT_FAILURE);
		}

	p->inimigoObj = InimigoObjCria(v,num_nivel,ini);
	p->prox = NULL;

	return(p);
}

/**
 * libera a memoria ocupada por uma celula da lista de objetos inimigo
 * \param
 * \return 
 */
void InimigoObjListaDestroi(InimigoObjLista* o)
{
	InimigoObjLista* aux1 = NULL;
	InimigoObjLista* aux2 = NULL;

	while(aux1!=NULL)
	{
		InimigoObjDestroi(aux1->inimigoObj);
		aux2=aux1;
		aux1=aux1->prox;
		free(aux2);
	}

}

/**
 * monta e carrega toda uma lista ligada de 'InimigoObjLista's
 * \param
 * \return 
 */
InimigoObjLista* InimigoObjListaCarrega (Video *v,int num_nivel)
{
	InimigoObjLista* p = NULL;
	/*Ponteiro auxiliar para a lista InimigoObj*/

	InimigoObjLista* paux = NULL;
	/* Idem ao anterior*/

	InimigoLista* lista_inimigos = NULL; 
	/* Ponteiro para a lista ligada dos inimigos 
    * criada a partir de um arquivo de leitura 
    */

	char arqInim[100]; /* String para a montagem do arquivo de entrada */
	int num_inim; 
	/* Guarda o número de inimigos armazenados na lista 'lista_inimigos'*/ 
	int i; /* Contador */

	sprintf(arqInim,"%s%d.txt",INI_FILES_PATH,num_nivel);

	/* Gera a lista de inimigos a partir de um arquivo de entrada */
	lista_inimigos = inimigoListaCarrega(arqInim);

	/* Obtem o numero de inimigos da lista ligada */
	num_inim = lista_inimigos->inimigo->rotulo;	

	/*
	 * Este loop cria o numero de celulas de acordo com 
	 * o numero de inimigos do arquivo de entrada 
	 */
	for(i=0;i<num_inim;i++)
	{						
		p=InimigoObjListaCria(v,num_nivel,lista_inimigos->inimigo);				
		lista_inimigos = lista_inimigos->prox;	
		p->prox = paux;
		paux = p;		
	}	

	return(p);
}

#ifdef alimento
AlimentoObj* AlimentoObjCria(int nivel, int rotulo)
{
	AlimentoObj* p;	
	char arqImg[100];
	
	sprintf(arqImg,"%s/%d/%d.png",INI_IMG_PATH,nivel,rotulo);

	if((p=(AlimentoObj*)malloc(1*sizeof(AlimentoObj)))==NULL)
		{
			fprintf (stderr, "\n %s",MSG_ERR_AlimentoObjCria);
			exit(EXIT_FAILURE);
		}

	p->videoObj = VideoObjSetaAtributos_IMG (arqImg);
						
	p->alimento  = NULL;

	return(p);
	
}


/**
 * cria uma celula de lista ligada 'AlimentoObjLista' 
 * \param
 * \return 
 */
AlimentoObjLista* AlimentoObjListaCria (char *arqDados)
{
	AlimentoObjLista* p;
	
	if((p=(AlimentoObjLista*)malloc(1*sizeof(AlimentoObjLista)))==NULL)
		{
			fprintf (stderr, "\n %s",MSG_ERR_AlimentoObjListaCria);
			exit(EXIT_FAILURE);
		}
	p->alimento = alimentoCarrega (arqDados);
	p->prox = NULL;
	

	return(p);
}

/**
 * monta e carrega toda uma lista ligada de 'alimentoObjLista's
 * \param
 * \return 
 */
AlimentoObjLista* AlimentoObjListaCarrega(char *arqDados)
{

}

/**
 * destroi uma lista de objetos alimento
 */
void AlimentoObjListaDestroi (AlimentoObjLista *l)
{
}
#endif

/**
 * cria um nivel do jogo
 * \param
 * \return 
 */
NivelObj* NivelObjCria (Video *v,int nivel)
{
	NivelObj* p = NULL; 	

	if((p=(NivelObj*)malloc(1*sizeof(NivelObj)))==NULL)
		{
			fprintf (stderr, "\n %s",MSG_ERR_NivelObjCria);
			exit(EXIT_FAILURE);
		}

	p->cenarioObj = CenarioObjCria (v,nivel);
	p->personagemObj = PersonagemObjCria(v);
	p->inimigoObjLista = InimigoObjListaCarrega(v,nivel);
/*	p->alimentoObjLista = AlimentoObjListaCarrega(v,nivel);	*/

	return(p);
}

/**
 * 
 * \param
 * \return 
 */
void NivelObjDestroi(NivelObj* o)
{
	NivelObj* aux = o;

	CenarioObjDestroi(aux->cenarioObj);
	PersonagemObjDestroi(aux->personagemObj);	
	InimigoObjListaDestroi(aux->inimigoObjLista);
/*	AlimentoObjListaDestroi(aux->alimentoObjLista);*/

	free(aux);
}

/**
 *
 * \param
 * \return 
 */
NivelObjLista* NivelObjListaCria(Video *v,int nivel)
{
	NivelObjLista* p = NULL;

	if((p=(NivelObjLista*)malloc(1*sizeof(NivelObjLista*)))==NULL)
		{
			fprintf (stderr, "\n %s",MSG_ERR_NivelObjListaCria);
			exit(EXIT_FAILURE);
		}
	p->rotulo=&nivel;
	p->nivelObj = NivelObjCria (v,nivel);
	p->prox = NULL;
	p->ant = NULL;

	return(p);
	
}

/**
 *
 * \param
 * \return 
 */
NivelObjLista* NivelObjListaCarrega(Video *v)
{
	int i;
	NivelObjLista* p = NULL;	
	NivelObjLista* paux = NULL;

	for(i=0;i<NUM_NIVEIS;i++)
	{
		paux=p;
		p=NivelObjListaCria(v,i+1);		
		p->prox = NULL;
		p->ant = paux;
	}	
		
	return(p);
}

/**
 *
 * \param
 * \return 
 */
void NivelObjListaDestroi (NivelObjLista *o)
{
	NivelObjLista* aux1 = o;
	NivelObjLista* aux2 = NULL;

	while(aux1!=NULL){
		NivelObjDestroi(aux1->nivelObj);		
		aux2=aux1;
		aux1=aux1->prox;
		free(aux2);
	}			
}


/**Prepara as imagens de um objeto
 * \param
 * \return 
 */  
VideoObj* VideoObjSetaAtributos_IMG (char* path)
{
	VideoObj* pers;	

	pers = videoObjCria (path, 48, 62); 
	
	/* define cor de transparência */
	videoObjTrans (pers, 0x20, 0x9C, 0x00);

	/* define delay da animação do personagem */
	videoObjAniDelay (pers, 200);

	/* define intervalo de quadros da animação */
	videoObjAniIntervalo (pers, 5, 5);

	/* inicializa animação */
	videoObjAniInicia (pers);

	return(pers);
}
