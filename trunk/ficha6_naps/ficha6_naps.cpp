#include <stdlib.h>
#include <GL/glut.h>

// include para a bib devil
// n�o esquecer de adicionar a lib (devil.lib) ao projecto
#include <IL/il.h>

#include <math.h>

#define ANG2RAD 3.14159265358979323846/360.0 

#define COWBOYS 8
#define RAIO_COWBOYS 5
#define INDIOS 16
#define RAIO_INDIOS 25
#define ARVORES 1000
#define STEP_COWBOY 1.0f
#define STEP_INDIO 0.5f


float step = 0.0;

float height = 2.0f;
float x = 0.0f;
float z = 0.0f;


float camX = 00, camY = 30, camZ = 40;

float cX = 0, cY = 0, cZ = 0;
float ang = 0;

int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;

unsigned int img_text, img_height;
int text_w, text_h, height_w, height_h;
unsigned int text_id;
unsigned char *text_data, *height_data;

int grid_n;

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

float h(float x, float z) {
   return height_data[(int) x + (int) z * height_w] / 2.0;
}

void heightedVertex(float mult, float x, float z) {
   glVertex3f(mult*x, h(x, z), mult*z);
}

void drawPlane() {

   float grid_width = 256 / (float) grid_n;

   float color[] = {0.2,0.8,0.2,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
   int x = 0, y = 0;
   glPolygonMode(GL_BACK, GL_LINE);

   glPushMatrix();
   glBindTexture(GL_TEXTURE_2D, text_id);
   glTranslatef(-128, 0, -128);
   for(x = 0; x < height_h; x++) {
      glBegin(GL_TRIANGLE_STRIP);
         for(y = 0; y < height_w; y++) {
            glTexCoord2f(y, 0);    
			heightedVertex(grid_width, (x+1), y);
            glTexCoord2f(y, 1);   
			heightedVertex(grid_width, x, y);

         }
      glEnd();
   }
   glBindTexture(GL_TEXTURE_2D, 0);
   glPopMatrix();
}

void drawTree() {

   glPushMatrix();
   glRotatef(-90,1.0,0.0,0.0);
   float color[] = {1.0,1.0,0.5,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
   glutSolidCone(0.25,4,5,1);
   float color2[] = {0.0, 0.5 + rand() * 0.5f/RAND_MAX,0.0,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color2);
   glTranslatef(0.0,0.0,2.0);
   glutSolidCone(2.0,5.0,5,1);
   glPopMatrix();
}


void placeTrees() {

   float r = 35.0;
   float alpha;
   float rr;
   float x,z;

   srand(31457);
   int arvores = 0;

   while (arvores < ARVORES) {

      rr = rand() * 150.0/ RAND_MAX;
      alpha = rand() * 6.28 / RAND_MAX;

      x = cos(alpha) * (rr + r);
      z = sin(alpha) * (rr + r);

      if (fabs(x) < 128 && fabs(z) < 128) {

         glPushMatrix();
         glTranslatef(x,h(x+128, z+128),z);
         drawTree();
         glPopMatrix();
         arvores++;
      }
   }
}

void drawDonut() {

   glPushMatrix();
   glTranslatef(0.0,0.5,0.0);
   float color[] = {1.0,0.0,1.0,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
   glutSolidTorus(0.5,1.25,8,16);
   glPopMatrix();
}

void drawIndios() {

   float angulo;
   float color[] = {1.0,0.0,0.0,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
   for (int i = 0; i < INDIOS; i++) {
      
      angulo = i * 360.0/INDIOS + step * STEP_INDIO;
      glPushMatrix();
      glRotatef(angulo,0.0,1.0,0.0);
      glTranslatef(0.0,0.0,RAIO_INDIOS);
      glutSolidTeapot(1);
      glPopMatrix();
   }
}

void drawCowboys() {

   float angulo;
   float color[] = {0.0,0.0,1.0,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
   for (int i = 0; i < COWBOYS; i++) {
      
      angulo = i * 360.0/COWBOYS + step * STEP_COWBOY;
      glPushMatrix();
      glRotatef(-angulo,0.0,1.0,0.0);
      glTranslatef(RAIO_COWBOYS,0.0,0.0);
      glutSolidTeapot(1);
      glPopMatrix();
   }
}

void drawScene() {

   drawPlane();
   placeTrees();
   drawDonut();
   // move teapots up so that they are placed on top of the ground plane
   glTranslatef(0.0,1.0,0.0);
   drawCowboys();
   drawIndios();
}

float camH(float x, float z) {
   double intX, intZ;
   float fracX, fracZ;

   fracX = modf(x, &intX);
   fracZ = modf(z, &intZ);

   float alt1, alt2;

   alt1 = h(intX,     intZ) * (1 - fracZ) + h(intX,     intZ + 1) * fracZ;
   alt2 = h(intX + 1, intZ) * (1 - fracZ) + h(intX + 1, intZ + 1) * fracZ;

   return alt1 * (1 - fracX) + alt2 * fracX;
}

/*float alturaCamara(float x, float z){
   double intX, intZ;
   float fracX, fracZ;

   fracX = modf(x, &intX);
   fracZ = modf(z, &intZ);

   float alt1, alt2;
   
   alt1 = mapa->h(intX,     intZ) * (1 - fracZ) + mapa->h(intX,     intZ + 1) * fracZ;
   alt2 = mapa->h(intX + 1, intZ) * (1 - fracZ) + mapa->h(intX + 1, intZ + 1) * fracZ;

   return alt1 * (1 - fracX) + alt2 * fracX;
}*/

void renderScene(void) {

   float pos[4] = {-1.0, 1.0, 1.0, 0.0};

   glClearColor(0.0f,0.0f,0.0f,0.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();

   #define CAM 0
   #if CAM == 1
   gluLookAt(camX, h(camX+128, camZ+128) + 10, camZ,
            0, 0, 0,
           0.0f,1.0f,0.0f);
   #else
   camY = h(cX+128, cZ+128) + 2;
   gluLookAt(cX, camY, cZ,
           cX + cos(ang), camY, cZ + sin(ang),
           0.0f,1.0f,0.0f);
   #endif

   glLightfv(GL_LIGHT1,GL_POSITION, pos);

   drawScene();
   step++;

// End of frame
   glutSwapBuffers();
}



// escrever fun��o de processamento do teclado

void processKeys(unsigned char key, int xx, int yy) 
{
   switch(key) {
      case 'a':
      case 'A':
         ang-=0.02;
         break;

      case 'd':
      case 'D':
         ang+=0.02;
         break;

      case 'w':
      case 'W':
         cX += 0.3*cos(ang);
         cZ += 0.3*sin(ang);
         break;

      case 's':
      case 'S':
         cX -= 0.5   *cos(ang);
         cZ -= 0.5*sin(ang);
         break;
   }
}



void processMouseButtons(int button, int state, int xx, int yy) 
{
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


void processMouseMotion(int xx, int yy)
{

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
   camY = rAux *                           sin(betaAux * 3.14 / 180.0);


}


void init() {

// Colocar aqui load da imagem que representa o mapa de alturas
   ilInit();

   ilGenImages(1, &img_height);

   ilBindImage(img_height);
   ilLoadImage("terreno2.jpg");
   ilConvertImage(IL_LUMINANCE,IL_UNSIGNED_BYTE);
   height_w = ilGetInteger(IL_IMAGE_WIDTH);
   height_h = ilGetInteger(IL_IMAGE_HEIGHT);
   height_data = ilGetData();


// Colocar aqui o c�digo para carregar a imagem e criar uma textura
   ilGenImages(1, &img_text);
   ilBindImage(img_text);
   ilLoadImage("relva1.jpg");
   ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
   text_w = ilGetInteger(IL_IMAGE_WIDTH);
   text_h = ilGetInteger(IL_IMAGE_HEIGHT);
   text_data = ilGetData();

   grid_n = height_w;

   glGenTextures(1,&text_id); // unsigned int texID - variavel global;
   glBindTexture(GL_TEXTURE_2D,text_id);
   glTexParameteri(GL_TEXTURE_2D,               GL_TEXTURE_WRAP_S,        GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D,               GL_TEXTURE_WRAP_T,        GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D,               GL_TEXTURE_MAG_FILTER,    GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,               GL_TEXTURE_MIN_FILTER,    GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text_w, text_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, text_data);


// alguns settings para OpenGL
   glEnable(GL_DEPTH_TEST);
   //glEnable(GL_CULL_FACE);

// inicializa��o da luz
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

}


int main(int argc, char **argv) {

// inicializa��o
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
   glutInitWindowPosition(100,100);
   glutInitWindowSize(800,600);
   glutCreateWindow("CG@DI-UM");
      

// registo de fun��es 
   glutDisplayFunc(renderScene);
   glutIdleFunc(renderScene);
   glutReshapeFunc(changeSize);

// p�r aqui registo da fun��es do teclado e rato

   glutKeyboardFunc(processKeys);
   glutMouseFunc(processMouseButtons);
   glutMotionFunc(processMouseMotion);

// alguns settings para OpenGL
   glEnable(GL_DEPTH_TEST);
   //glEnable(GL_CULL_FACE);
   glEnable(GL_TEXTURE_2D);

// inicializa��o da luz
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

   init();


// entrar no ciclo do GLUT 
   glutMainLoop();

   return 0;
}