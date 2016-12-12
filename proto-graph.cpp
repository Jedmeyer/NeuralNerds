#include<iostream>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include<bitset>
#include<ctime>
#include<random>
#include<stdexcept>
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





int Button_save_x[2];
int Button_save_y[2];
char Button_save_label[] = {'S','a','v','e','\0'};
char Button_load_label[] = {'L','o','a','d','\0'};
char generation_label[] = {'G','e','n','e','r','a','t','i','o','n',' ','#',':',' ','\0'};
char chromosome_label[] = {'C','h','r','o','m','o','s','o','m','e',' ','#',':',' ','\0'};
char * genome_label;
int Button_load_x[2] = {0,10};
int Button_load_y[2] = {0,10};
int Button_play[2];
bool mouseIsDragging = false;




int WIDTH = 650;  // width of the user window
int HEIGHT = 400;  // height of the user window

int originx = 50, originy = 50, yaxispeak = HEIGHT - 50, xaxispeak = WIDTH - 200;
int xrange = xaxispeak-originx;
int yrange = yaxispeak-originy;

int statusx1 = xaxispeak + 25;
int statusx2 = WIDTH - 50;
int statusy1 = yaxispeak;
int statusy2 = yaxispeak - 140;


// make and fill the test arrays (setValues or setValues2 is called immediately in main)
const int NUM_VALUES = 10;
const int POP = 10;
string NUM_VAL = to_string(NUM_VALUES);
double *xvalues = new double[NUM_VALUES];
double *yvalues = new double[NUM_VALUES];
double **yvalues2 = new double*[NUM_VALUES];
double highesty = 0;





void setValues()
{
  for(int i = 0; i < NUM_VALUES; i++)
    xvalues[i] = i+1;
  
  for(int i = 0; i <  NUM_VALUES; i++)
    {
      yvalues[i] = (i+1) * (i+1);
      //yvalues[i] = sqrt(100*(i+1));
      if (highesty < yvalues[i])
	highesty = yvalues[i];
    }
}

void setValues2()
{
  for(int i = 0; i < NUM_VALUES; i++)
    xvalues[i] = i+1;
  
  for(int i = 0; i <  NUM_VALUES; i++)
    {
      yvalues2[i] = new double[POP];
      for(int j = 0; j < POP; j++){
	       yvalues2[i][j] = (sqrt(100*(i+1))) + j;
	       if (highesty < yvalues2[i][j])
	         highesty = yvalues2[i][j];
	       }
    }
}

//This sets the modifiers to scale the graph
double xmodifier = 1;
double ymodifier = 1;
void setModifiers()
{
  xmodifier = (double)xrange / (double)NUM_VALUES;
  ymodifier = (double)yrange / highesty;
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
  glColor3f(1., 1., 1.);
  glBegin(GL_POINTS);
  for(int i = 0; i < NUM_VALUES; i++)
    glVertex2f(originx + (xvalues[i] * xmodifier), originy + (yvalues[i] * ymodifier));
  glEnd();
}

void plotPoints2()
{
  glColor3f(1., 1., 1.);
  glBegin(GL_POINTS);
  for(int i = 0; i < NUM_VALUES; i++)
    {
      for(int j = 0; j < POP; j++)
	{
	  glVertex2f(originx + (xvalues[i] * xmodifier), originy + (yvalues2[i][j] * ymodifier));
	}
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
  drawNumber(originx - 35, yaxispeak, highesty);
  drawNumber(xaxispeak, originy - 25, NUM_VALUES);

  //plot the points
  //plotPoints();
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

  //write 'Status'
  drawText( statusx1 + (statusx2-statusx1)/3 - 5, statusy1 - 22, "Status");
  glColor3f(1.,1.,1.); // white
  glBegin(GL_LINE_STRIP);
  glVertex2f(statusx1, statusy1 - 30);
  glVertex2f(statusx2, statusy1 - 30);
  glEnd();

  //write 'Generation' and the number
  drawText( statusx1 + (statusx2-statusx1)/3 - 22, statusy1 - 50, "Generation");
  int sampleGen = 10;
  drawNumber( statusx1 + (statusx2-statusx1)/2 - 9, statusy1 - 75, sampleGen);
    
  //write 'Genome' and the number
  drawText( statusx1 + (statusx2-statusx1)/3 - 12, statusy1 - 100, "Genome");
  int sampleGenome = 5;
  drawNumber( statusx1 + (statusx2-statusx1)/2 - 3, statusy1 - 125, sampleGenome);
   
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

// process "special" keyboard events (those having to do with arrow keys)
void special_keyboard(int key,int x, int y)
{
  switch (key) {
    case GLUT_KEY_LEFT:

      break;
    case GLUT_KEY_RIGHT:

      break;
    case GLUT_KEY_UP:
      
      break;
    case GLUT_KEY_DOWN:

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
   statusy2 = yaxispeak - 140;
   setModifiers();
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0., WIDTH-1, 0., HEIGHT-1, -1.0, 1.0);
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
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special_keyboard);
  glutMainLoop();
}

void printVals()
{
  for(int i = 0; i < NUM_VALUES; i++)
    cout << xvalues[i] << ' ';
  cout << endl;
  for(int i = 0; i <  NUM_VALUES; i++)
    cout << yvalues[i] << ' ';
}

void printVals2()
{
  for(int i = 0; i < NUM_VALUES; i++)
    {
      cout << " x value: " << xvalues[i] << " \t y values: ";
      for(int j = 0; j < POP; j++)
	cout << yvalues2[i][j] << " ";
      cout << endl;
    }
}

int main()
{
  setValues();
  printVals();
  setModifiers();
  init_gl_window();
  



}
