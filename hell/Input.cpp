

#include <GL/glut.h>
#include <math.h>

#include "Camera.h"
#include "Input.h"


/* Cenas para o rato! */
int startX, startY, tracking = 0;
int alpha = 0, beta = 45, r = 50;
//float camPos[3] = { 0.0, 30.0, 40.0 };

extern Camera * _camera;

void processMouseButtons(int button, int state, int xx, int yy)		{
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}

	
}


void processMouseMotion(int xx, int yy)	{

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	_camera->camPosOnGodMode[XX] = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	_camera->camPosOnGodMode[YY] = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	_camera->camPosOnGodMode[ZZ] = rAux * 							     sin(betaAux * 3.14 / 180.0);


}

