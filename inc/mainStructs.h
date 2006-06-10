/* Mensagens de erro das funções de alocação de estruturas do main  */
#define MSG_ERR_CenarioObjCria "ERRO: Nao pode alocar memoria para a estrutura CenarioObj"
#define MSG_ERR_PersonagemObjCria "ERRO: Nao pode alocar memoria para a estrutura PersonagemObj"
#define MSG_ERR_AlimentoObjListaCria "ERRO: Nao pode alocar memoria para a estrutura AlimentoObjLista"
#define MSG_ERR_AlimentoObjCria "ERRO: Nao pode alocar memoria para a estrutura AlimentoObj"
#define MSG_ERR_NivelObjCria "ERRO: Nao pode alocar memoria para a estrutura NivelObj"
#define MSG_ERR_NivelObjListaCria "ERRO: Nao pode alocar memoria para a estrutura NivelObjLista"

/**
 * \struct CenarioObj
 * \brief objeto cenário
 */
typedef struct CenarioObj
{
	VideoObj        *videoObj;
	Cenario         *cenario;
}  CenarioObj;
 
/**
 * \struct PersonagemObj
 * \brief objeto personagem
 */
typedef struct PersonagemObj
{
	VideoObj        *videoObj;
	Personagem      *personagem;
}  PersonagemObj;

/**
 * \struct InimigoObj
 * \brief objeto inimigo
 */
typedef struct InimigoObj
{
	VideoObj        *videoObj;
	Inimigo         *inimigo;
}  InimigoObj;

/**
 * \struct InimigoObjLista
 * \brief lista de objetos inimigo
 */
typedef struct InimigoObjLista
{
	InimigoObj                  *inimigoObj;
	struct InimigoObjLista      *prox;
}  InimigoObjLista;

/**
 * \struct AlimentoObj
 * \brief objeto alimento
 */
typedef struct AlimentoObj
{
	VideoObj        *videoObj;
	Alimento        *alimento;
}  AlimentoObj;

/**
 * \struct AlimentoObjLista
 * \brief lista de objetos alimento
 */
typedef struct AlimentoObjLista
{
	AlimentoObj              *alimentoObj;
	struct AlimentoObjLista  *prox;
}  AlimentoObjLista;

/**
 * \struct NivelObj
 * \brief objeto nível
 */
typedef struct NivelObj
{
	CenarioObj      *cenarioObj;
	PersonagemObj   *personagemObj;
	InimigoObjLista *inimigoObjLista;
	AlimentoObjLista   *alimentoObjLista;
}  NivelObj;

/**
 * \struct NivelObjLista
 * \brief lista de objetos nível
 */
typedef struct NivelObjLista
{
	int				 		*rotulo; /*Mostra o nivel a ser carregado*/ 
	NivelObj             *nivelObj;
	struct NivelObjLista *prox;
	struct NivelObjLista *ant;
}  NivelObjLista; 
