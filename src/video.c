#include "main.h"

/* 
 * Cria um objeto de vídeo 
 */
VideoObj *videoObjCria (char *a, int w, int h) 
{
	VideoObj *o = NULL;
	SDL_Surface *s = NULL;

	if (!(s = IMG_Load(a))) {
		fprintf (stderr, "%s\n", IMG_GetError ());
		exit (EXIT_FAILURE);
	}

	if (!(o = (VideoObj *) malloc (sizeof(VideoObj)))) {
		fprintf (stderr, "VideoObj malloc error\n");
		exit (EXIT_FAILURE);
	}

	o->imagem = SDL_DisplayFormat (s);
	SDL_FreeSurface (s);

	o->posX = 0;
	o->posY = 0;

	o->quadro.x = 0;
	o->quadro.y = 0;
	o->quadro.w = w;
	o->quadro.h = h;

	o->indice = 0;

	o->ani_thread = NULL;
	o->ani_ativa = 0;
	o->ani_indice_i = 0;
	o->ani_indice_f = 0;
	o->ani_delay = 0;

	return o;
}

/*
 * Destrói um objeto de vídeo 
 */
void videoObjDestroi (VideoObj *o)
{
	SDL_FreeSurface(o->imagem);
	if (o->ani_thread != NULL) {
		videoObjAniTermina (o);
	}
	free(o);
}

/*
 * Define cor de transparência de um objeto de vídeo 
 */
void videoObjTrans (VideoObj *o, int r, int g, int b)
{
	int c;
	c = SDL_MapRGB (o->imagem->format, r, g, b);
	SDL_SetColorKey (o->imagem, SDL_RLEACCEL|SDL_SRCCOLORKEY, c);
}

/*
 * Define o índice de posição do quadro
 */
void videoObjIndice (VideoObj *o, int i)
{
	int x, y, kw, kh;

	x = 0;
	y = 0;
	kw = o->imagem->w / o->quadro.w;
	kh = o->imagem->h / o->quadro.h;

	if (i < 0) {
		i = kw * kh + (i % (kw * kh));
	}

	if (kw > 0) {
		x = i % kw;
		y = i / kw;
	}

	y = y % kh;

	o->indice = x + y * kw;
	o->quadro.x = x * o->quadro.w;
	o->quadro.y = y * o->quadro.h;
}

/*
 * Avança para o próximo índice de posição do quadro 
 */
void videoObjIndiceProx (VideoObj *o)
{
	videoObjIndice (o, o->indice + 1);
}

/*
 * Retorna ao índice anterior de posição do quadro 
 */
void videoObjIndiceAnt (VideoObj *o)
{
	videoObjIndice (o, o->indice - 1);
}

/*
 * Define delay de animação de um objeto de vídeo 
 */
void videoObjAniDelay (VideoObj *o, int d)
{
	o->ani_delay = d;
}

/*
 * Define o intervalo de animação de um objeto de vídeo 
 */
void videoObjAniIntervalo (VideoObj *o, int i, int f)
{
	if (o->ani_indice_i != i || o->ani_indice_f != f) {
		o->ani_indice_i = i;
		o->ani_indice_f = f;
		if (o->ani_thread != NULL) {
			videoObjAniTermina (o);
			videoObjAniInicia (o);
		}
	}
}

/*
 * Função para thread de animação de um objeto de vídeo 
 */
int videoObjAniThread (void *o)
{
	int i;
	VideoObj *obj = (VideoObj *)(o);

	while (obj->ani_ativa > 0) {
		for (i = obj->ani_indice_i; i <= obj->ani_indice_f; i++) {
			videoObjIndice (obj, i);
			SDL_Delay (obj->ani_delay);
		}
	}
	return 0;
}

/*
 * Inicia a animação de um objeto de vídeo 
 */
void videoObjAniInicia (VideoObj *o)
{
	if (o->ani_ativa == 0) {
		o->ani_ativa = 1;
		o->ani_thread = SDL_CreateThread (videoObjAniThread, (void *)(o));
	}
}

/*
 * Termina a animação de um objeto de vídeo 
 */
void videoObjAniTermina (VideoObj *o)
{
	if (o->ani_ativa > 0) {
		o->ani_ativa = 0;
		SDL_KillThread (o->ani_thread);
	}
	o->ani_thread = NULL;
}

/*
 * Cria um elemento para a lista de objetos de vídeo 
 */
VideoObjLista *videoObjListaCria (VideoObj *o)
{
	VideoObjLista *l;

	if (!(l = (VideoObjLista *) malloc (sizeof(VideoObjLista)))) {
		fprintf (stderr, "VideoObjLista malloc error\n");
		exit (EXIT_FAILURE);
	}
                   
	l->vobj = o;
	l->prox = NULL;

	return l;
}

/*
 * Destrói lista de objetos de vídeo 
 */
void videoObjListaDestroi (VideoObjLista *l)
{
}

/*
 * Cria janela de vídeo
 */
Video *videoCria (int l, int a, int c)
{
	Video *v = NULL;

	if (!(v = (Video *) malloc (sizeof(Video)))) {
		fprintf (stderr, "Video malloc error\n");
		exit (EXIT_FAILURE);
	}

	if (SDL_Init (SDL_INIT_EVERYTHING) == -1) {
		fprintf (stderr, "%s\n", SDL_GetError());
		exit (EXIT_FAILURE);
	}

	atexit(SDL_Quit);

	if (SDL_VideoModeOK (l, a, c, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_NOFRAME)) {
		v->video = SDL_SetVideoMode (
			l, a, c, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_NOFRAME);
	} else {
		v->video = SDL_SetVideoMode (
			l, a, c, SDL_SWSURFACE|SDL_NOFRAME);
	}

	if (v->video == NULL) {
		fprintf (stderr, "%s\n", SDL_GetError());
		exit (EXIT_FAILURE);
	}

	v->vobj_lst = videoObjListaCria (NULL);
	v->fundo = NULL;

	return v;
}

/*
 * Destrói janela de vídeo
 */
void videoDestroi (Video *v)
{
	videoObjListaDestroi (v->vobj_lst);
}

/*
 * Define o objeto de fundo da janela de vídeo.
 */
void videoFundo (Video *v, VideoObj *o)
{
	v->fundo = o;

	SDL_BlitSurface (o->imagem, &o->quadro, v->video, &o->quadro);
	SDL_UpdateRect (v->video, o->quadro.x, o->quadro.y,
		o->quadro.w, o->quadro.h);
}

/*
 * Adiciona objeto de vídeo à lista de objetos da janela
 */
void videoAdcObj (Video *v, VideoObj *o, int x, int y)
{
	VideoObjLista *l = NULL;

	o->posX = x;
	o->posY = y;

	l = videoObjListaCria (o);
	l->prox = v->vobj_lst;
	v->vobj_lst = l;
}

/*
 * Remove objeto de vídeo da lista de objetos da janela
 */
void videoRemObj (Video *v, VideoObj *o)
{
}

/*
 * Movimenta objeto de vídeo na janela
 */
void videoObjMove (Video *v, VideoObj *o, int x, int y)
{
	VideoObjLista *l;
	SDL_Rect r;

	for (l = v->vobj_lst; l->prox != NULL; l = l->prox) {
		if (o == l->vobj) {
			r.x = l->vobj->posX;
			r.y = l->vobj->posY;
			r.w = l->vobj->quadro.w;
			r.h = l->vobj->quadro.h;

			l->vobj->posX = x;
			l->vobj->posY = y;

			if (v->fundo != NULL) {
				SDL_BlitSurface (v->fundo->imagem, &r, v->video, &r);
			} else {

				SDL_FillRect(
					v->video, &r, SDL_MapRGB (
						v->video->format, 0x00, 0x00, 0x00)
				); 
			}
		}
	}
}

/*
 * Exibe conteúdo da lista de objetos de vídeo na janela
 */
void videoImprime (Video *v)
{
	VideoObj *o;
	VideoObjLista *l;
	SDL_Rect r;

	for (l = v->vobj_lst; l->prox != NULL; l = l->prox) {
		o = l->vobj;

		r.x = o->posX;
		r.y = o->posY;
		r.w = o->quadro.w;
		r.h = o->quadro.h;

		SDL_BlitSurface (o->imagem, &o->quadro, v->video, &r);
		SDL_UpdateRect (v->video, r.x, r.y, r.w, r.h);
	}
}
