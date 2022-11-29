#include "CSCIx229.h"

#define PI 3.1416

/* Define Globals */
double Ex = -1;
double Ez = 1;
double Ey = 1;
int axes = 1;       //  Display axes

//Textures
unsigned int texture[7]; // Texture names


//CAMERA SETTINGS
int mode = 1;       //  Ortho/Persp
int th = 20;         //  Azimuth of view angle
int ph = 20;         //  Elevation of view angle
int fov = 70;        //  Field of view (for perspective)
double asp = 1;      //  Aspect ratio
double state = 20.0; // 3d state space

//First Person Camera
int rot = 0.0;       //First person rotation
int first_person = 0;
double Cx = 0; 
double Cz = 0; 

int move = 0;

// LIGHTING
int one       =   1;  // Unit value
int distance  =   30;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   .9;  // Specular intensity (%)
int shininess =   .5;  // Shininess 
float shinyvec[1];    // Shininess 
int zh        =  90;  // Light azimuth
float ylight  =   30;  // Elevation of light

typedef struct {
   double x;
   double y;
   double z;
} points_t;

/*
 *  Draw vertex in polar coordinates with normal
 *  Adapted from ex13
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}


static void drawSphere(double x, double y, double z, double cx, double cy, double cz, double r) 
{
   int th, ph;

   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   
   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   glTranslated(x, y, z);
   glScaled(r, r, r); //radius

   int divisions = 1;

   for (ph=-90; ph<90; ph += divisions){
      glBegin(GL_QUAD_STRIP);

      for (th=0; th<=360; th += divisions){
         glColor3f(cx, Sin(ph)*cy, cz);
//         glNormal3d(Cos(th), Sin(th), Sin(th));
//        glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
//         glVertex3d(Sin(th)*Cos(ph+divisions) , Sin(ph+divisions) , Cos(th)*Cos(ph+divisions));
         Vertex(th, ph);
         Vertex(th, ph+divisions);
      }
      glEnd();
   }  

   glPopMatrix();
}
/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 *  Adapted from ex13
 */
static void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.1 * emission, 10.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,0.4);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   
   //  Undo transofrmations
   glPopMatrix();
}

void drawCylinder(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th) {
   double radius = 0.3;
   double height = 0.2;

   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};

   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

   glPushMatrix();

   //  Transform cylinder
   glTranslated(x,y,z);
   glRotated(th,0,0,1);
   glScaled(dx,dy,dz);
   
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

   glBindTexture(GL_TEXTURE_2D, texture[0]);
   int j;
   glBegin(GL_TRIANGLE_STRIP);
   for (j = 0; j <= 360; j++) {
      const float texCoord = (j / (float) 360);

      double x = radius * Cos(j);
      double y = height;
      double z = radius * Sin(j);

      //glColor3f(j/306, j/360, j/360);
      glNormal3d(Cos(j), 1, Sin(j));
      glTexCoord2f(-texCoord, 0.0); glVertex3d(x, -y, z);
      glTexCoord2f(-texCoord, 1.0); glVertex3d(x, y, z);
   }
   glEnd();
   double i; 
   glNormal3d(0,1,0);

   /* Top of Cylinder */
   glBegin(GL_TRIANGLE_FAN);
      glVertex3d(0.0, height, 0.0);
      for(i = 0.0; i < 360; i+=.125) {
         glVertex3d(radius * cos(i), height, radius * sin(i));
      }
   glEnd();

   glNormal3d(0,-1,0);

   /* Bottom of Cylinder */
   glBegin(GL_TRIANGLE_FAN);
      glVertex3d(0.0, -height, 0.0);
      for(i = 0.0; i < 360; i+=.125) {
         glVertex3d(radius * cos(i), -height, radius * sin(i));
      }

   glEnd();
   glPopMatrix(); 
   glDisable(GL_TEXTURE_2D);
}

/*
 *  Set projection
 */
static void myProject()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if(first_person) {
      gluPerspective(fov, asp, 0.1f, 100.f);
   }
   else {
      if (mode)
         gluPerspective(fov, asp, 0.1f, 100.f); 
      else
         glOrtho(-asp*state,+asp*state, -state, +state, -1000.f, 1000.f);
   }  
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

static void drawXYPlane(double grid_length, double h, int tex){

   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};

   glPushMatrix();
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);


   if(tex) glEnable(GL_TEXTURE_2D);
   if(tex) glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   if(tex) glBindTexture(GL_TEXTURE_2D, texture[2]);
   
   glBegin(GL_QUADS);
   //glEnable(GL_NORMALIZE);
   glNormal3f(0, 1, 0);
   // for(double i = 0; i < grid_length; i+= 1){
   //    for(double j = 0; j < grid_length; j+=1){
   //       glTexCoord2f(0,0); glVertex3f(-i/3, h ,-j/3);
   //       glTexCoord2f(1,0); glVertex3f(i/3, h  ,-j/3);
   //       glTexCoord2f(1,1); glVertex3f(i/3, h  ,j/3);
   //       glTexCoord2f(0,1); glVertex3f(-i/3, h ,j/3);
   //    }
   // }
   glTexCoord2f(0,0); glVertex3f(-grid_length, h, -grid_length);
   glTexCoord2f(1,0); glVertex3f(+grid_length, h, -grid_length);
   glTexCoord2f(1,1); glVertex3f(+grid_length, h, +grid_length);
   glTexCoord2f(0,1); glVertex3f(-grid_length, h, grid_length);   
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D); 

}

/*
 *  Display the scene
 *  Taken from HW3 and Example 9
 */
void display()
{
   const double len=1.5;
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glClearColor(0.7,0.7,0.7,0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
   glLoadIdentity();

   if (first_person) {
      Cx = +2*state*Sin(rot);
      Cz = -2*state*Cos(rot);

      gluLookAt(Ex,Ey,Ez, Cx+Ex,Ey,Cz+Ez, 0,1,0);
   }
   else {
      //  Perspective 
      if (mode)
      {
         double px = -2*state*Sin(th)*Cos(ph);
         double py = +2*state        *Sin(ph);
         double pz = +2*state*Cos(th)*Cos(ph);
         gluLookAt(px,py,pz , 0,0,0 , 0,Cos(ph),0);
      }
      //  Orthogonal
      else
      {
         glRotatef(ph,1,0,0);
         glRotatef(th,0,1,0);
      }
   }

   glShadeModel(GL_SMOOTH);
   float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
   float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
   float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
   float Position[]  = {distance*Cos(zh), ylight, distance*Sin(zh), .80};
   glColor3f(1,1,1);

   ball(Position[0], Position[1], Position[2], 0.4);

   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHT0);

   glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
   glLightfv(GL_LIGHT0,GL_POSITION,Position);

   //DRAW SHAPES
   glColor3f(1, 1, 1);
   drawCylinder(0, +2, 9, 5,  30, 5, 10 );
   drawCylinder(9, +2, 0, 5,  30, 5, -10 );
   drawCylinder(9, +2, -9, 5, 30, 5, 5 );
   drawCylinder(-9, +2, -9, 5,30, 5, 2 );
   drawCylinder(9, +2, 9, 5,  30, 5, 5 );
   drawCylinder(-9, +2, 9, 5, 30, 5, -5 );
   drawCylinder(0, +2, -9, 5, 30, 5, -1 );
   drawCylinder(-9, +2, 0, 5, 30, 5, 0 );

   drawSphere(0.1, 0.1, 0.1,   1, 0.4, 0.1, 1);
   // drawSphere(-10, 0.1, -3, 1, 1, 0.4, 1.5);
   // drawSphere(-10, 1, 3,    1, 0.3, 1, 1);
   // drawSphere(-5, 1, -5,    1, 1, 0.1, 2);

   glColor3f(0.7, 0.7 , 0.7);
   drawXYPlane(5, -1.9, 0);   
   glColor3f(0.8,0.8,0.8);
   drawXYPlane(11, -2, 1);   
   glColor3f(1,1,1);
   drawXYPlane(30, -2.3, 1);


//  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   glColor4f(0.9, 0.5, 0, 0.5);

   //  Display parameters
   glWindowPos2i(10, 900);
   if (first_person) {
      Print("first_person=On View Angle=%d",rot);
   }
   else {
      Print("first_person=Off Angle=%d,%d  state=%.1f FOV=%d Projection=%s",th,ph,state,fov,mode?"Perpective":"Orthogonal");
   }
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 *  Adopted from ex13
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/3000.0;
   zh = fmod(90*t, 360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   if(!first_person) {
      if (key == GLUT_KEY_RIGHT)
         th += 5;
      else if (key == GLUT_KEY_LEFT)
         th -= 5;
      else if (key == GLUT_KEY_UP)
         ph += 5;
      else if (key == GLUT_KEY_DOWN)
         ph -= 5;
      else if (key == GLUT_KEY_PAGE_UP && state>1)
         state -= 0.1;
      else if (key == GLUT_KEY_PAGE_DOWN)
         state += 0.1;
      th %= 360;
      ph %= 360;
   }
   myProject();
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   else if (ch == '9')
      axes = 1-axes;
   else if (ch == ' ') {
      move = 1-move;
   }
   else if (ch == '<')
      zh += 3;
   else if (ch == '>')
      zh -= 3;
   else if (ch == 'f' || ch == 'F')
   {
      first_person = 1-first_person;
   }

   if (first_person) {
      double dt = 0.05;
      if (ch == 'w' || ch == 'W'){
         Ex += Cx*dt; 
         Ez += Cz*dt;
      }
      else if (ch == 'a' || ch == 'A'){
         rot -= 3;
   glNormal3f(0, 1, 0);
   // for(double i = 0; i < grid_length; i+= 1){
   //    for(double j = 0; j < grid_length; j+=1){
   //       glTexCoord2f(0,0); glVertex3f(-i/3, h ,-j/3);
   //       glTexCoord2f(1,0); glVertex3f(i/3, h  ,-j/3);
   //       glTexCoord2f(1,1); glVertex3f(i/3, h  ,j/3);
   //       glTexCoord2f(0,1); glVertex3f(-i/3, h ,j
      }
      else if (ch == 's' || ch == 'S'){
         Ex -= Cx*dt;
         Ez -= Cz*dt;
      }
      else if (ch == 'd' || ch == 'D'){
         rot += 3;
      }
      rot %= 360;
   }
   else {
      if (ch == '0')
         th = ph = 0;
      else if (ch == 'm' || ch == 'M')
         mode = 1-mode;
      else if (ch == 'z')
         fov--;
      else if (ch == 'x')
         fov++;
   }
   
   myProject();
   glutIdleFunc(move?idle:NULL);
   glutPostRedisplay();
}


void reshape(int width,int height)
{
   asp = (height>0) ? (double)width/height : 1;
   glViewport(0,0, width,height);
   myProject();
}


int main(int argc,char* argv[])
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(1920,1080);
   glutCreateWindow("Homework 6");
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //texture[0] = LoadTexBMP("uv_map.bmp");
   texture[0] = LoadTexBMP("pillar.bmp");
   texture[1] = LoadTexBMP("crate.bmp");
   texture[2] = LoadTexBMP("brick_floor_diffuse.bmp");


   ErrCheck("init");
   glutMainLoop();
   return 0;
}