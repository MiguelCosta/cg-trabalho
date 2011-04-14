
#include "Camera.h"
#include "mapa.h"

void scene(){
	_mapa->desenhar();
}

/**
 * Desenha a cena
 */
//renderScene
void Camera::desenhar(void) {
	
	/* se a camara estiver para o objecto - first person */
	if(tipoDeVista == PRIMEIRA_PESSOA){
	//	gluLookAt(	cam_pos[XX],			cam_pos[YY],			cam_pos[ZZ],
	//				cam_pos[XX]+cam_vd[XX],	cam_pos[YY]+cam_vd[YY],	cam_pos[ZZ]+cam_vd[ZZ],
	//				0,						1,						0);
		}
	// se a camara estiver para o mundo - third person
	else if(tipoDeVista == TERCEIRA_PESSOA){
	//	gluLookAt(cam_pos[XX],	cam_pos[YY],	cam_pos[ZZ],
	//			  0,			0,				0,
	//			  0,			1,				0);
	}
	// se a camara estiver em modo deus
	else if(tipoDeVista == MODO_DEUS){
		gluLookAt(0.0,		1000.0,		0.0,
				  0.0,		0.0,		0.0,
				  0.0,		1.0,		0.0);
	}

}

Camera::Camera(void)	{
	
	tipoDeVista = MODO_DEUS;

	direcao[XX] = 0.0;
	direcao[YY] = -1.0;
	direcao[ZZ] = 0.0;
}


Camera::~Camera(void)
{
}
