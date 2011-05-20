
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <IL/il.h>

#include "Mapa.h"
#include "Camera.h"
#include "Input.h"

Mapa	*_mapa;
//Agente	*_agente;
Camera	*_camera;
bool teclas[NUM_TECLAS];

void renderScene(void)	{
	
	float pos[4]={10.0,1.0,-1.0,0.0};
	GLfloat amb[3]={0.5,0.5,0.5};
	GLfloat diff[3]={1.0,1.0,1.0};

	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	_camera->desenhar();

	//instruções de posicionamento da luz
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);


	//_agente->desenhar();
	_mapa->desenhar();
	
	glutSwapBuffers();
}


//Redimensionar a janela
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you can't make a window of zero width).
	if(h == 0)
		h = 1;

	//width = w; 
	//height = h;

	float ratio = 1.0 * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1.5,1000);
	glMatrixMode(GL_MODELVIEW);
}

void carregaTexturas(){
	ilInit();
	_mapa->initMapaAlturas((ILstring)"texturas/mapa_alturas.jpg");
	_mapa->initTextura("texturas/terreno/relva.png");
	
}

void carregaObjectos(){
	//carregar edificio do tesouro
			_mapa->edificio->edificio = glmReadOBJ("modelos/edificio/Observatory.obj");
			glmUnitize(_mapa->edificio->edificio);
			glmFacetNormals(_mapa->edificio->edificio);
			glmVertexNormals(_mapa->edificio->edificio,90);
	//carregar chaves
			int i;
			for(i=0;i<NUM_CHAVES;i++){
				_mapa->chaves[i]->chave = glmReadOBJ("modelos/edificio/chave.obj");
				glmUnitize(_mapa->chaves[i]->chave);
				glmFacetNormals(_mapa->chaves[i]->chave);
				glmVertexNormals(_mapa->chaves[i]->chave,90);
			}
	//carregar agente
			_mapa->agente->agente = glmReadOBJ("modelos/agente/al.obj");
			glmUnitize(_mapa->agente->agente);
			glmFacetNormals(_mapa->agente->agente);
			glmVertexNormals(_mapa->agente->agente,90);
}


int main(int argc, char **argv) {

	
	// Codigo do programa
	_mapa = new Mapa();
	_camera = new Camera();
	// Inicializacao
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1024,1024);
	glutCreateWindow("Trabalho CG");
	
	// Registo de funcoes
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	
	glutKeyboardFunc(processarTecladoDown);
	glutKeyboardUpFunc(processarTecladoUp);
	glutSpecialFunc(processarTecladoEspecialDown);
	glutSpecialUpFunc(processarTecladoEspecialUp);

	glutPassiveMotionFunc(processarMovimentoRato);
	//glutMouseFunc(processMouseButtons);
	//glutMotionFunc(processMouseMotion);


	// Definicoes do OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glutSetCursor(GLUT_CURSOR_NONE);
	//glutFullScreen();

	glPolygonMode(GL_FRONT, GL_LINE);
	//inicialização da luz
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);



	//carregar texturas
	carregaTexturas();

	//carregar objectos
	carregaObjectos();

	glutMainLoop();
	return 0;
}

