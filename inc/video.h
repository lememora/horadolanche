#define VIDEOX 800
#define VIDEOY 600
#define COLOR_PALLETE 16

/* define a localiza��o dos arquivos de imagem do jogo */
#define IMG_CEN_PATH "./var/cen/img/"
#define PER_IMG_PATH "./var/per/img/Personagem.png"
#define INI_IMG_PATH "./var/ini/img/"


/** 
 * \todo
 * � preciso corrigir os rastros que aparecem na tela durante o movimento
 * e anima��o de sprites na tela. Isto pode estar sendo ocasionado pelo
 * constante interrupmento de threads durante a troca de intervalo de anima��es
 */


/** 
 * \struct VideoObj
 * 
 * \brief Estrutura de objeto de v�deo.
 *
 * Os objetos de v�deo s�o respons�veis por armazenar os sprites de
 * objetos e anima��es que ser�o exibidos na tela.
 * 
 */
typedef struct VideoObj {
	int          posX;         /**< posi��o x */
	int          posY;         /**< posi��o y */
	SDL_Rect     quadro;       /**< quadro de corte da imagem */
	SDL_Surface *imagem;       /**< imagem */
	int          indice;       /**< �ndice de posi��o do quadro */
	SDL_Thread  *ani_thread;   /**< thread de anima��o */
	int          ani_ativa;    /**< atividade de anima��o */
	int          ani_indice_i; /**< �ndice inicial do intervalo de anima��o */
	int          ani_indice_f; /**< �ndice final do intervalo de anima��o */
	int          ani_delay;    /**< delay da anima��o */
} VideoObj;

/**
 * \struct VideoObjLista
 * 
 * \brief Estrutura de lista de objetos de v�deo.
 *
 */
typedef struct VideoObjLista
{
	VideoObj             *vobj; /* objeto de v�deo */
	struct VideoObjLista *prox; /* pr�ximo membro da estrutura */
} VideoObjLista;


/** 
 * Cria um objeto de v�deo.
 *
 * \param a		arquivo de imagem
 * \param l		largura do quadro
 * \param a		altura do quadro
 * \return		objeto de v�deo
 */
VideoObj *videoObjCria (char *a, int w, int h);

/**
 * Destr�i um objeto de v�deo. 
 * 
 * \param o		objeto de v�deo
 */
void videoObjDestroi (VideoObj *o);

/** 
 * Define cor de transpar�ncia de um objeto de v�deo.
 *
 * \param o		objeto de v�deo
 * \param r		valor para cor vermelha
 * \param g		valor para cor verde
 * \param b		valor para cor azul
 */
void videoObjTrans (VideoObj *o, int r, int g, int b);

/**
 * Define o �ndice de posi��o do quadro.
 *
 * \param o		objeto de v�deo
 * \param i		�ndice de posi��o do quadro
 */
void videoObjIndice (VideoObj *o, int i);

/**
 * Avan�a para o pr�ximo �ndice de posi��o do quadro. 
 *
 * \param o		objeto de v�deo
 */
void videoObjIndiceProx (VideoObj *o);

/**
 * Retorna ao �ndice anterior de posi��o do quadro.
 * 
 * \param o		objeto de v�deo
 */
void videoObjIndiceAnt (VideoObj *o);

/**
 * Define delay de anima��o de um objeto de v�deo. 
 *
 * \param o		objeto de v�deo
 * \param d		delay da anima��o
 */
void videoObjAniDelay (VideoObj *o, int d);

/**
 * Define o intervalo de anima��o de um objeto de v�deo. 
 * 
 * \param o		objeto de v�deo
 * \param i		�ndice de posi��o inicial do quadro
 * \param f		�ndice de posi��o final do quadro
 */
void videoObjAniIntervalo (VideoObj *o, int i, int f);

/**
 * Fun��o para thread de anima��o de um objeto de v�deo.
 * 
 * \param o		objeto de v�deo (objeto de v�deo c/ casting p/ void)
 * \return		inteiro nulo
 */
int videoObjAniThread (void *o);

/**
 * Inicia a anima��o de um objeto de v�deo.
 * 
 * \param o		objeto de v�deo
 */
void videoObjAniInicia (VideoObj *o);

/**
 * Termina a anima��o de um objeto de v�deo.
 *
 * \param o		objeto de v�deo
 */
void videoObjAniTermina (VideoObj *o);

/**
 * Cria um elemento para a lista de objetos de v�deo.
 * 
 * \param o		objeto de v�deo
 * \return		elemento da lista de objetos de v�deo
 */
VideoObjLista *videoObjListaCria (VideoObj *o);

/**
 * Destr�i lista de objetos de v�deo.
 *  
 * \param l		primeiro elemento da lista de objetos de v�deo
 */
void videoObjListaDestroi (VideoObjLista *l);


/**
 * \struct Video
 * 
 * \brief Estrutura da janela de v�deo.
 *
 * A janela de v�deo � composta por tr�s camadas (Janela, fundo e 
 * lista de objetos de v�deo). A Janela � a moldura no gerenciador 
 * gr�fico, o fundo � o objeto de v�deo utilizado para cobrir atualiza��es
 * da lista de objetos de v�deo e a lista de objetos de v�deo cont�m os
 * sprites que ser�o exibidos/animados na tela.
 * 
 */
typedef struct Video
{
	SDL_Surface   *video;    /* v�deo */
	VideoObj      *fundo;    /* objeto de v�deo para imagem de fundo */
	VideoObjLista *vobj_lst; /* lista de objetos de v�deo */
} Video;

/**
 * Cria janela de v�deo
 * 
 * \param l		largura
 * \param a		altura
 * \param c		n�mero de cores
 * \return		v�deo
 */
Video *videoCria (int l, int a, int c);

/**
 * Destr�i janela de v�deo
 * 
 * \param v		v�deo
 */
void videoDestroi (Video *v);

/**
 * Define o objeto de fundo da janela de v�deo.
 * 
 * \param v		v�deo
 * \param o		objeto de v�deo
 */
void videoFundo (Video *v, VideoObj *o);

/**
 * Adiciona objeto de v�deo � lista de objetos da janela
 * 
 * \param v		v�deo
 * \param o		objeto de v�deo
 * \param x		posi��o x
 * \param y		posi��o y
 */
void videoAdcObj (Video *v, VideoObj *o, int x, int y);

/**
 * Remove objeto de v�deo da lista de objetos da janela
 * 
 * \param v		v�deo
 * \param o		objeto de v�deo
 */
void videoRemObj (Video *v, VideoObj *o);

/**
 * Movimenta objeto de v�deo na janela
 * 
 * \param v		v�deo
 * \param o		objeto de v�deo
 * \param x		posi��o x
 * \param y		posi��o y
 */
void videoObjMove (Video *v, VideoObj *o, int x, int y);

/**
 * Exibe conte�do da lista de objetos de v�deo na janela
 * 
 * \param v		v�deo
 */
void videoImprime (Video *v);
