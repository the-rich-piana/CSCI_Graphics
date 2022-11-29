/*
 *  HW4
 *
 *  Key bindings:
 *  WASD    move fps
 *  m       Toggle ortho mode
 *  f       Toggle first person veiw on and off (higher priority than the other two view modes)
 *  z/x     Change FOV
 *  9          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
#define PI 3.1416

/* Define Globals */
double Ex = -1;
double Ez = 1;
double Ey = 1;
int axes = 1;       //  Display axes


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

//  Macro for sin & cos in degrees

#define LEN 8192

void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

/*
 *  Set projection
 */
static void Project()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //First person, or Ortho/Perspectives
   if(first_person) {
      gluPerspective(fov, asp, 0.1f, 100.f);
   }
   else {
      if (mode)
         gluPerspective(fov, asp, 0.1f, 100.f); 
      else
         glOrtho(-asp*state,+asp*state, -state, +state, -1000.f, 1000.f);
   }  
   //Manipulating matrix
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
/*
 *  Display the scene
 *  Taken from HW3 and Example 9
 */

static void drawSphere(double x, double y, double z, double cx, double cy, double cz, double r) 
{
   int th, ph;

   glPushMatrix();
   glTranslated(x, y, z);
   glScaled(r, r, r); //radius

   int divisions = 1;

   for (ph=-90; ph<90; ph += divisions){
      glBegin(GL_QUAD_STRIP);

      for (th=0; th<=360; th += divisions){
         glColor3f(cx, Sin(ph)*cy, cz);
         glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
         glVertex3d(Sin(th)*Cos(ph+divisions) , Sin(ph+divisions) , Cos(th)*Cos(ph+divisions));
      }
      glEnd();
   }

   glPopMatrix();
}

void display()
{
   const double len = 1.5;  //  Length of axes
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glLoadIdentity();

   if (first_person) {
      Cx = +2*state*Sin(rot); //Ajust the camera vector based on rot
      Cz = -2*state*Cos(rot);

      gluLookAt(Ex,Ey,Ez, Cx+Ex,Ey,Cz+Ez, 0,1,0); //  Use gluLookAt, y is the up-axis

   }
   //Cameras
   else {
      //Perspective view angle
      if (mode)
      {
         double px = -2*state*Sin(th)*Cos(ph);
         double py = +2*state        *Sin(ph);
         double pz = +2*state*Cos(th)*Cos(ph);
         gluLookAt(px,py,pz , 0,0,0 , 0,Cos(ph),0);
      }
      //Ortho view angle
      else
      {
         glRotatef(ph,1,0,0);
         glRotatef(th,0,1,0);
      }
   }

   //Cool spheres
    drawSphere(1, 0.1, -4,   0.1, 1, 1, 1);
    drawSphere(-10, 0.1, -3, 1, 1, 0.4, 1.5);
    drawSphere(-10, 1, 3,    1, 0.3, 1, 1);
    drawSphere(-5, 1, -5,    1, 1, 0.1, 2);
    drawSphere(10, 1, 10, 0.8, 0.9, 1, 1);
    drawSphere(-10, 1, -10, 0.8, 0.9, 1, 1);

   //  Draw axes
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
   //XY PLane
   glBegin(GL_QUADS);
   glColor4f(0.7, 0.7, 0.7, 0.5);
   glVertex3d(-10,-0.6 ,-10);
   glVertex3d(10  ,-0.6 ,-10);
   glVertex3d(10  ,-0.6 ,10);
   glVertex3d(-10 ,-0.6 ,10);
   glEnd();  
   glBegin(GL_QUADS);
   glColor4f(0.4, 0.4, 0.4, 0.5);
   glVertex3d(-30, -0.7 ,-30);
   glVertex3d(30  ,-0.7 ,-30);
   glVertex3d(30  ,-0.7 ,30);
   glVertex3d(-30 ,-0.7 ,30);
   glEnd();       

   glBegin(GL_QUADS);
   glColor4f(1, 0.1, 0, 0.5);
   glVertex3d(-1, -0.5 ,-1);
   glVertex3d(1  ,-0.5 ,-1);
   glVertex3d(1  ,-0.5 ,1);
   glVertex3d(-1 ,-0.5 ,1);
   glEnd();     
   //  Display parameters
   glWindowPos2i(10, 970);

   glColor4f(1, 0.1, 0, 0.5);
   if (first_person) {
      Print("first_person=On View Angle=%d",rot);
   }
   else {
      Print("first_person=Off Angle=%d,%d,  state=%.1f FOV=%d Projection=%s",th,ph,state,fov,mode?"Perpective":"Orthogonal");
   }
   //  Render the scene and make it visible
   glFlush();
   glutSwapBuffers();
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
   Project();
   glutPostRedisplay();
}

/*
 *  Key Bindings
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Toggle axes
   else if (ch == 'y')
      axes = 1-axes;
   //  Toggle first person
   else if (ch == 'f' || ch == 'F'){
      first_person = 1 - first_person;
   }


   double move = 0.01;
   if (first_person) {
      if (ch == 'w' || ch == 'W'){
         Ex += Cx*move; //Update the eye vector based on the camera vector
         Ez += Cz*move;
      }
      else if (ch == 'a' || ch == 'A'){
         rot -= 5;
      }
      else if (ch == 's' || ch == 'S'){
         Ex -= Cx*move;
         Ez -= Cz*move;
      }
      else if (ch == 'd' || ch == 'D'){
         rot += 5;
      }
      rot %= 360;
   }
   else {
      //  Reset view angle
      if (ch == '0')
         th = ph = 0;
      //  Switch display mode
      else if (ch == 'm' || ch == 'M')
         mode = 1 - mode;
      //  Change field of view angle
      else if (ch == 'z')
         fov--;
      else if (ch == 'x')
         fov++;
   }
   Project();
   glutPostRedisplay();
}

/*
 *  Window Resize
 */
void reshape(int width,int height)
{
   asp = (height>0) ? (double)width/height : 1;
   glViewport(0,0, width,height);
   Project();
}

int main(int argc,char* argv[])
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(1920,1080);
   glutCreateWindow("Homework 4");
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutMainLoop();
   return 0;
}

