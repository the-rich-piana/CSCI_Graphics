#include "CSCIx229.h"

int theta = 30;
int phi = 10;         
int axes=1;       
int mode=0;       
int fov = 70;
int asp = 1;
int dim = 30;

double Exx = -1;
double Eyy = 1;
double Ezz = 1;
//  Cosine and Sine in degrees


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

void drawCylinder(double x, double y, double z, double dx,double dy,double dz, double th) {
   double radius1 = 0.3;
   double radius2 = 0.3;

   double height = 0.2;

   glPushMatrix();
   //  Transform cylinder
   glTranslated(x,y,z);
   glRotated(th,0,0,1);
   glScaled(dx,dy,dz);

   int j;
   glBegin(GL_TRIANGLE_STRIP);
   for (j = 0; j <= 360; j++) {
      double x = radius1 * Cos(j);
      double y = height;
      double z = radius1 * Sin(j);

      //glColor3f(j/306, j/360, j/360);
      glVertex3d(x, y, z);
      glVertex3d(x, -y, z);
   }
   glEnd();
   double i; 

   /* Top of Cylinder */
   glBegin(GL_TRIANGLE_FAN);
      glVertex3d(0.0, height, 0.0);
      for(i = 0.0; i < 360; i+=.125) {
         glVertex3d(radius2 * cos(i), height, radius2 * sin(i));
      }
   glEnd();
   /* Bottom of Cylinder */
   glBegin(GL_TRIANGLE_FAN);
      glVertex3d(0.0, -height, 0.0);
      for(i = 0.0; i < 360; i+=.125) {
         glVertex3d(radius1 * cos(i), -height, radius1 * sin(i));
      }
   glEnd();

   glPopMatrix(); 
}
/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glClearColor(0.7,0.7,0.7,0);

  glLoadIdentity(); //loads identity matrix to clear previous transformations
  //double Ex = Exx*dim*Sin(theta)*Cos(phi);
  //double Ey = Eyy*dim        *Sin(phi);
  //double Ez = Ezz*dim*Cos(theta)*Cos(phi);
    gluLookAt(Exx*dim*Sin(theta)*Cos(phi) ,Eyy*dim        *Sin(phi), Ezz*dim*Cos(theta)*Cos(phi) , 0,0,0 , 0,Cos(phi),0); //Perspective code borrowed from ex9   

   glRotatef(phi, 1, 0, 0);
   glRotatef(theta, 0, 1, 0);
   glEnable(GL_DEPTH_TEST); //Enable z buffering
   const double axis_len = 1;  //  Length aof axes
   
    glColor3f(0.75, 0.4, 0.0);
    drawCylinder(0, 0, 0, 6, 15, 6, 1);
    glColor3f(0.8, 0.4, 0.0);
    drawCylinder(0, -2, 0, 8, 13, 8, 1);
    glColor3f(0.86, 0.4, 0.0);
    drawCylinder(0, -3, 0, 10, 7, 10, 1);
    glColor3f(0.3, 0.1, 0.1);
    drawCylinder(0, -8, 0, 2, 20, 2, 1);


    glColor3f(0.8, 0.5, 0.0);
    drawCylinder(5, 0, 5, 7, 15, 7, 1);
    glColor3f(0.85, 0.5, 0.0);
    drawCylinder(5, -3, 5, 9, 13, 9, 1);
    glColor3f(0.89, 0.5, 0.0);
    drawCylinder(5, -7, 5, 11, 7, 11, 1);
    glColor3f(0.3, 0.1, 0.1);
    drawCylinder(5, -8, 5, 2, 20, 2, 1);

    glColor3f(0.92, 0.6, 0.1);
    drawCylinder(-10, 2, -8, 5, 13, 5, 0.7);
    glColor3f(0.88, 0.6, 0.0);
    drawCylinder(-10, -3, -8, 7, 12, 7, 0.7);
    glColor3f(0.85, 0.5, 0.0);
    drawCylinder(-10, -7, -8, 8, 7, 8, 0.7);
    glColor3f(0.3, 0.1, 0.1);
    drawCylinder(-10, -8, -8, 2, 20, 2, 1);

    glColor3f(0.8, 0.5, 0.0);
    drawCylinder(-10, 0, 4, 7, 19, 7, 1);
    glColor3f(0.85, 0.5, 0.0);
    drawCylinder(-10, -3, 4, 9, 13, 9, 1);
    glColor3f(0.89, 0.5, 0.0);
    drawCylinder(-10, -7, 4, 10, 7, 10, 1);
    glColor3f(0.3, 0.1, 0.1);
    drawCylinder(-10, -8, 4, 2, 20, 2, 1);    


    glBegin(GL_QUADS);

    glColor3f(0.6,0.7,0.1);
    glVertex3f(20, -10, 20);
    glVertex3f(20, -10, -20);
    glVertex3f(-20, -10, -20);
    glVertex3f(-20, -10, 20);

    glColor3f(0.3,0.15,0.1);
    glVertex3f(-15, -5, 15);
    glVertex3f(-15, -8, 15);
    glVertex3f(-15, -8, -15);
    glVertex3f(-15, -5, -15);    

     glColor3f(0.3,0.15,0.1);
    glVertex3f(-15, -5, 15);
    glVertex3f(-15, -8, 15);
    glVertex3f(15, -8, 15);
    glVertex3f(15, -5, 15);      

     glColor3f(0.3,0.15,0.1);
    glVertex3f(-15, -5, -15);
    glVertex3f(-15, -10, -15);
    glVertex3f(15, -10, -15);
    glVertex3f(15, -5, -15);      

    glEnd();
   //  Draw axes
   glColor3f(1,1,1);
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
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   //  Print the text string
//   Print("Angle=%d,%d Sigma=%d, beta=%f, rho=%d", theta,phi, (int)s, b, (int)r);//ADD VALUES HERE

   glFlush();
   glutSwapBuffers();
}

static void Project()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluPerspective(fov, asp, 0.1f, 100.f); 

    //glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int x, y, z=0;
void special(int key, int x, int y)
{
   if (key == GLUT_KEY_RIGHT)
      theta+= 2;   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      theta-= 2;
   else if (key == GLUT_KEY_UP)
      phi += 2;
   else if (key == GLUT_KEY_DOWN)
      phi -= 2;
 
   theta %= 360;
   phi %= 360;
   Project();
   glutPostRedisplay();
}

void key(unsigned char ch,int x,int y)
{
   if (ch == '0')
      theta= phi= 0;
    else if(ch == 'w'){
        Exx += .1;
    }
    else if(ch == 's'){
        Exx -= .1;
    }    
    else if(ch == 'a'){
        Eyy += .1;
    }  
    else if(ch == 'd'){
        Eyy -= .1;
    }            
    Project();
   glutPostRedisplay();
}

void reshape(int width,int height)
{
    glViewport(1, 1, width,height);
    //gluPerspective(fov, asp, dim/4,4*dim);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-dim*asp,+dim*asp, -dim,+dim, -dim,+dim);   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Project();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(1920/2, 1080/2);
   glutCreateWindow("Giuliano Costa");
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutMainLoop();

   return 0;
}