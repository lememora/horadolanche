#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* define a localização dos arquivos de imagem do cenario */
#define CENARIO_PATH "./var/cen/img/Cenario1.png"
#define FILEIN_CEN_PATH "./var/def.txt"
#define FILEMATRIZ_CEN_PATH "./var/"
/* relação de distancia e tamanho na tela (1[m] = x[pixel]) */
#define CEN_DIST_PIXEL 10

/* relação de escala entre a matriz de cenario e o tamanho da tela*/
#define CEN_ESCALA_PIXEL 20

/* define os tipos de transponibilidade da célula do cenário */
#define CAMINHO_LIVRE 0
#define CAMINHO_BLOQUEADO '#'
#define SAIDA 'S'
#define ENTRADA 'E'

/* defines de uso */
#define MSG_ERR_NUMARG_CEN "Numero de argumentos insuficiente"
#define MSG_USO_CENARIO " -i <entrada> -m <matriz>-o <saida>"
#define MSG_ERR_FILEIN_CEN "ERRO: Arquivo de leitura do cenario nao pode ser aberto"
#define MSG_ERR_FILEOUT_CEN "ERRO: Arquivo de escrita do cenario nao pode ser aberto"
#define MSG_ERR_SINT_FILE_IN_CEN "ERRO: Sintaxe do arquivo de leitura de cenario incompleto"
#define MSG_ERR_CRIAELEM "hlcenario_cria_elem malloc error"
#define MSG_ERR_CRIACELCEN "Constroi_Matriz malloc error"

/**
 * estrutura de lista quadruplamente ligada 
 */
typedef struct hlcenario_celula_cen {

	char tipo;
	int X;
	int Y;
	int W;
	int H;
	struct hlcenario_celula_cen* cima;
	struct hlcenario_celula_cen* baixo;
	struct hlcenario_celula_cen* esq;
	struct hlcenario_celula_cen* dir;
} hlcenario_celula_cen;

/**
 * estrutura de lista unicamente ligada 
 */
typedef struct elem {
	
	char simb;
	int def;
	struct elem* prox; 
} elem;


/**
  * le um arquivo de entrada e retira dados "default"
  * a respeito da matriz de entrada
  * \param arq
  * \return void
  */
void 	hlcenario_leArquivo		(char* arq,int *linhas,int *colunas);

/**
  * escreve um arquivo de entrada e constroi uma lista 
  * "quadruplamente ligada" em forma de matriz
  * \param arq
  * \param matriz
  * \return void
  */ 
void	hlcenario_escreveArquivo	(char* arq, hlcenario_celula_cen* matriz);

/**
  * le um arquivo de entrada e constroi uma lista 
  * "quadruplamente ligada" em forma de matriz
  * \param arq
  * \return void
  */
void hlcenario_leMatriz(char* arq, hlcenario_celula_cen* matriz);


/**
  * cria uma lista "quadruplamente ligada" em forma de matriz
  * \param linhas
  * \param colunas
  * \return ponteiro para a primeira celula da matriz
*/
hlcenario_celula_cen*	constroi_Matriz	(int lin,int col);

/**
 *
 */
void hlcenario_insere_na_Matriz(hlcenario_celula_cen* pontq,hlcenario_celula_cen* pontr);

/**
 * cria um elemento de lista quadruplamente ligada
 * \return celula com 4 apontadores 
 */
hlcenario_celula_cen* criahlcenario_celula_cen();

/**
 *
 */
void hlcenario_insere_na_lista(elem* pontp, char simbolo);

/**
 * cria um elemento de lista ligada
 * \return celula com 1 apontador
 */
elem* hlcenario_cria_elem();
