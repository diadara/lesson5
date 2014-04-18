//
// This code was created by Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
//
// If you've found this code useful, please let me know.
//
// Visit me at www.demonews.com/hosted/nehe 
// (email Richard Campbell at ulmont@bellsouth.net)
//
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // needed to sleep
#include <stdio.h>
#include<math.h>

/* ASCII code for the escape key. */
#define ESCAPE 27

#define hdistance 2.0f
#define nradius  0.4f
#define hradius  0.05f
#define ndistance  3.0f
#define nangle 30.0f
#define RANGLE 5
float PIby180 = 3.14/180;
/* The number of our GLUT window */
int window; 

float z = 0.0f;
float rx = 0.0f;
float ry = 0.0f;
float rz = 0.0f;
float tr = 0.0f;



/* rotation angle for the triangle. */


/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);			        // The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);		        // Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene()
{

  //  GLfloat y;        // Storage for varying Y coordinate
  //  GLfloat fSizes[2];      // Line width range metrics
  //  GLfloat fCurrSize;      // Save current size
  //  glGetFloatv(GL_LINE_WIDTH_RANGE,fSizes);
  //  fCurrSize = fSizes[0];
  //  printf("\n line width range %f %f",fSizes[0],fSizes[1]);


  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
  glLoadIdentity();				// Reset The View

  glTranslatef(0.0f,0.0f,z);	/* For zooming */
  glTranslatef(tr,0.0f,0.0f);
  glRotatef(ry,0.0f,1.0f,0.0f);	/* For rotation along y axis */
  glRotatef(rx,1.0f,0.0f,0.0f);	/* For rotation along x axis */
  glRotatef(rz,0.0f,0.0f,1.0f);	/* For rotation along z axis */

  for(int i =0;i<20;i++)
    {
      glRotatef(nangle,0.0f,0.0f,1.0f);
      glTranslatef(0.0f,0.0f,ndistance);
      // draw a pyramid (in smooth coloring mode)

      glPushMatrix();
      glTranslatef(-hdistance,0.0f,0.0f);
      glColor3f(0.0f,0.0f,1.0f);			// Blue
      glutSolidSphere(nradius, 100, 100);
      GLUquadricObj *p = gluNewQuadric();
      gluQuadricDrawStyle(p,GLU_LINE);
      glPushMatrix();
      glRotatef(90,0.0,1.0f,0.0f );
      glColor3f(0.0f,1.0f,0.0f);
      gluCylinder(p,hradius,hradius,2*hdistance,100,100);
      glPopMatrix();

  
      glTranslatef(2*hdistance,0.0f,0.0f);
      glColor3f(1.0f,0.0f,0.0f);			// Red
      glutSolidSphere(nradius, 100, 100);
      glPopMatrix();

      glColor3f(0.0f,1.0f,1.0f);
      glLineWidth(5.0f);
      glBegin(GL_LINES);
      glVertex3f(hdistance,0.0f,0.0f);
      glVertex3f(hdistance*cos(nangle *PIby180),hdistance*sin(nangle *PIby180),ndistance);


      glVertex3f(-hdistance,0.0f,0.0f);
      glVertex3f(-hdistance*cos(nangle *PIby180),-hdistance*sin(nangle *PIby180),ndistance);
      
      
      glEnd();
    }
  /* rtri+=0.20f;					// Increase The Rotation Variable For The Pyramid */
  /* rquad-=0.20f;					// Decrease The Rotation Variable For The Cube */

  // swap the buffers to display, since double buffering is used.
  glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
  printf("\n You pressed %c ",key);
  /* avoid thrashing this call */
  usleep(100);

  /* If escape is pressed, kill everything. */
  switch(key)
    {
    case ESCAPE:
      /* shut down our window */
      glutDestroyWindow(window); 
      /* exit the program...normal termination. */
      exit(0);
      break;                    /* redundant */
    case 'z':
      z -= 0.1f;
      break;
    case 'Z':
      z += 0.1f;
      break;
    case 't':
      tr -= 0.1f;
      break;
    case 'T':
      tr += 0.1f;
      break;
      case 'Q':
      rx += RANGLE;
      break;
    case 'q':
      rx-= RANGLE;
      break;
    case 'W':
      ry += RANGLE;
      break;
    case 'w':
      ry-= RANGLE;
      break;
    case 'E':
      rz += RANGLE;
      break;
    case 'e':
      rz-= RANGLE;
      break;
    
    
    default:
      printf("\nthat doesn't do anything yet");
      break;
    }
}

int main(int argc, char **argv) 
{  
  /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
  glutInit(&argc, argv);  

  /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported 
     Depth buffered for automatic clipping */  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

  /* get a 640 x 480 window */
  glutInitWindowSize(640, 480);  

  /* the window starts at the upper left corner of the screen */
  glutInitWindowPosition(0, 0);  

  /* Open a window */  
  window = glutCreateWindow("Jeff Molofee's GL Code Tutorial ... NeHe '99");  

  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&DrawGLScene);  

  /* Go fullscreen.  This is as soon as possible. */
  glutFullScreen();

  /* Even if there are no events, redraw our gl scene. */
  glutIdleFunc(&DrawGLScene);

  /* Register the function called when our window is resized. */
  glutReshapeFunc(&ReSizeGLScene);

  /* Register the function called when the keyboard is pressed. */
  glutKeyboardFunc(&keyPressed);

  /* Initialize our window. */
  InitGL(640, 480);
  
  /* Start Event Processing Engine */  
  glutMainLoop();  

  return 1;
}




