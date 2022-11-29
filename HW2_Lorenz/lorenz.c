
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int theta =0;
int phi =0;         
int axes=1;       
int mode=0;       

/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;

double lorenz_points[1000][3];

//  Cosine and Sine in degrees

#define Cos(x) (cos((x)*3.14 / 180))
#define Sin(x) (sin((x)*3.14 / 180))

#define LEN 8192  //  Maximum lengthetaof text string


void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   va_start( args, format);
   vsnprintf(buf, LEN, format, args);
   va_end(args);
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();
   glRotatef(phi, 1, 0, 0);
   glRotatef(theta, 0, 1, 0);

   /* Z BUFFER */
   if (mode==2 || mode==3)
      glEnable(GL_DEPTH_TEST);
   else
      glDisable(GL_DEPTH_TEST);
   if (mode!=2)
      glEnable(GL_CULL_FACE);
   else
      glDisable(GL_CULL_FACE);

   int i;
   double x = 1;
   double y = 1;
   double z = 1;
   double dt = 0.001;

   const double axis_len = 0.1;  //  Length aof axes
   glBegin(GL_LINE_STRIP);
   
   for (i=0;i<50000;i++)
   {
      double dx = s*(y-x);
      double dy = x*(r-z)-y;
      double dz = x*y - b*z;
      x += dt*dx;
      y += dt*dy;
      z += dt*dz;

      glColor3f((double)i/50000.0, 0.2, 0.3);
      glVertex3d(x*0.03, y*0.03, z*0.03);
   }
   glEnd();
      
   glColor3f(1,0.4,1);
   //  Draw axes
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(axis_len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,axis_len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,axis_len);
      glEnd();
      //  Label axes
      glRasterPos3d(axis_len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,axis_len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,axis_len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   //  Print the text string
   Print("Angle=%d,%d Sigma=%d, beta=%f, rho=%d", theta,phi, (int)s, b, (int)r);//ADD VALUES HERE
   glFlush();
   glutSwapBuffers();
}

void special(int key, int x, int y)
{
   if (key == GLUT_KEY_RIGHT)
      theta+= 5;   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      theta-= 5;
   else if (key == GLUT_KEY_UP)
      phi+= 5;
   else if (key == GLUT_KEY_DOWN)
      phi-= 5;
   theta%= 360;
   phi%= 360;
   glutPostRedisplay();
}


void key(unsigned char ch,int x,int y)
{
   if (ch == '0')
      theta= phi= 0;
   /*Change sigma */
   else if (ch=='s'|| ch == 'S')
     s -= 1; 
   else if (ch=='w'|| ch == 'W')
     s += 1; 


   glutPostRedisplay();
}

void reshape(int width,int height)
{
   GLdouble zNear = -10;
   GLdouble zFar = 1000000000;
   glViewport(0,0, width,height);
   gluPerspective(60, (float)(width) / (height), zNear, zFar);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(720 * 2, 480 *2);
   glutCreateWindow("Lorenz Attractor");
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutMainLoop();

   return 0;
}