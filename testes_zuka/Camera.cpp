#include "Camera.h"



void scene(){
	_mapa->desenhar();
}

/**
 * Desenha a cena
 */
//renderScene
void Camera::mostracena(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	/* se a camara estiver para o objecto - first person */
	if(tipoDeVista == PRIMEIRA_PESSOA){
		gluLookAt(	cam_pos[XX],			cam_pos[YY],			cam_pos[ZZ],
					cam_pos[XX]+cam_vd[XX],	cam_pos[YY]+cam_vd[YY],	cam_pos[ZZ]+cam_vd[ZZ],
					0,						1,						0);
		}
	// se a camara estiver para o mundo - third person
	else if(tipoDeVista == TERCEIRA_PESSOA){
		gluLookAt(cam_pos[XX],	cam_pos[YY],	cam_pos[ZZ],
				  0,			0,				0,
				  0,			1,				0);
	}
	// se a camara estiver em modo deus
	else if(tipoDeVista == MODO_DEUS){
		gluLookAt(cam_pos[XX],	cam_pos[YY],	cam_pos[ZZ],
				  0,			0,				0,
				  0,			1,				0);
	}


	scene();
	
	glutSwapBuffers();
}

Camera::Camera(void)
{
	tipoDeVista = MODO_DEUS;
	mostracena();
}


Camera::~Camera(void)
{
}
