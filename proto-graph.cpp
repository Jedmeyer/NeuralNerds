#include<fstream>
#include<iostream>
#include<iomanip>
#include<sstream>
using namespace std;
#include<vector>
#ifdef MACOSX
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<stdlib.h>
#include<math.h>
#include<string.h>

/* To do list in 2k16 lul
   Connect the dots :D
   Pause button :I
 */


int WIDTH = 650;  // width of the user window
int HEIGHT = 400;  // height of the user window

int originx = 50, originy = 50, yaxispeak = HEIGHT - 50, xaxispeak = WIDTH - 200;
int xrange = xaxispeak-originx;
int yrange = yaxispeak-originy;

int statusx1 = xaxispeak + 25;
int statusx2 = WIDTH - 50;
int statusy1 = yaxispeak;
int statusy2 = yaxispeak - 85;

// gen data struct, each genData holds the data for a generation
struct genData
{
  int high;
  int ave;
  genData(int highScore, int aveScore)
  {
    high = highScore;
    ave = aveScore;
  }
};


//initialize the vector to hold the data :D
  vector<genData> gens;


//This sets the modifiers to scale the graph
double xmodifier = 1;
double ymodifier = 1;
int highestScore;


void setModifiers()
{
  xmodifier = (double)xrange / (double)gens.size();
  ymodifier = (double)yrange / (double)highestScore;
}

//updates gens (called in idle function)
void updateGens()
{
  int trash;
  ifstream g("Testinput.txt");
  for(unsigned int i = 0; i < 3*gens.size(); i++)
    g >> trash;

  if (g >> trash)
    {
      int hScore;
      int aScore;
      
      g >> hScore;
      g >> aScore;
      
      if(hScore > highestScore)
	highestScore = hScore;

      genData newGD(hScore, aScore);
      gens.push_back(newGD);
      
      setModifiers();
    }
}


char programName[] = "proto-graph";

// the drawText function draws some text at location x, y
//   note:  the text to be drawn is a C-style string!
void drawText(float x, float y, const char *text)
{
  glRasterPos2f( x, y );
  int length = strlen(text);
  for (int i = 0; i < length; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

// the drawNumber function draws a number at location x, y
void drawNumber(double x, double y, double num)
{
  stringstream oss;
  oss << num; oss.flush();
  drawText(x, y, oss.str().c_str());
}


//plots xvalues and yvalues
void plotPoints()
{
  glBegin(GL_POINTS);
  for(unsigned int i = 0; i < gens.size(); i++)
    {
      glColor3f(1., 1., 0);
      glVertex2f(originx + ((1+i) * xmodifier), originy + (gens[i].high  * ymodifier));
      glColor3f(1., 0, 0);
      glVertex2f(originx + ((1+i) * xmodifier), originy + (gens[i].ave  * ymodifier));
    }
  glEnd();
}



// the display function actually does the work of drawing in the window.
//   this function will be called every time the appearance of the window
//   needs to be remade.
void display()
{
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // draw the axis for the graph
  glColor3f(1.,1.,1.); // white
  glBegin(GL_LINE_STRIP);
  glVertex2f( xaxispeak, originy);
  glVertex2f( originx, originy);
  glVertex2f( originx, yaxispeak);
  glEnd();

  // draw the labels
  drawText(((originx + xaxispeak)/2-50) , originy - 25, "Generation");
  drawText(originx - 25, (originy + yaxispeak)/2, "Fit");

  
  // draw the limits of the graph/axis
  drawNumber(originx - 25, originy, 0);
  drawNumber(originx, originy - 25, 0);
  drawNumber(originx - 35, yaxispeak, highestScore);
  drawNumber(xaxispeak, originy - 25, gens.size());
  
  
  //plot the points
  plotPoints();

  //draw the status box
  glColor3f(1.,1.,1.); // white
  glBegin(GL_LINE_STRIP);
  glVertex2f(statusx1,statusy1);
  glVertex2f(statusx2, statusy1);
  glVertex2f(statusx2, statusy2);
  glVertex2f(statusx1 , statusy2);
  glVertex2f(statusx1, statusy1);
  glEnd();

  //write 'Key'
  drawText( statusx1 + (statusx2-statusx1)/3 + 5 , statusy1 - 22, "Key");
  glColor3f(1.,1.,1.); // white
  glBegin(GL_LINE_STRIP);
  glVertex2f(statusx1, statusy1 - 30);
  glVertex2f(statusx2, statusy1 - 30);
  glEnd();

  //write 'Highest' in gold
  glColor3f(1., 1., 0); // gold
  drawText( statusx1 + (statusx2-statusx1)/3 - 10, statusy1 - 50, "Highest");
      
  //write 'Average' in red
  glColor3f(1., 0, 0); // red
  drawText( statusx1 + (statusx2-statusx1)/3 - 12, statusy1 - 75, "Average");
   
  // tell the graphics card that we're done-- go ahead and draw!
  glutSwapBuffers();
}


// process keyboard events
void keyboard( unsigned char c, int x, int y )
{
  int win = glutGetWindow();
  switch(c) {
    case 'q':
    case 'Q':
    case 27:
      // get rid of the window (as part of shutting down)
      glutDestroyWindow(win);
      exit(0);
      break;
    case '\b':
      break;
    default:
      break;
  }
  glutPostRedisplay();
}


// the reshape function handles the case where the user changes the size
//   of the window.  We need to fix the coordinate
//   system, so that the drawing area is still the unit square.
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   WIDTH = w;  HEIGHT = h;
   
   //dynamic size
   yaxispeak = HEIGHT - 50;
   xaxispeak = WIDTH - 200;
   xrange = xaxispeak-originx;
   yrange = yaxispeak-originy;
   statusx1 = xaxispeak + 25;
   statusx2 = WIDTH - 50;
   statusy1 = yaxispeak;
   statusy2 = yaxispeak - 85;
   setModifiers();
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0., WIDTH-1, 0., HEIGHT-1, -1.0, 1.0);
}

// Constant refreshing of values
void idle()
{
  updateGens();
  glutPostRedisplay();
}

// the init function sets up the graphics card to draw properly
void init(void)
{
  // clear the window to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, 0., HEIGHT-1, -1.0, 1.0);

  // set up how points and lines will be drawn.  The following
  //  commands make points and lines look nice and smooth.
  glPointSize(3);
  glLineWidth(1.5);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

  // welcome message
  cout << "Welcome to " << programName << "." << endl;
}

// init_gl_window is the function that starts the ball rolling, in
//  terms of getting everything set up and passing control over to the
//  glut library for event handling.  It needs to tell the glut library
//  about all the essential functions:  what function to call if the
//  window changes shape, what to do to redraw, handle the keyboard,
//  etc.
void init_gl_window()
{
  char *argv[] = {programName};
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100,100);
  glutCreateWindow(programName);
  init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
}

int main()
{
  /*
    setValues();
    cout << endl;
  */
  //setValues2();
  //setModifiers();
  init_gl_window();
}

