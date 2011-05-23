#include "ListaBalas.h"


ListaBalas::ListaBalas(void)
{
	indice = 0;
}

void ListaBalas::init(void){
	for(int i = 0; i < MAX_BALAS ; i++){

	}

}

void ListaBalas::addBala(GLdouble x, GLdouble y, GLdouble z, GLdouble ang){
	listaBalas[indice] = new Bala(x,y,z,ang);
	listaBalas[indice]->ok = true;
	incIndiceBalas();
}

void ListaBalas::incIndiceBalas(void){
	if(indice != MAX_BALAS-1) indice++;
	else indice = 0;
}

void ListaBalas::desenha(void){

	for(int i = 0 ; i < indice ; i++){
		float posX = listaBalas[i]->getPosicaoXX();
		float posY = listaBalas[i]->getPosicaoYY();
		float posZ = listaBalas[i]->getPosicaoZZ();

		if(posX < -MAPA_TAM || posX > MAPA_TAM || posZ < -MAPA_TAM || posZ > MAPA_TAM){
			listaBalas[i]->ok = false;
		} else {
			for(int j = 0; j < MAPA_TAM ; j++)
				if(listaBalas[i]->ok) listaBalas[i]->desenha();

		}
	}

}

ListaBalas::~ListaBalas(void)
{
}
