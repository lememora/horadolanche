#define VIDEOX 800
#define VIDEOY 600
#define COLOR_PALLETE 16

/* define a localização dos arquivos de imagem do jogo */
#define IMG_CEN_PATH "./var/cen/img/"
#define PER_IMG_PATH "./var/per/img/Personagem.png"
#define INI_IMG_PATH "./var/ini/img/"


/** 
 * \todo
 * É preciso corrigir os rastros que aparecem na tela durante o movimento
 * e animação de sprites na tela. Isto pode estar sendo ocasionado pelo
 * constante interrupmento de threads durante a troca de intervalo de animações
 */


/** 
 * \struct VideoObj
 * 
 * \brief Estrutura de objeto de vídeo.
 *
 * Os objetos de vídeo são responsáveis por armazenar os sprites de
 * objetos e animações que serão exibidos na tela.
 * 
 */
typedef struct VideoObj {
	int          posX;         /**< posição x */
	int          posY;         /**< posição y */
	SDL_Rect     quadro;       /**< quadro de corte da imagem */
	SDL_Surface *imagem;       /**< imagem */
	int          indice;       /**< índice de posição do quadro */
	SDL_Thread  *ani_thread;   /**< thread de animação */
	int          ani_ativa;    /**< atividade de animação */
	int          ani_indice_i; /**< índice inicial do intervalo de animação */
	int          ani_indice_f; /**< índice final do intervalo de animação */
	int          ani_delay;    /**< delay da animação */
} VideoObj;

/**
 * \struct VideoObjLista
 * 
 * \brief Estrutura de lista de objetos de vídeo.
 *
 */
typedef struct VideoObjLista
{
	VideoObj             *vobj; /* objeto de vídeo */
	struct VideoObjLista *prox; /* próximo membro da estrutura */
} VideoObjLista;


/** 
 * Cria um objeto de vídeo.
 *
 * \param a		arquivo de imagem
 * \param l		largura do quadro
 * \param a		altura do quadro
 * \return		objeto de vídeo
 */
VideoObj *videoObjCria (char *a, int w, int h);

/**
 * Destrói um objeto de vídeo. 
 * 
 * \param o		objeto de vídeo
 */
void videoObjDestroi (VideoObj *o);

/** 
 * Define cor de transparência de um objeto de vídeo.
 *
 * \param o		objeto de vídeo
 * \param r		valor para cor vermelha
 * \param g		valor para cor verde
 * \param b		valor para cor azul
 */
void videoObjTrans (VideoObj *o, int r, int g, int b);

/**
 * Define o índice de posição do quadro.
 *
 * \param o		objeto de vídeo
 * \param i		índice de posição do quadro
 */
void videoObjIndice (VideoObj *o, int i);

/**
 * Avança para o próximo índice de posição do quadro. 
 *
 * \param o		objeto de vídeo
 */
void videoObjIndiceProx (VideoObj *o);

/**
 * Retorna ao índice anterior de posição do quadro.
 * 
 * \param o		objeto de vídeo
 */
void videoObjIndiceAnt (VideoObj *o);

/**
 * Define delay de animação de um objeto de vídeo. 
 *
 * \param o		objeto de vídeo
 * \param d		delay da animação
 */
void videoObjAniDelay (VideoObj *o, int d);

/**
 * Define o intervalo de animação de um objeto de vídeo. 
 * 
 * \param o		objeto de vídeo
 * \param i		índice de posição inicial do quadro
 * \param f		índice de posição final do quadro
 */
void videoObjAniIntervalo (VideoObj *o, int i, int f);

/**
 * Função para thread de animação de um objeto de vídeo.
 * 
 * \param o		objeto de vídeo (objeto de vídeo c/ casting p/ void)
 * \return		inteiro nulo
 */
int videoObjAniThread (void *o);

/**
 * Inicia a animação de um objeto de vídeo.
 * 
 * \param o		objeto de vídeo
 */
void videoObjAniInicia (VideoObj *o);

/**
 * Termina a animação de um objeto de vídeo.
 *
 * \param o		objeto de vídeo
 */
void videoObjAniTermina (VideoObj *o);

/**
 * Cria um elemento para a lista de objetos de vídeo.
 * 
 * \param o		objeto de vídeo
 * \return		elemento da lista de objetos de vídeo
 */
VideoObjLista *videoObjListaCria (VideoObj *o);

/**
 * Destrói lista de objetos de vídeo.
 *  
 * \param l		primeiro elemento da lista de objetos de vídeo
 */
void videoObjListaDestroi (VideoObjLista *l);


/**
 * \struct Video
 * 
 * \brief Estrutura da janela de vídeo.
 *
 * A janela de vídeo é composta por três camadas (Janela, fundo e 
 * lista de objetos de vídeo). A Janela é a moldura no gerenciador 
 * gráfico, o fundo é o objeto de vídeo utilizado para cobrir atualizações
 * da lista de objetos de vídeo e a lista de objetos de vídeo contém os
 * sprites que serão exibidos/animados na tela.
 * 
 */
typedef struct Video
{
	SDL_Surface   *video;    /* vídeo */
	VideoObj      *fundo;    /* objeto de vídeo para imagem de fundo */
	VideoObjLista *vobj_lst; /* lista de objetos de vídeo */
} Video;

/**
 * Cria janela de vídeo
 * 
 * \param l		largura
 * \param a		altura
 * \param c		número de cores
 * \return		vídeo
 */
Video *videoCria (int l, int a, int c);

/**
 * Destrói janela de vídeo
 * 
 * \param v		vídeo
 */
void videoDestroi (Video *v);

/**
 * Define o objeto de fundo da janela de vídeo.
 * 
 * \param v		vídeo
 * \param o		objeto de vídeo
 */
void videoFundo (Video *v, VideoObj *o);

/**
 * Adiciona objeto de vídeo à lista de objetos da janela
 * 
 * \param v		vídeo
 * \param o		objeto de vídeo
 * \param x		posição x
 * \param y		posição y
 */
void videoAdcObj (Video *v, VideoObj *o, int x, int y);

/**
 * Remove objeto de vídeo da lista de objetos da janela
 * 
 * \param v		vídeo
 * \param o		objeto de vídeo
 */
void videoRemObj (Video *v, VideoObj *o);

/**
 * Movimenta objeto de vídeo na janela
 * 
 * \param v		vídeo
 * \param o		objeto de vídeo
 * \param x		posição x
 * \param y		posição y
 */
void videoObjMove (Video *v, VideoObj *o, int x, int y);

/**
 * Exibe conteúdo da lista de objetos de vídeo na janela
 * 
 * \param v		vídeo
 */
void videoImprime (Video *v);
