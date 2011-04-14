#include "Camera.h"



void scene()	{


}

/**
 * Desenha a cena
 */
void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	/* se a camara estiver para o objecto - first person
	if(tipo_de_camera == PRIMEIRA_PESSOA || tipo_de_camera == PRIMEIRA_PESSOA_NOVO)
		gluLookAt(	cam_pos[XX],			cam_pos[YY],			cam_pos[ZZ],
					cam_pos[XX]+cam_vd[XX],	cam_pos[YY]+cam_vd[YY],	cam_pos[ZZ]+cam_vd[ZZ],
					0,						1,						0);

	// se a camara estiver para o mundo - third person
	else gluLookAt(camX,camY,camZ,
					0,0,0,
					0,1,0);
	*/
	scene();
	
	glutSwapBuffers();
}

Camera::Camera(void)
{
}


Camera::~Camera(void)
{
}
