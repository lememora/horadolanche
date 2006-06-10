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
 * prot�tipos
 */

/**
 * cria um inimigo
 * \return		inimigo
 */
Inimigo *inimigoCria (void);

/**
 * destr�i um inimigo
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
 * destr�i um trajeto de inimigo
 * \param t		trajeto
 */
void inimigoTrajetoDestroi (InimigoTrajeto *t);

/**
 * carrega uma lista de inimigos a partir de um arquivo 
 * \param a		arquivo de inicializa��o
 * \return		inimigo
 */
InimigoLista *inimigoListaCarrega (char* a);

/**
 * coordena a movimenta��o do inimigo atrav�s do trajeto
 * \param p		inimigo
 */
void inimigoMove (Inimigo *i);
