#define INI_PATH "./var/ini/input/"

/*
 * estrutura de inimigo
 */
typedef struct Inimigo
{
	int    rotulo;
	int    posX;
	int    posY;
	int    tamX;
	int    tamY;
	int    dano;
	int    veloc;
	struct InimigoTrajeto *trajeto;
} Inimigo;


/*
 * estrutura de lista de inimigos
 */
typedef struct InimigoLista
{
	Inimigo *inimigo;
	struct InimigoLista *prox;
} InimigoLista;


/*
 * estrutura da lista de trajeto do inimigo
 */
typedef struct InimigoTrajeto
{
	char dir;
	struct InimigoTrajeto *prox;
	struct InimigoTrajeto *cab;
} InimigoTrajeto;


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
