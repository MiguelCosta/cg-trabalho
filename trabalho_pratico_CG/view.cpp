#include "view.h"
#include <math.h>

int tipo_de_camera = PRIMEIRA_PESSOA;

// local camera position
GLdouble cam_pos[]={0.0, 1.2,20};

// local camera view direction
GLdouble cam_vd[]={0.0, 0.0, -1.0};

// camera orientation angle
int startX, startY, tracking = 0;
int alpha = 0, beta = 0, r = 5;
float camX = 0, camY, camZ = 5;

float cam_alpha=0.0;


float velocidade_cam = 1;

bool cam_local = true; // switch between camera local to agent and high camera

unsigned int texID;
unsigned int largura, altura, format, il_img[20];
unsigned char *il_imgData;




void keyboard(unsigned char key, int x, int y){
	switch(key) {
		case 27:   // ESCape, fechar a janela
			exit (0);
			break;

		// alterar o modo da camara
		case '1': 
				cam_local = false;	// vista de third person
				tipo_de_camera = TERCEIRA_PESSOA;	// vista de third person
				break;
		case '2': 
				cam_local = true;		// vista de first person
				tipo_de_camera = PRIMEIRA_PESSOA;		// vista de first person
				break;
		case '3':
				tipo_de_camera = PRIMEIRA_PESSOA_NOVO;
				break;

		// alterar a posi��o da camara
		case 'w': 
			cam_pos[0] = cam_pos[0] + cam_vd[0]*VELOCIDADE_CAM;
			cam_pos[1] = cam_pos[1] + cam_vd[1]*VELOCIDADE_CAM;
			cam_pos[2] = cam_pos[2] + cam_vd[2]*VELOCIDADE_CAM;				  
			break;

		case 's': 
			cam_pos[0] = cam_pos[0] - cam_vd[0]*VELOCIDADE_CAM;
			cam_pos[1] = cam_pos[1] - cam_vd[1]*VELOCIDADE_CAM;
			cam_pos[2] = cam_pos[2] - cam_vd[2]*VELOCIDADE_CAM;				  
			break;

		//rodar a camara
		case 'd': cam_alpha += 0.05;
				     cam_vd[XX] = sin(cam_alpha); 		  
     				     cam_vd[ZZ] = -cos(cam_alpha);
				     break;
		case 'a': cam_alpha -= 0.05;
				    cam_vd[XX] = sin(cam_alpha); 		  
     				    cam_vd[ZZ] = -cos(cam_alpha);			  
				    break;
		default: 
			break;
	}
	glutPostRedisplay();
}


//Teclas Especiais (F1..F12, Home, End, setas, etc...)
void keybord_special(int key, int x, int y) {
	switch (key) {
		
	}

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

	while (arvores < ARVORES) {

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


//Desenha o Solo
void drawPlane() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);

	glPushMatrix();

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

//Desenha tudo
void scene() {

	//drawWorld();
	placeTrees();
	drawBoneco();
	glColor3f(0.8,0.5,0.2);
	drawPlane();
}



void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	// se a camara estiver para o objecto - first person
	if(tipo_de_camera == PRIMEIRA_PESSOA || tipo_de_camera == PRIMEIRA_PESSOA_NOVO)
		gluLookAt(	cam_pos[XX],			cam_pos[YY],			cam_pos[ZZ],
					cam_pos[XX]+cam_vd[XX],	cam_pos[YY]+cam_vd[YY],	cam_pos[ZZ]+cam_vd[ZZ],
					0,						1,						0);

	// se a camara estiver para o mundo - third person
	else gluLookAt(camX,camY,camZ,
					0,0,0,
					0,1,0);
	scene();
	
	glutSwapBuffers();
}


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
		case 0:
			break;
		default:
			break;
	}
	glutPostRedisplay();
}


/**
 * Funcao que cria menu de contexto do rato
 */
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
	
			glutAttachMenu(GLUT_MIDDLE_BUTTON);

}


//Bot�o premido ou solto
//tracking == 1 -> bot�o esquerdo premido	-> move a camara
//tracking == 2 -> bot�o direito premido	-> zoom da camara
//tracking == 3 -> bot�o scroll premido		-> menu
//tracking == 0 -> nenhum bot�o premido
void processMouseButtons(int button, int state, int xx, int yy) 
{
   if (state == GLUT_DOWN)  {
		// onde est� o ponteiro quando se clica
	  startX = xx;
      startY = yy;

	  // bot�o esquerdo do rato primido
	  if (button == GLUT_LEFT_BUTTON){ 
		  tracking = 1; 
		  printf("\nTraching; %d",tracking);
	  }
	  // bot�o direito do rato primido
	  else if (button == GLUT_RIGHT_BUTTON) { 
		  tracking = 2; 
		  printf("\nTraching; %d",tracking);
	  }

	  // bot�o scroll primido
	  else if (button == GLUT_MIDDLE_BUTTON) { 
		  cria_menu(); 
		  tracking = 3; 
		  printf("\nTraching; %d",tracking);
	  }
      else tracking = 0;
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



void ratoPassivo(int x, int y)	{
	static int lastX = x, lastY = y;

	cam_vd[XX] += x - lastX;
	cam_vd[YY] += y - lastY;
}


//Movimento passivo (sem bot�o premido) ou activo
void processMouseMotion(int xx, int yy)
{

   int deltaX, deltaY;		// para colocar as varia�oes do movimento
   int alphaAux, betaAux;	// alpha e beta auxiliares
   int rAux= r;				// raio auxiliar

   int meioEcraX = glutGet(GLUT_WINDOW_WIDTH)/2;
   int meioEcraY = glutGet(GLUT_WINDOW_HEIGHT)/2;


   if (!tracking){
      printf("nada\n");
	  return;
   }

   // � quando se mostra o menu
   if (tracking == 3){
	   return;
   }

   deltaX = xx - startX;
   deltaY = yy - startY;

   /* quando bot�o direito est� primido */
   if (tracking == 1) {

      alphaAux = alpha + deltaX;
      betaAux = beta + deltaY;

      if (betaAux > 80.0) betaAux = 80.0;	// limite superior da camara
      if (betaAux < 3) betaAux = 3 ;	// limite inferior da camara

	  //glutWarpPointer(meioEcraX, meioEcraY);
	  //glutSetCursor(GLUT_CURSOR_NONE);
      rAux = r;								// raio da camara
   }
   
   /* quando est� o bot�o direito do rato activo */
	if (tracking == 2) {
      alphaAux = alpha;
      betaAux = beta;
      rAux = r - deltaY;

      if (rAux < 3)		// limite inferior do zoom
         rAux = 3;
   }

   // calcula a nova posi��o da camara
   camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
   camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
   camY = rAux *                                sin(betaAux * 3.14 / 180.0);


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