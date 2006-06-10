#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>

#include "video.h"
#include "personagem.h"
#include "cenario.h"
#include "inimigo.h"
#include "alimento.h"
#include "entrada.h"
#include "mainStructs.h"
#include "mainColisao.h"
#include "mainAnimacao.h"


enum { FALSE, TRUE };

#define FPS 30
#define NUM_NIVEIS 1

/* Fun��es do m�dulo Main */

/**
 * tela inicial
 */
void inicio (Video *video, Teclado *teclado);

/**
 * tela de jogo
 */
void jogo (Video *video, Teclado *teclado, NivelObjLista *nivelObjLista);

/**
 * tela final
 */
void fim (Video *video, Teclado *teclado);

/**
 * carrega a lista com todos os n�veis
 */
NivelObjLista *NivelObjListaCarrega (Video *v);

/**
 * destr�i a lista com todos os n�veis
 */
void NivelObjListaDestroi (NivelObjLista *o);

/**
 * sincroniza a verosimilhan�a entre as informa��es
 * de v�deo e dados da estrutura de objeto personagem
 */
int PersonagemObjSinc (Video* v,PersonagemObj *o);

/**
 * sincroniza a verosimilhan�a entre as informa��es
 * de v�deo e dados da estrutura de objeto inimigo 
 */
int InimigoObjSinc (InimigoObj *o);

/**
 * sincroniza a verosimilhan�a entre as informa��es
 * de v�deo e dados da estrutura de objeto alimento 
 */
int AlimentoObjSinc (AlimentoObj *o);

/**
 * cria um objeto cen�rio
 */
CenarioObj* CenarioObjCria (Video* v,int nivel);

/**
 * destroi um objeto cen�rio
 */
void CenarioObjDestroi (CenarioObj *o);

/**
 * cria um objeto personagem
 */
PersonagemObj* PersonagemObjCria(Video* v);

/**
 * destroi um objeto personagem
 */
void PersonagemObjDestroi (PersonagemObj *o);

/**
 * cria um objeto InimigoObj
 */
InimigoObj* InimigoObjCria(Video* v,int nivel,Inimigo* inim);

/**
 * cria uma lista de objetos inimigo
 */
InimigoObjLista* InimigoObjListaCria (Video* v,int num_nivel,Inimigo* ini);

/**
 * destroi uma lista de objetos inimigo
 */
void InimigoObjListaDestroi (InimigoObjLista *l);

/**
 * cria uma lista de objetos alimento
 */
AlimentoObjLista* alimentoObjListaCria (char *arqDados);

/**
 * destroi uma lista de objetos alimento
 */
void AlimentoObjListaDestroi (AlimentoObjLista *l);

/**
 * Ajusta todas as propriedades de video de um objeto
 */
VideoObj* VideoObjSetaAtributos_IMG (char* path);


