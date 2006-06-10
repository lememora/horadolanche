#define PER_FILES_PATH "./var/per/input/per.txt"

/* intervalos de energia e sa�de do personagem */
#define PER_ENERG_MIN    0
#define PER_ENERG_DESNUT 1000
#define PER_ENERG_NORMAL 2000
#define PER_ENERG_MAX    4000

/* rela��o de massa e energia (1[kg] = x[kcal]) -- hipot�tico */
#define PER_MASSA_ENERG 20

/* velocidades de movimento em m/s */
#define PER_VEL_MAX 2
#define PER_VEL_MIN 1

/* consumo de energia em kcal de um corpo com 
 * massa 1kg com velocidade 1m/s durante 3600 segundos */
#define PER_CONS_ENERG_MOV 1000 / 3600

/* consumo de energia em kcal de um corpo com
 * massa 1kg com velocidade de 0m/s (repouso) durante 3600 segundos */
#define PER_CONS_ENERG_REP 250 / 3600

/* define sa�de do personagem */
#define PER_SAUDE_DESNUT 0
#define PER_SAUDE_NORMAL 1
#define PER_SAUDE_OBESO  2

/* define caracteres das dire��es de movimento */
#define MOV_DIR_CIMA     'c'
#define MOV_DIR_DIREITA  'd'
#define MOV_DIR_BAIXO    'b'
#define MOV_DIR_ESQUERDA 'e'
#define MOV_DIR_NULL     '-'

#define PER_PATH ".var/per/input/1.txt"


/*
 * estrutura do personagem
 */
typedef struct Personagem
{
	int    posX;
	int    posY;
	char   dir;
	float  energia;
} Personagem;


/*
 * prot�tipos
 */

/**
 * cria um personagem
 * \param x		posi��o x do personagem
 * \param y		posi��o y do personagem
 * \param d		dire��o de movimento do personagem
 * \param e		energia do personagem
 * \return		personagem
 */
Personagem *personagemCria (int x, int y, char d, float e);

/**
 * destr�i um personagem
 * \param p		personagem
 */
void personagemDestroi (Personagem *p);

/**
 * cria um personagem a partir de um arquivo de inicializa��o
 * \parap a		arquivo de inicializa��o
 * \return		personagem
 */
Personagem *personagemCarrega (char* a);

/**
 * obt�m a massa do personagem
 * \param p		personagem
 * \return		massa do personagem em kg
 */
int personagemMassa (Personagem *p);

/**
 * obt�m a velocidade do personagem
 * \param p		personagem
 * \return		velocidade do personagem em m/s
 */
int personagemVel (Personagem *p);

/**
 * retorna sa�de do personagem
 * \param p		personagem
 * \return		sa�de do personagem (desnutrido, normal ou obeso)
 */
int personagemSaude (Personagem *p);

/**
 * coordena a movimenta��o do personagem e o consumo de energia
 * deve ser utilizada mesmo quando n�o h� movimento (d == MOV_DIR_NULL)
 * pois realiza o consumo de energia vital
 * \param p		personagem
 * \param d		dire��o do movimento
 */
void personagemMove (Personagem *p, char d);

/**
 * recupera a energia de um personagem
 * \param p		personagem
 * \param r		energia fornecida para recupera��o
 */
void personagemRecupera (Personagem *p, float r);

/**
 * define a condi��o f�sica um personagem (se est� gordo ou magro)
 * \param p		personagem
 * \param r		energia fornecida para recupera��o
 */
int aparenciaPersonagem(Personagem* p);

/**
 * Tira energia do personagem de acordo com o dano do inimigo em contato
 * \param Quantidade de dano que o inimigo da 
 * \param personagem principal
 **/  
void dano (int dano,Personagem *personagem);
