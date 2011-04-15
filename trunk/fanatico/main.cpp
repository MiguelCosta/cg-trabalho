#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <GL/glut.h>

#define FPS 0 //Especifica o modo FPS
#define TPS 1 //Especifica o modo TPS
#define N_KEYS 4 //Numero de chaves
#define RADAR_DIST 100 //distancia minima de uma chave para ser detetada

/************************************************************************************************************************
************************* VARIAVEIS GLOBAIS *****************************************************************************
************************************************************************************************************************/

int width = glutGet(GLUT_SCREEN_WIDTH);
int height = glutGet(GLUT_SCREEN_HEIGHT);
float camX = 0.0, camY = 1.0, camZ = -15.0;      //Posicaos da camara
float eyeX, eyeY, eyeZ;                     //Posicao onde a camara aponta
float playerX, playerZ, playerY;            //Posicao do avatar em modo TPS
float dirX, dirY, dirZ;                     //Vector director onde a camara aponta
float rightX, rightZ;                     //Vector director que aponta para a direita
float alpha = 0, beta = 0;                  //Angulos utilizados para calculo da posicao da camara e para onde ela aponta
int mouseX = 0, mouseY = 0;                  //Posicoes do rato para a movimentacao
bool running = true, help = false;            //Butoes de pausa e ajuda
int view = FPS;                           //Variavel que define o modo FPS ou TPS
float keyPos[N_KEYS][3];                  //Matriz contendo as coordenadas das chaves


/************************************************************************************************************************
************************* FUNCOES AUXILIARES ****************************************************************************
************************************************************************************************************************/


/*Esta funcao calcula para cada frame as posicoes da camara
   e para onde ela aponta tendo em conta o modo (FPS ou TPS)*/
void calcPos(float a, float b) {
   if(view == FPS) {
      eyeX = camX + (500 * cos(b) * sin(a));
      eyeZ = camZ + (500 * cos(b) * cos(a));
      eyeY = camY + (500 * sin(b));
   }   
   else {
      eyeX = playerX + (10 * cos(b) * sin(a));
      eyeZ = playerZ + (10 * cos(b) * cos(a));
      eyeY = playerY + (10 * sin(b));
      camX = playerX + (5 * cos((M_PI/10)-b) * sin(M_PI + a));
      camY = playerY + (5 * sin((M_PI/10)-b));
      camZ = playerZ + (5 * cos((M_PI/10)-b) * cos (M_PI + a));
   }
}

/*Funcao que calcula para cada frame os vectores directores
   utilizados para a movimentacao*/
void updateDir() {
   float x = eyeX - camX;
   float y = eyeY - camY;
   float z = eyeZ - camZ;
   float comp = sqrt((x*x) + (y*y) + (z*z));
   dirX = x/comp;                        //calculo do versor (dv = d/||d||)
   dirZ = z/comp;
   dirY = y/comp;
   rightX = -dirZ;                        //produto dos vectores dir e up(0,1,0)
   rightZ = dirX;
}

/*Radianos para Graus*/
float radToDeg(float val) {
   return ((180*val)/M_PI);
}

/* funcao que calcula a distancia entre dois pontos
   utilizada para as chaves*/
float distancia(float c1[3], float c2[3]){
   float dist = 0;
   float dx,dy,dz;
   
   dx = c1[0] - c2[0];
   dy = c1[1] - c2[1];
   dz = c1[2] - c2[2];
   
   dist = dx*dx+dy*dy+dz*dz;
   
   return dist;
}

/************************************************************************************************************************
************************* FUNCOES DE CALCULO ****************************************************************************
************************************************************************************************************************/

/*Funcao que determina pela posicao das chaves e da camara ou avatar
   a distancia entre eles e se for menor que RADAR_DIST é desenhada*/
void radar(char * ptr) {
   float posplay[3];
   float key[3];
   float dist = RADAR_DIST, aux = RADAR_DIST;
   int intkey = -1;
   
   if(view == FPS) {
      posplay[0] = camX; posplay[1] = camY; posplay[2] = camZ; }
   else {posplay[0] = playerX; posplay[1] = playerY; posplay[2] = playerZ;}

   for(int i=0; i<N_KEYS; i++) {
      key[0] = keyPos[i][0]; key[1] = keyPos[i][1]; key[2] = keyPos[i][2];
      aux = distancia(posplay, key);
      if(aux<dist && aux<RADAR_DIST) {
         dist = aux;
         intkey = i;
      }
   }

   if(intkey != -1)
      sprintf(ptr, "A chave nº%d está a %f", intkey, dist);
   else sprintf(ptr, "Sem chaves por perto...");
}

/*Funcao utilizada na inicializacao para determinar aleatoreamente
as posicoes das chaves*/
void getKeyPos() {
   srand(100);
   float ang, coordX, coordZ;
   int i = 0;
   while(i < N_KEYS) {
      ang = rand();
      coordX = ang*cos(ang);
      coordZ = ang*cos(ang);
      if(ang>25 && ang<100 && coordX<100 && coordZ<100) {
         keyPos[i][0] = coordX;
         keyPos[i][2] = coordZ;
         keyPos[i][1] = 2;
         i++;
      }
   }
}

/*FUNCAO AUXILIAR PARA PROJECCAO ORTOGONAL, EM CIMA A ESQUERDA*/
void resetPerspectiveProjection() {
   // set the current matrix to GL_PROJECTION
   glMatrixMode(GL_PROJECTION);
   // restore previous settings
   glPopMatrix();
   // get back to GL_MODELVIEW matrix
   glMatrixMode(GL_MODELVIEW);
}

/*FUNCAO AUXILIAR PARA PROJECCAO ORTOGONAL, EM CIMA A ESQUERDA*/
void renderBitmapString(float x, float y, void *font,char *string)
{
   char *c;
   // set position to start drawing fonts
   glRasterPos2f(x, y);
   // loop all the characters in the string
   for (c=string; *c != '\0'; c++) 
   {
      glutBitmapCharacter(font, *c);
   }
}

/*FUNCAO AUXILIAR PARA PROJECCAO ORTOGONAL, EM CIMA A ESQUERDA*/
void setOrthographicProjection(){
   // switch to projection mode
   glMatrixMode(GL_PROJECTION);
   //save previous matrix which contains the 
   //settings for the perspective projection
   glPushMatrix();
   // reset matrix
   glLoadIdentity();
   // set a 2D orthographic projection
   gluOrtho2D(0, 1024, 0, 800);
   // invert the y axis, down is positive
   glScalef(1, -1, 1);
   // mover the origin from the bottom left corner
   // to the upper left corner
   glTranslatef(0, -800, 0);
   glMatrixMode(GL_MODELVIEW);
}

/*FUNCAO PRINCIPAL DA PROJECCAO ORTOGONAL, EM CIMA A ESQUERDA*/
int font=(int)GLUT_BITMAP_8_BY_13;
void writeText(){

   glDisable (GL_LIGHTING);

   glPushMatrix();
   glLoadIdentity();
   
   setOrthographicProjection();
   glColor3f(1.0, 1.0, 1.0);

   char ajuda[6][50];
   char tempo[50];
   radar(tempo);

   strcpy(ajuda[0],"Ajuda (h)");
   strcpy(ajuda[1],"w - Ir para a frente");
   strcpy(ajuda[2],"s - Ir para traz");
   strcpy(ajuda[3],"d - Ir para a direita");
   strcpy(ajuda[4],"a - Ir para a esquerda");
   strcpy(ajuda[5],"v - Mudar tipo de camara");

   //for(int i = 0 ; i < 5 ; i++){
      renderBitmapString(30,35,(void *)font,tempo/*[i]*/);
   //}
   if(!help)
      renderBitmapString(30,55,(void *)font,ajuda[0]);
   else {
      for(int i = 0 ; i < 6 ; i++)
         renderBitmapString(30,55+(i*20),(void *)font,ajuda[i]);
   }
   resetPerspectiveProjection();
   glPopMatrix();
   glEnable (GL_LIGHTING);   
}

/************************************************************************************************************************
************************* FUNCOES DE DESENHO ****************************************************************************
************************************************************************************************************************/

/*Desenho base de uma chave*/
void key() {
   glPushMatrix();
   glScalef(0.5,1,1);
   glutSolidTorus(0.5,1,10,10);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0,-3.5,0);
   glScalef(1,10,1);
   glutSolidCube(0.5);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-0.5,-5.5,0);
   glScalef(2,1,1);
   glutSolidCube(0.5);
   glTranslatef(0,1,0);
   glutSolidCube(0.5);
   glPopMatrix();
}

/*Desenho do terreno*/
void drawGround() {
   glDisable(GL_LIGHT0);
   glColor3f(0.3, 0.3, 0.3);
   GLfloat emis[3] = {0.0, 0.0, 0.0};
   glMaterialfv(GL_FRONT, GL_EMISSION, emis);
   for(int i = -200; i < 199; i++) {
   glBegin(GL_TRIANGLE_STRIP);
      for(int j = -200; j < 200; j++) {
         glNormal3f(0, 1, 0);
         glVertex3f(j, 0, i);
         glVertex3f(j, 0, i+1);
      }
   glEnd();
   }
   glEnable(GL_LIGHT0);

   glColor3f(1.0, 1.0, 1.0);
   GLfloat emis2[3] = {1.0, 1.0, 1.0};
   glMaterialfv(GL_FRONT, GL_EMISSION, emis2);
   glPushMatrix();
   glTranslatef(0.0, 0.0, 0.0);
   glutSolidSphere(2, 10, 10);
   glPopMatrix();

   glColor3f(0.0, 0.0, 1.0);
   glMaterialfv(GL_FRONT, GL_EMISSION, emis);
   glPushMatrix();
   glTranslatef(10, 1, 10);
   glutSolidCube(2);
   glPopMatrix();

}

/*Desenho do avatar*/
void drawPlayer() {
   if(view == TPS) {
      glColor3f(1.0, 0.0, 0.0);
      GLfloat emis1[3] = {0.0, 0.0, 0.0};
      glMaterialfv(GL_FRONT, GL_DIFFUSE, emis1);
      glPushMatrix();
      glTranslatef(playerX, playerY-0.6, playerZ);
      glRotatef(radToDeg(alpha) - 90, 0.0, 1.0, 0.0);
      glutSolidTeapot(0.5);
      glPopMatrix();
   }

   glColor3f(1.0, 1.0, 1.0);
   GLfloat emis[3] = {1.0, 1.0, 1.0};
   glMaterialfv(GL_FRONT, GL_EMISSION, emis);
   glPushMatrix();
   glTranslatef(camX + 2*dirX, camY + 2*dirY, camZ + 2*dirZ);
   glutSolidSphere(0.005, 10, 10);
   glPopMatrix();


}

/*Desenho das varias chaves*/
void drawkeys() {
   for(int i=0; i < 4; i++) {
      glColor3f(0.0, 1.0, 0.0);
      glPushMatrix();
      glTranslatef(keyPos[i][0], keyPos[i][1], keyPos[i][2]);
      glScalef(0.3,0.3,0.3);
      key();
      glPopMatrix();
   }
}

/************************************************************************************************************************
************************* FUNCOES OPENGL ****************************************************************************
************************************************************************************************************************/

void changeSize(int w, int h) {

   // Prevent a divide by zero, when window is too short
   // (you cant make a window with zero width).
   if(h == 0)
      h = 1;

   // compute window's aspect ratio 
   float ratio = w * 1.0 / h;

   // Reset the coordinate system before modifying
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   
   // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

   // Set the correct perspective
   gluPerspective(45,ratio,1,1000);

   // return to the model view matrix mode
   glMatrixMode(GL_MODELVIEW);
}

/*void centerMouse(){

   if (x > width-3 || x < 2 || z > height-3 || z < 2)
      SetCursorPos(width / 2, height / 2);
}*/

void renderScene(void) {
   glClearColor(0.0f,0.0f,0.0f,0.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();
   gluLookAt(camX, camY, camZ, 
            eyeX, eyeY, eyeZ,
           0.0f,1.0f,0.0f);
   //centerMouse();
   GLfloat amb[3] = {0.2, 0.2, 0.2};
   GLfloat pos[4] = {0.0, 0.0 ,0.0, 1.0};
   glLightfv(GL_LIGHT0, GL_POSITION, pos);
   glLightfv(GL_LIGHT0, GL_AMBIENT, amb);

   updateDir();

   drawGround();
   drawPlayer();
   drawkeys();
   writeText();

   glutSwapBuffers();
}

/************************************************************************************************************************
************************* FUNCOES TECLADO E RATO ************************************************************************
************************************************************************************************************************/

// escrever função de processamento do teclado
void processKeys(unsigned char key, int xx, int yy) {   
   if(running) {
      switch(key) {
      // escrever aqui código para processar eventos
         case 'w':
            if(view == FPS) {                  //Utilisa o vector director para orientar a nova posicao
               camX += 3*dirX;                  //da camara e para onde ela aponta
               camZ += 3*dirZ;
               eyeX += 3*dirX;
               eyeZ += 3*dirZ;
            }
            else {
               playerX += 3*dirX;               //Estruturado para o modo FPS e TPS
               playerZ += 3*dirZ;
               calcPos(alpha, beta);
            }
            break;
         case 's':
            if(view == FPS) {
               camX -= 3*dirX;
               camZ -= 3*dirZ;
               eyeX -= 3*dirX;
               eyeZ -= 3*dirZ;
            }
            else {
               playerX -= 3*dirX;
               playerZ -= 3*dirZ;
               calcPos(alpha, beta);
            }
            break;
         case 'a':
            if(view == FPS) {                  //Utilisa o vecto diretor orientado a direita para
               camX -= 2*rightX;               //os movimentos laterais
               camZ -= 2*rightZ;
               eyeX -= 2*rightX;
               eyeZ -= 2*rightZ;
            }
            else {
               playerX -= 3*rightX;
               playerZ -= 3*rightZ;
               calcPos(alpha, beta);
            }
            break;
         case 'd':
            if(view == FPS) {
               camX += 2*rightX;
               camZ += 2*rightZ;
               eyeX += 2*rightX;
               eyeZ += 2*rightZ;
            }
            else {
               playerX += 3*rightX;
               playerZ += 3*rightZ;
               calcPos(alpha, beta);
            }
            break;
         case 'v' :                           //Passa do modo FPS para TPS e vice versa
            if(view == FPS) {
               playerX = camX; playerY = camY; playerZ = camZ;
               view = TPS;
               calcPos(alpha, beta);
            }
            else {
               camX = playerX; camY = playerY; camZ = playerZ;
               view = FPS;
               calcPos(alpha, beta);
            }
            break;                           //Pausa o jogo
         case 'p' : running = ! running;
            break;
         case 'h' : help = ! help;               //Menu de ajuda na projecao ortogonal, em cima a esquerda
            break;
         case 27 :                           //ESC pa sair
            exit(0);
      }
   
      glutPostRedisplay();
   }
}

// escrever função de processamento do teclado (teclas especiais)

void processSpecialKeys(int key, int xx, int yy) {
   if(running) {
      switch(key) {
      
      // escrever aqui código para processar eventos
         case GLUT_KEY_UP:
            break;
         case GLUT_KEY_DOWN:
            break;
         case GLUT_KEY_LEFT:
            break;
         case GLUT_KEY_RIGHT:
            break;
      }
      glutPostRedisplay();
   }
}

void fmouse(int button, int state, int xx, int yy) 
{

   // escrever aqui código para processar eventos do rato (botões)

   
}

void fmotion(int xx, int yy) {   

   // escrever aqui código para processar eventos do rato (movimento)

   //glutPostRedisplay();
}

/*Aqui os novos valores de X e Y das posicoes do rato sao passados
como argumentos e com os valores da frame anterior, guardados anteriormente
e possivel criar a interacao do modo FPS e TPS alterando os angulos*/
void fpassiveMouse(int xx, int yy) {
   
   if(running) {
      if(xx > mouseX)
         alpha -= 0.06;
      if(xx < mouseX)
         alpha += 0.06;
      mouseX = xx;

      if(yy > mouseY)
         beta -= 0.03;
      if(yy < mouseY)
         beta += 0.03;
      mouseY = yy;

      calcPos(alpha, beta);
      
      glutPostRedisplay();
   }
}

// escrever função de processamento do menu

/************************************************************************************************************************
************************* MAIN ******************************************************************************************
************************************************************************************************************************/

void main(int argc, char **argv) {

// inicialização
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
   glutInitWindowPosition(100,100);
   glutInitWindowSize(800,600);
   glutCreateWindow("CG@DI-UM");

    glShadeModel(GL_SMOOTH);

// registo de funções 
   glutDisplayFunc(renderScene);
   glutIdleFunc(renderScene);
   glutReshapeFunc(changeSize);

// pôr aqui registo da funções do teclado e rato
   glutMouseFunc(fmouse);
   glutMotionFunc(fmotion);
   glutKeyboardFunc(processKeys);   
   glutSpecialFunc(processSpecialKeys);
   glutPassiveMotionFunc(fpassiveMouse);

// pôr aqui a criação do menu


// alguns settings para OpenGL

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);

   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHTING);
   glEnable(GL_COLOR_MATERIAL);
   
   calcPos(alpha, beta);
   getKeyPos();

// entrar no ciclo do GLUT 
   glutMainLoop();
}