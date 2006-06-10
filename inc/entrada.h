/*Estrutura que tem uma thread interna que le os eventos do teclado e guarda a tecla apertada, caso ela 
seja uma tecla valida*/


typedef struct Teclado
{
 SDL_Thread *thread;
 char tecla;
} Teclado;


/*
 * 	
 */
Personagem* leArquivo (char *arq, int *tempo, int *n);

/* faz a escrita do arquivo de dados de saída com as informações
   atualizadas sobre os personagens */
void escreveArquivo (Personagem *lista, char *saida, int tempo, int n);

/**
 * Cria uma estrutura teclado com seus valores default  e também cria uma thread
 * que executara o tecladoThread
 */
Teclado *tecladoCria ();

/**
 * Destroi a estrutura Teclado e o thread relacionado a ele
 * \param t	ponteiro para a estrutura teclado
 */
void tecladoDestroi (Teclado* t);

/**
 *Thread executada que le os eventos do teclado e passa a informação para o main atraves 
 *da variavel teclado
 */
int tecladoThread (void *args);

