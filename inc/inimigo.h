#define INI_FILES_PATH "./var/ini/input/"
#define MSG_ERR_FILE_INI_PATH "ERRO: Nao pode abrir a arquivo de entrada dos inimigos"

/*
 * estrutura da lista de trajeto do inimigo
 */
typedef struct inimigoTrajeto
{
	char dir;
	struct inimigoTrajeto *prox;
	struct inimigoTrajeto *cab;
} InimigoTrajeto;


/*
 * estrutura de inimigo
 */
typedef struct inimigo
{
	int    rotulo;
	int    posX;
	int    posY;
	int    tamX;
	int    tamY;
	int    dano;
	int    veloc;
	struct inimigoTrajeto *trajeto;
} Inimigo;


/*
 * estrutura de lista de inimigos
 */
typedef struct inimigoLista
{
	struct inimigo *inimigo;
	struct inimigoLista *prox;
} InimigoLista;

/*
 * protótipos
 */

/**
 * cria um inimigo
 * \return		inimigo
 */
Inimigo *inimigoCria (void);

/**
 * destrói um inimigo
 * \param p		inimigo
 */
void inimigoDestroi (Inimigo *i);

/**
 * cria uma lista de inimigos
 * \param i		inimigo
 * \return		lista de inimigos
 */
InimigoLista *inimigoListaCria (Inimigo *i);

/**
 * destroi uma lista de inimigos
 * \param l		lista de inimigos
 */
void inimigoListaDestroi (InimigoLista *l);

/**
 * cria um trajeto de inimigo
 * \return		trajeto
 */
InimigoTrajeto *inimigoTrajetoCria (void);

/**
 * destrói um trajeto de inimigo
 * \param t		trajeto
 */
void inimigoTrajetoDestroi (InimigoTrajeto *t);

/**
 * carrega uma lista de inimigos a partir de um arquivo 
 * \param a		arquivo de inicialização
 * \return		inimigo
 */
InimigoLista *inimigoListaCarrega (char* a);

/**
 * coordena a movimentação do inimigo através do trajeto
 * \param p		inimigo
 */
void inimigoMove (Inimigo *i);
