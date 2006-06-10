#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>


/** 
 * estrutura de objeto de vídeo 
 */
typedef struct VideoObj {
	int          posX;         /* posição x */
	int          posY;         /* posição y */
	SDL_Rect     quadro;       /* quadro de corte da imagem */
	SDL_Surface *imagem;       /* imagem */
	int          indice;       /* índice de posição do quadro */
	SDL_Thread  *ani_thread;   /* thread de animação */
	int          ani_ativa;    /* atividade de animação */
	int          ani_indice_i; /* índice inicial do intervalo de animação */
	int          ani_indice_f; /* índice final do intervalo de animação */
	int          ani_delay;    /* delay da animação */
} VideoObj;

/**
 * lista de estruturas de objetos de vídeo
 */
typedef struct VideoObjLista {
	VideoObj             *vobj; /* objeto de vídeo */
	struct VideoObjLista *prox; /* próximo membro da estrutura */
} VideoObjLista;


/** 
 * cria um objeto de vídeo 
 * \param a		arquivo de imagem
 * \param l		largura do quadro
 * \param a		altura do quadro
 * \return		objeto de vídeo
 */
VideoObj *videoObjCria (char *a, int w, int h);

/**
 * destrói um objeto de vídeo 
 * \param o		objeto de vídeo
 */
void videoObjDestroi (VideoObj *o);

/** 
 * define cor de transparência de um objeto de vídeo 
 * \param o		objeto de vídeo
 * \param r		valor para cor vermelha
 * \param g		valor para cor verde
 * \param b		valor para cor azul
 */
void videoObjTrans (VideoObj *o, int r, int g, int b);

/**
 * define o índice de posição do quadro
 * \param o		objeto de vídeo
 * \param i		índice de posição do quadro
 */
void videoObjIndice (VideoObj *o, int i);

/**
 * avança para o próximo índice de posição do quadro 
 * \param o		objeto de vídeo
 */
void videoObjIndiceProx (VideoObj *o);

/**
 * retorna ao índice anterior de posição do quadro 
 * \param o		objeto de vídeo
 */
void videoObjIndiceAnt (VideoObj *o);

/**
 * define delay de animação de um objeto de vídeo 
 * \param o		objeto de vídeo
 * \param d		delay da animação
 */
void videoObjAniDelay (VideoObj *o, int d);

/**
 * define o intervalo de animação de um objeto de vídeo 
 * \param o		objeto de vídeo
 * \param i		índice de posição inicial do quadro
 * \param f		índice de posição final do quadro
 */
void videoObjAniIntervalo (VideoObj *o, int i, int f);

/**
 * função para thread de animação de um objeto de vídeo 
 * \param o		objeto de vídeo (objeto de vídeo c/ casting p/ void)
 * \return		inteiro nulo
 */
int videoObjAniThread (void *o);

/**
 * inicia a animação de um objeto de vídeo 
 * \param o		objeto de vídeo
 */
void videoObjAniInicia (VideoObj *o);

/**
 * termina a animação de um objeto de vídeo 
 * \param o		objeto de vídeo
 */
void videoObjAniTermina (VideoObj *o);

/**
 * cria um elemento para a lista de objetos de vídeo 
 * \param o		objeto de vídeo
 * \return		elemento da lista de objetos de vídeo
 */
VideoObjLista *videoObjListaCria (VideoObj *o);

/**
 * destrói lista de objetos de vídeo 
 * \param l		primeiro elemento da lista de objetos de vídeo
 */
void videoObjListaDestroi (VideoObjLista *l);


/**
 * estrutura da janela de vídeo
 */
typedef struct Video {
	SDL_Surface   *video;    /* vídeo */
	VideoObj      *fundo;    /* objeto de vídeo para imagem de fundo */
	VideoObjLista *vobj_lst; /* lista de objetos de vídeo */
} Video;

/**
 * cria janela de vídeo
 * \param l		largura
 * \param a		altura
 * \param c		número de cores
 * \return		vídeo
 */
Video *videoCria (int l, int a, int c);

/**
 * destrói janela de vídeo
 * \param v		vídeo
 */
void videoDestroi (Video *v);

/**
 * define o objeto de fundo da janela de vídeo.
 * \param v		vídeo
 * \param o		objeto de vídeo
 */
void videoFundo (Video *v, VideoObj *o);

/**
 * adiciona objeto de vídeo à lista de objetos da janela
 * \param v		vídeo
 * \param o		objeto de vídeo
 * \param x		posição x
 * \param y		posição y
 */
void videoAdcObj (Video *v, VideoObj *o, int x, int y);

/**
 * remove objeto de vídeo da lista de objetos da janela
 * \param v		vídeo
 * \param o		objeto de vídeo
 */
void videoRemObj (Video *v, VideoObj *o);

/**
 * movimenta objeto de vídeo na janela
 * \param v		vídeo
 * \param o		objeto de vídeo
 * \param x		posição x
 * \param y		posição y
 */
void videoMovObj (Video *v, VideoObj *o, int x, int y);

/**
 * exibe conteúdo da lista de objetos de vídeo na janela
 * \param v		vídeo
 */
void videoImprime (Video *v);
