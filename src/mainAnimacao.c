#include "main.h"

void defineInterAni(NivelObj* nivel)
{
	PersonagemObj* p = nivel->personagemObj;	
	InimigoObjLista* i = nivel->inimigoObjLista;

	defineInterAniPersonagem(p);

	for(;i!=NULL;i=i->prox)	defineInterAniInimigo(i->inimigoObj);
}

void defineInterAniPersonagem(PersonagemObj* o){

	Personagem* p = o->personagem;
	VideoObj* pers = o->videoObj;

	if (aparenciaPersonagem(p) == PER_SAUDE_DESNUT ||
		 aparenciaPersonagem(p) == PER_SAUDE_NORMAL){		
			
			switch (p->dir) {
					case '1' :
						videoObjAniIntervalo (pers,  1,  1);
						break;
					case '2' :
						videoObjAniIntervalo (pers,  9,  9);
						break;
					case '3' :
						videoObjAniIntervalo (pers,  17, 17);
						break;
					case '4' :
						videoObjAniIntervalo (pers, 25, 25);
						break;
			
					case 'c' :
						videoObjAniIntervalo (pers,  0,  3);
						break;
					case 'd' :
						videoObjAniIntervalo (pers,  8,  11);
						break;
					case 'b' :
						videoObjAniIntervalo (pers,  16, 19);
						break;
					case 'e' :
						videoObjAniIntervalo (pers, 24, 27);
						break;
			}
		}		

		else if (aparenciaPersonagem(p) == PER_SAUDE_OBESO){
			switch (p->dir) {
					case '1' :
						videoObjAniIntervalo (pers,  5,  5);
						break;
					case '2' :
						videoObjAniIntervalo (pers,  13, 13);
						break;
					case '3' :
						videoObjAniIntervalo (pers,  21, 21);
						break;
					case '4' :
						videoObjAniIntervalo (pers, 29, 29);
						break;
		
					case 'c' :
						videoObjAniIntervalo (pers,  4,  7);
						break;
					case 'd' :
						videoObjAniIntervalo (pers, 12, 15);
						break;
					case 'b' :
						videoObjAniIntervalo (pers, 20, 23);
						break;
					case 'e' :
						videoObjAniIntervalo (pers, 28, 31);
						break;
			}			
		}
}

void defineInterAniInimigo(InimigoObj* o)
{
	Inimigo* p = o->inimigo;
	VideoObj* pers = o->videoObj;

		switch (p->trajeto->dir) {
			case '1' :
				videoObjAniIntervalo (pers,  5,  5);
				break;
			case '2' :
				videoObjAniIntervalo (pers,  13, 13);
				break;
			case '3' :
				videoObjAniIntervalo (pers,  21, 21);
				break;
			case '4' :
				videoObjAniIntervalo (pers, 29, 29);
				break;
		
			case 'c' :
				videoObjAniIntervalo (pers,  4,  7);
				break;
			case 'd' :
				videoObjAniIntervalo (pers, 12, 15);
				break;
			case 'b' :
				videoObjAniIntervalo (pers, 20, 23);
				break;
			case 'e' :
				videoObjAniIntervalo (pers, 28, 31);
				break;
		}			
}
