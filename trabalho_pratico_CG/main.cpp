#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <IL/il.h>
#include <string.h>
#include "glm.h"

#define _PI_ 3.14159

#define XX 0
#define YY 1
#define ZZ 2

/* Tipos de camera */
#define FIST_PERSON		1
#define THIRD_PERSON	2
#define GOD_MODE		3
#define _ANTERIOR		4
#define _ANTERIOR_		5

/* Tipo de camera */
int cam_type = GOD_MODE;

/* Posicao do agente */
GLdouble pos[]={0.0, 1.2, 0.0};

/* local camera position */
GLdouble cam_pos[]={0.0, 1.2,20}; 

/* local camera view direction */
GLdouble cam_vd[]={0.0, 0.0, -1.0};

/* camera orientation angle */
int startX, startY, tracking = 0; /* Coisas para o rato! */
int alpha = 0, beta = 0, r = 5;
float camX = 0, camY, camZ = 5;

float velocidade_move = 0.05;

//variaveis texturas

//Load imagem
unsigned char *il_imgData;
unsigned int largura, altura, format, il_img[20];

//Criar um objecto de textura
unsigned int texID;

//Variaveis Ilumina��o
bool flag_luz = false;

float cam_alpha=0.0;

bool cam_local=true; // switch between camera local to agent and high camera


/* Velocidade do agente */
float delta = 1;


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

<<<<<<< .mine
//Frames por segundo
void fps()	{


	step=0;
}

=======
>>>>>>> .r15
//Desenha os eixos
void drawAxis() {
   glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(2000.0, 0.0, 0.0);

	  glColor3f(0.0, 1.0, 0.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 2000.0, 0.0);
      
	  glColor3f(0.0, 0.0, 1.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, 2000.0);
   glEnd();
}

//Desenha uma �rvore
void drawTree() {
	glPushMatrix();
		glRotatef(-90,1.0,0.0,0.0);
		glColor3f(1.0,1.0,0.5);
		glutSolidCone(0.25,4,8,1);
		glColor3f(0.0,1.0,0.0);
		glTranslatef(0.0,0.0,2.0);
		glutSolidCone(2.0,5.0,8,1);
	glPopMatrix();
}

//Coloca as �rvores aleatoriamente
void placeTrees() {

	float r = 10;
	float alpha;
	float rr;
	float x,z;

	srand(31457);
	int arvores = 0;

	while (arvores < 500) {

		rr = rand() * 2000.0/ RAND_MAX;
		alpha = rand() * 6.28 / RAND_MAX;

		x = cos(alpha) * (rr + r);
		z = sin(alpha) * (rr + r);

		if (fabs(x) < 2000 && fabs(z) < 2000) {

			glPushMatrix();
			glTranslatef(x,0.0,z);
			drawTree();
			glPopMatrix();
			arvores++;
		}
	}
}

//Desenha uma esfera para o Globo
void drawWorld(){
	
	glBindTexture(GL_TEXTURE_2D,1);
	
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1,0);glVertex3f( 1.0f, -1.0f, 0.0f);
		glTexCoord2f(1,1);glVertex3f( 1.0f, 1.0f, 0.0f);
		glTexCoord2f(0,1);glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();


}

void pos_Luz(){
	GLfloat amb[3] = {0.2, 0.2, 0.2};
	GLfloat diff[3] = {1.0, 1.0, 1.0};
	GLfloat pos[4] = {0.0, 0.5, 0.5, 0.0};

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
}

//Desenha o Solo
void drawPlane() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);

	glPushMatrix();
	//float color[] = {0.8,0.5,0.2,0.0};
	//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	//int x,y;

	//glPushMatrix();
	//glTranslatef(-100,0,-100);
	//for(x=0; x < 500; x++){
		//glBindTexture(GL_TEXTURE_2D, texID);
		//glBegin(GL_QUADS);
		//glTexCoord2f(largura, altura);
	//}

	glBegin(GL_QUADS);
		glTexCoord2f(-2000,2000);glVertex3f(-2000.0, 0.0, 2000.0);
		glTexCoord2f(2000,2000);glVertex3f( 2000.0, 0.0, 2000.0);
		glTexCoord2f(2000,-2000);glVertex3f( 2000.0, 0.0,-2000.0);
		glTexCoord2f(-2000,-2000);glVertex3f(-2000.0, 0.0,-2000.0);
	glEnd();
	
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
}

//Desenha o Agente
void drawBoneco() {

	glPushMatrix();
	glTranslatef(0.0,2,0.0);
	glColor3f(0.0,0.5,1.0);
	glutSolidTeapot(2);
	//glutSolidTorus(0.5,1.25,8,16);
	glPopMatrix();
}

//Loading textura, nome da textura como par�metro. Ex: Load_img(batman.jpg)
void Load_img(char *filename) {

	ilInit();
	ilGenImages(1, il_img); // get an unique ID
	ilBindImage(il_img[0]); // Bind this image name.
	
	ilLoadImage((ILstring)filename); // Load the image
	
	largura = ilGetInteger (IL_IMAGE_WIDTH);
	altura = ilGetInteger (IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE); //nao sei o q faz , n sei se � necessario
	il_imgData = ilGetData();
	format = ilGetInteger(IL_IMAGE_FORMAT);


	glGenTextures (1, &texID); // get texture unique ID
	glBindTexture (GL_TEXTURE_2D, texID); // bind it

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,largura,altura,0,format,GL_UNSIGNED_BYTE,il_imgData);
	
	//difere do tupo de imagem que queremos carregar
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,largura,altura,0,GL_RGBA,GL_UNSIGNED_BYTE,il_imgData);
	
	//ilDeleteImages(1, &il_img);// Release data space created with DevIL

	// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// inicializa��o da luz
	
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);
}


//Desenha tudo
void scene() {

	//drawWorld();
	placeTrees();
	drawBoneco();
	glColor3f(1,1,1);
	drawPlane();

}


void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	switch(cam_type)	{
		case FIST_PERSON:
			gluLookAt(	pos[XX], pos[YY], pos[ZZ],
						pos[XX]+cam_vd[XX], pos[YY]+cam_vd[YY], pos[ZZ]+cam_vd[ZZ],
						0,1,0);
			break;
		case THIRD_PERSON:
			gluLookAt(	pos[XX], pos[YY], 20+pos[ZZ],
						pos[XX]+cam_vd[XX], pos[YY]+cam_vd[YY], 20+pos[ZZ]+cam_vd[ZZ],
						0,1,0);
			break;
		case GOD_MODE:
			gluLookAt(	pos[XX], 1000, pos[ZZ],
						0,0,-1,//0,
						0,1,0);
		case _ANTERIOR:
			gluLookAt(	cam_pos[0],cam_pos[1],cam_pos[2],
						cam_pos[0]+cam_vd[0],cam_pos[1]+cam_vd[1],cam_pos[2]+cam_vd[2],
						0,1,0);
			break;
		case _ANTERIOR_:
			gluLookAt(camX,camY,camZ,
					0,0,0,
					0,1,0);
<<<<<<< .mine
	pos_Luz();
=======
	}
	
	drawAxis();
>>>>>>> .r15
	scene();
<<<<<<< .mine
	
	Load_img("relva1.jpg");
	//Load_img("123.jpg");
	//drawAxis();
	step++;
=======
>>>>>>> .r15
	glutSwapBuffers();
}

<<<<<<< .mine
void menuFaceModo(int op){

	switch(op){
		case 0: glPolygonMode(GL_FRONT,GL_FILL);
			break;
		case 1: glPolygonMode(GL_FRONT,GL_LINE);
			break;
		case 2: glPolygonMode(GL_FRONT,GL_POINT);
			break;
		case 3: glPolygonMode(GL_BACK,GL_FILL);
			break;
		case 4: glPolygonMode(GL_BACK,GL_LINE);
			break;
		case 5: glPolygonMode(GL_BACK,GL_POINT);
			break;
		case 6: glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			break;
		case 7: glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			break;
		case 8: glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
			break;
	}
	glutPostRedisplay();
}
void escolherMapa(int op){

	switch(op){
		case 0: fprintf(stderr,"erro");
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
void cria_menu(){

	int submenu1, submenu2;

		submenu1 = glutCreateMenu(escolherMapa);
			glutAddMenuEntry("Mapa 1", 1);
			glutAddMenuEntry("Mapa 2", 2);
		submenu2 = glutCreateMenu(menuFaceModo);
			glutAddMenuEntry("GL_FRONT | GL_FILL",0);
			glutAddMenuEntry("GL_FRONT | GL_LINE",1);
			glutAddMenuEntry("GL_FRONT | GL_POINT)",2);
			glutAddMenuEntry("GL_BACK  | GL_FILL",3);
			glutAddMenuEntry("GL_BACK  | GL_LINE",4);
			glutAddMenuEntry("GL_BACK  | GL_POINT)",5);
			glutAddMenuEntry("GL_FRONT_AND_BACK | GL_FILL",6);
			glutAddMenuEntry("GL_FRONT_AND_BACK | GL_LINE",7);
			glutAddMenuEntry("GL_FRONT_AND_BACK | GL_POINT)",8);
		glutCreateMenu(escolherMapa);
			glutAddSubMenu("Mapas", submenu1);
			glutAddSubMenu("Face dos Objetos", submenu2);
	

	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

//Teclas Normais (letras, n�meros, etc...)
void keyboard(unsigned char key, int x, int y){
	switch(key) {
=======
void keyboard (unsigned char key, int x, int y) {
	switch (key)	{
>>>>>>> .r15
		case 27:   // ESCape
			exit (0);
			break;
		case '1': 
			cam_type = FIST_PERSON;
			break;
		case '2':
			cam_type = THIRD_PERSON;
			break;
		case '3':
			cam_type = GOD_MODE;
			break;
		case '4':
			cam_type = _ANTERIOR;
			break;
		case '5':
			cam_type = _ANTERIOR_;
			break;

		case 'w': 
			pos[XX] += cam_vd[XX]*delta;
			//pos[YY] += cam_vd[YY]*delta;
			pos[ZZ] += cam_vd[ZZ]*delta;				  
			break;
		case 's': 
			pos[XX] -= cam_vd[XX]*delta;
			//pos[YY] -= cam_vd[YY]*delta;
			pos[ZZ] -= cam_vd[ZZ]*delta;				  
			break;
		case 'a':
			pos[XX] -= cam_vd[ZZ]*delta;
			//pos[ZZ] 
		case 'd':

		default: 
			break;
	}
		//se a camara rodar com as setas
<<<<<<< .mine
		case 'd': cam_alpha += velocidade_move;
=======
		/*case 'd': cam_alpha += 0.05;
>>>>>>> .r15
				     cam_vd[XX] = sin(cam_alpha); 		  
     				     cam_vd[ZZ] = -cos(cam_alpha);
				     break;
		case 'a': cam_alpha -= velocidade_move;
				    cam_vd[XX] = sin(cam_alpha); 		  
     				    cam_vd[ZZ] = -cos(cam_alpha);			  
<<<<<<< .mine
				    break;
		case 'l': flag_luz = !flag_luz;
					break;
		case 'm': cria_menu();
				break;
		default: 
			break;
	}
=======
				    break;*/
	
>>>>>>> .r15
	glutPostRedisplay();
}

//Teclas Especiais (F1..F12, Home, End, setas, etc...)
void special_kb(int key, int x, int y) {
	switch (key) {
		
	}

}

//Bot�o premido ou solto
//tracking == 1 -> bot�o esquerdo premido
//tracking == 2 -> bot�o direito premido
//tracking == 0 -> nenhum bot�o premido
void processMouseButtons(int button, int state, int xx, int yy) 
{	/*
   if (state == GLUT_DOWN)  {
      startX = xx;
      startY = yy;
      if (button == GLUT_LEFT_BUTTON)
         tracking = 1;
      else if (button == GLUT_RIGHT_BUTTON)
         cria_menu();//tracking = 2;
	  else if (button == GLUT_MIDDLE_BUTTON)
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
   */
   
}

<<<<<<< .mine
//Movimento passivo (sem bot�o premido) ou activo
=======
void processMouseMove(int x, int y)	{
	static int lastX = x;
	static int lastY = y;

>>>>>>> .r15
	cam_vd[0]+= (x-lastX);
	cam_vd[1]+= (y-lastY);

	lastX = x;
	lastY = y;

	SetCursorPos()
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
   camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
   camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
   camY = rAux *                          sin(betaAux * 3.14 / 180.0);

}

<<<<<<< .mine
=======
/*void special_kb(int key, int x, int y) {
	switch (key) {
		
	}
>>>>>>> .r15

<<<<<<< .mine
=======
}*/
>>>>>>> .r15

int main(int argc, char **argv) {

	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1024,1024);
	glutCreateWindow("Trabalho Patra de CG");
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboard);
	//glutSpecialFunc(special_kb);
	//glutMouseFunc(mouse);
	glutMouseFunc(processMouseButtons);
    glutPassiveMotionFunc(processMouseMove);
	//glutMotionFunc(processMouseMotion);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//criarTextura();
	glutMainLoop();
	return 0;
}