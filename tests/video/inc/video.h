#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>


/** 
 * estrutura de objeto de v�deo 
 */
typedef struct VideoObj {
	int          posX;         /* posi��o x */
	int          posY;         /* posi��o y */
	SDL_Rect     quadro;       /* quadro de corte da imagem */
	SDL_Surface *imagem;       /* imagem */
	int          indice;       /* �ndice de posi��o do quadro */
	SDL_Thread  *ani_thread;   /* thread de anima��o */
	int          ani_ativa;    /* atividade de anima��o */
	int          ani_indice_i; /* �ndice inicial do intervalo de anima��o */
	int          ani_indice_f; /* �ndice final do intervalo de anima��o */
	int          ani_delay;    /* delay da anima��o */
} VideoObj;

/**
 * lista de estruturas de objetos de v�deo
 */
typedef struct VideoObjLista {
	VideoObj             *vobj; /* objeto de v�deo */
	struct VideoObjLista *prox; /* pr�ximo membro da estrutura */
} VideoObjLista;


/** 
 * cria um objeto de v�deo 
 * \param a		arquivo de imagem
 * \param l		largura do quadro
 * \param a		altura do quadro
 * \return		objeto de v�deo
 */
VideoObj *videoObjCria (char *a, int w, int h);

/**
 * destr�i um objeto de v�deo 
 * \param o		objeto de v�deo
 */
void videoObjDestroi (VideoObj *o);

/** 
 * define cor de transpar�ncia de um objeto de v�deo 
 * \param o		objeto de v�deo
 * \param r		valor para cor vermelha
 * \param g		valor para cor verde
 * \param b		valor para cor azul
 */
void videoObjTrans (VideoObj *o, int r, int g, int b);

/**
 * define o �ndice de posi��o do quadro
 * \param o		objeto de v�deo
 * \param i		�ndice de posi��o do quadro
 */
void videoObjIndice (VideoObj *o, int i);

/**
 * avan�a para o pr�ximo �ndice de posi��o do quadro 
 * \param o		objeto de v�deo
 */
void videoObjIndiceProx (VideoObj *o);

/**
 * retorna ao �ndice anterior de posi��o do quadro 
 * \param o		objeto de v�deo
 */
void videoObjIndiceAnt (VideoObj *o);

/**
 * define delay de anima��o de um objeto de v�deo 
 * \param o		objeto de v�deo
 * \param d		delay da anima��o
 */
void videoObjAniDelay (VideoObj *o, int d);

/**
 * define o intervalo de anima��o de um objeto de v�deo 
 * \param o		objeto de v�deo
 * \param i		�ndice de posi��o inicial do quadro
 * \param f		�ndice de posi��o final do quadro
 */
void videoObjAniIntervalo (VideoObj *o, int i, int f);

/**
 * fun��o para thread de anima��o de um objeto de v�deo 
 * \param o		objeto de v�deo (objeto de v�deo c/ casting p/ void)
 * \return		inteiro nulo
 */
int videoObjAniThread (void *o);

/**
 * inicia a anima��o de um objeto de v�deo 
 * \param o		objeto de v�deo
 */
void videoObjAniInicia (VideoObj *o);

/**
 * termina a anima��o de um objeto de v�deo 
 * \param o		objeto de v�deo
 */
void videoObjAniTermina (VideoObj *o);

/**
 * cria um elemento para a lista de objetos de v�deo 
 * \param o		objeto de v�deo
 * \return		elemento da lista de objetos de v�deo
 */
VideoObjLista *videoObjListaCria (VideoObj *o);

/**
 * destr�i lista de objetos de v�deo 
 * \param l		primeiro elemento da lista de objetos de v�deo
 */
void videoObjListaDestroi (VideoObjLista *l);


/**
 * estrutura da janela de v�deo
 */
typedef struct Video {
	SDL_Surface   *video;    /* v�deo */
	VideoObj      *fundo;    /* objeto de v�deo para imagem de fundo */
	VideoObjLista *vobj_lst; /* lista de objetos de v�deo */
} Video;

/**
 * cria janela de v�deo
 * \param l		largura
 * \param a		altura
 * \param c		n�mero de cores
 * \return		v�deo
 */
Video *videoCria (int l, int a, int c);

/**
 * destr�i janela de v�deo
 * \param v		v�deo
 */
void videoDestroi (Video *v);

/**
 * define o objeto de fundo da janela de v�deo.
 * \param v		v�deo
 * \param o		objeto de v�deo
 */
void videoFundo (Video *v, VideoObj *o);

/**
 * adiciona objeto de v�deo � lista de objetos da janela
 * \param v		v�deo
 * \param o		objeto de v�deo
 * \param x		posi��o x
 * \param y		posi��o y
 */
void videoAdcObj (Video *v, VideoObj *o, int x, int y);

/**
 * remove objeto de v�deo da lista de objetos da janela
 * \param v		v�deo
 * \param o		objeto de v�deo
 */
void videoRemObj (Video *v, VideoObj *o);

/**
 * movimenta objeto de v�deo na janela
 * \param v		v�deo
 * \param o		objeto de v�deo
 * \param x		posi��o x
 * \param y		posi��o y
 */
void videoMovObj (Video *v, VideoObj *o, int x, int y);

/**
 * exibe conte�do da lista de objetos de v�deo na janela
 * \param v		v�deo
 */
void videoImprime (Video *v);
