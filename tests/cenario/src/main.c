#include "cenario.h"
#define mostraXY

int main (int argc,char *argv[])
{
	int i;
	/* atributos da matriz */ 
	int linhas, colunas;

	char arqLeit[50];
	char arqResp[50];
	char arqMat[50];

	hlcenario_celula_cen* matriz = NULL;

	if(argc!=7)
     {
    		fprintf(stderr,"\n %s.Digite: %s %s", MSG_ERR_NUMARG_CEN,argv[0],MSG_USO_CENARIO);
			exit(1);
     }

	for(i=1;i<7;i++){           
    		if(argv[i][0]=='-')       
    			switch(argv[i][1])
    			{
    			case'i':
            		strcpy(arqLeit,argv[i+1]);
            		break;
							case'm':
            		strcpy(arqMat,argv[i+1]);
            		break;
				
    			case'o':
            		strcpy(arqResp,argv[i+1]);
            		break;
    			default:
            		fprintf(stderr,"%s",MSG_USO_CENARIO);
            		break;
    			}
    
    }
	
	hlcenario_leArquivo(arqLeit,&linhas,&colunas);
	matriz = constroi_Matriz(linhas,(colunas));
	hlcenario_leMatriz(arqMat, matriz);
	hlcenario_escreveArquivo(arqResp,matriz);	

	return(0);
}



int define_tipo(char caractere,elem* lista_simbolos)
{
	int tipo = -1;
	elem* p;

	for(p=lista_simbolos;p!=NULL;p=p->prox)	
		if(p->simb==caractere) 
		{
			tipo=p->def;
			break;
		}	

	return(tipo);
}

/** le um arquivo de entrada e constroi uma lista 
 * "quadruplamente ligada" em forma de matriz
 */
void hlcenario_leArquivo(char* arq,int *linhas,int *colunas)
{
	/* atributos da celula */	
	char caractere;

	FILE *fp = NULL; /* Ponteiro para o arquivo de leitura*/		
	
	if((fp=fopen(FILEIN_CEN_PATH,"r"))==NULL)
	{
		fprintf(stderr, "%s\n", MSG_ERR_FILEIN_CEN);
		exit (EXIT_FAILURE);
	}

	while(!feof(fp)) 
	{
		fscanf(fp,"%c",&caractere);
		switch(caractere){
			/* armazena dimensões da matriz */
			case 'w' : /* (size) */
				fscanf(fp,"\n%d",colunas);				
				break;

			case 'h':
				fscanf(fp,"\n%d",linhas);
				break;
		}	
	}
	
	fclose(fp);
	
}

void hlcenario_leMatriz(char* arq, hlcenario_celula_cen* matriz)
{
	int i = 0; /* contador */
	int j = 0; /* contador */ 
	int nivel = 1;
	hlcenario_celula_cen* p = NULL;
	hlcenario_celula_cen* q = NULL;
	FILE *fp = NULL; /* Ponteiro para o arquivo de leitura*/
	char caractere,nomearq[90];

	sprintf(nomearq,"%s%d.txt",FILEMATRIZ_CEN_PATH,nivel);

	if((fp=fopen(nomearq,"r"))==NULL)
	{
		fprintf(stderr, "\n%s\n%s\n", MSG_ERR_FILEIN_CEN,nomearq);
		exit (EXIT_FAILURE);
	}

	for(q=matriz; q!=NULL; q=q->baixo,i++){
		j=0;
		for(p=q; p!=NULL; p=p->dir,j++){
			fscanf(fp,"%c\n",&caractere);		
			p->tipo = caractere;
			p->X = j;
			p->Y = i;
			p->W = j;
			p->H = i;
		   }				   
		}				

}

void hlcenario_escreveArquivo (char* arq, hlcenario_celula_cen* matriz)
{	
	hlcenario_celula_cen* n = NULL;
	hlcenario_celula_cen* o = NULL;
	FILE *fp;

	if((fp=fopen(arq,"w"))==NULL)
	{
		fprintf(stderr, "%s\n", MSG_ERR_FILEOUT_CEN);
		exit (EXIT_FAILURE);
	}
	 						
	for(n=matriz;n!=NULL;n=n->baixo){						
		for(o=n;o->dir!=NULL;o=o->dir)
			fprintf(fp,"%c",o->tipo);
		fprintf(fp,"\n");			
		}
	fprintf(fp,"\n\n");

	for(n=o;n!=NULL;n=n->cima){						
		for(o=n;o->esq!=NULL;o=o->esq)
			fprintf(fp,"%c",o->tipo);
		fprintf(fp,"\n");			
		}
	fprintf(fp,"\n\n");

	for(n=matriz->dir->dir->dir->dir->dir;n->baixo!=NULL;n=n->baixo);
		for(o=n;o->cima!=NULL;o=o->cima)			
	fprintf(fp,"\n%d%d%c\n\n",o->W,o->H,o->tipo);
	for(n=matriz->dir->dir->dir->dir->dir;n!=NULL;n=n->esq) fprintf(fp,"%c",n->tipo);
 	
/*	for(n=n;n!=NULL;n=n->cima){						
		for(o=n;o!=NULL;o=o->esq)
			fprintf(fp,"%c",o->tipo);
		fprintf(fp,"\n");			
		}
	fprintf(fp,"\n\n");
*/	
#ifdef mostraXY		
	for(n=matriz;n!=NULL;n=n->baixo){		
		for(o=n;o!=NULL;o=o->dir) fprintf(fp," %d%d",o->W,o->H); 	
		fprintf(fp,"\n");
		}
#endif
	
}		
