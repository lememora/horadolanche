#define FILES_CEN_PATH "./var/cen/input/"


/* relação de distancia e tamanho na tela (1[m] = x[pixel]) */
#define CEN_DIST_PIXEL 10

/* relação de escala entre a matriz de Cenario e o tamanho da tela*/
#define CENARIO_CEL_TAM_PIXEL 20

/* define os tipos de transponibilidade da célula do cenário */
#define CAMINHO_LIVRE '0'
#define CAMINHO_BLOQUEADO '#'
#define SAIDA 'S'
#define ENTRADA 'E'

/* defines de uso */
#define MSG_ERR_NUMARG_CEN "Numero de argumentos insuficiente"
#define MSG_USO_Cenario " -i <entrada> -m <matriz>-o <saida>"
#define MSG_ERR_FILEIN_CEN "ERRO: Arquivo de leitura do Cenario nao pode ser aberto"
#define MSG_ERR_FILEOUT_CEN "ERRO: Arquivo de escrita do Cenario nao pode ser aberto"
#define MSG_ERR_SINT_FILE_IN_CEN "ERRO: Sintaxe do arquivo de leitura de Cenario incompleto"
#define MSG_ERR_CRIAELEM "Cenario_cria_elem malloc error"
#define MSG_ERR_CRIACELCEN "Constroi_Matriz malloc error"


/**
 * \brief estrutura de lista quadruplamente ligada 
 */
typedef struct Cenario {

	char tipo;
	int X;
	int Y;	
	struct Cenario* cima;
	struct Cenario* baixo;
	struct Cenario* esq;
	struct Cenario* dir;
} Cenario;

/**
  * le um arquivo de entrada e retira dados "default"
  * a respeito da matriz de entrada
  * \param arq
  * \return void
  */
void 	Cenario_leArquivo		(char* arq,int *linhas,int *colunas);

/**
  * escreve um arquivo de entrada e constroi uma lista 
  * "quadruplamente ligada" em forma de matriz
  * \param arq
  * \param matriz
  * \return void
  */ 
void	Cenario_escreveArquivo	(char* arq, Cenario* matriz);

/**
  * le um arquivo de entrada e constroi uma lista 
  * "quadruplamente ligada" em forma de matriz
  * \param arq
  * \return void
  */
void Cenario_leMatriz(char* arq, Cenario* matriz,int num_nivel);


/**
  * cria uma lista "quadruplamente ligada" em forma de matriz
  * \param linhas
  * \param colunas
  * \return ponteiro para a primeira celula da matriz
  */
Cenario*	constroi_Matriz	(int lin,int col);

/**
 * cria um elemento de lista quadruplamente ligada
 * \return celula com 4 apontadores 
 */
Cenario* criaCenario();

/**
 * De acordo com um par ordenado (x,y) devolve o apontador para a celula do Cenario
 * que tem Cenario->X=x e Cenario->y=y
 * \param posicao na horizontal
 * \param posicao na vertical 
 * \param uma celula do Cenario
 * \return ponteiro para a celula procurada
 */
Cenario *coordPonteiro(int x,int y,Cenario *cen);
