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




class genome {
public:
  int id;
  int totalspec=1;
  genome(int i){
    id = i;
    }
};

class chromo {
public:
  bitset<36> data; // We will be switching to strings.  They will take up more memory, but will simplify the design of the genetic algorithms.
  double fitness;
  genome *fam;
  int gid;
  int specid;

  chromo(bitset<36> in) {
    data = in;
  }
  chromo(bitset<36> in, genome *parent){
    data = in;
    fam = parent;
  }


};

double decode(chromo c, bool console);


//Global variables declared here
char* decoded;
bitset<4> gene;
int counter;
double target = 25;
double num;
double val;
double num2;
const int genSize = 10;
bool op = true;
bool number = false;
bool first = true;
bool isType = true;
bool yesNum = false;
bool prevNum = false;
char* function;
char type;
double fitness;
int genNum=0;
int genomeNum=0;
const int totalGens=10;
float mutationChance = 5;
chromo*** genArr = new chromo**[totalGens];
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

// void inherit (chromo *parent,bool mute){
//   gid = parent.id;
//   if (mute){
//     specid = parent->fam.totalspec;
//     parent->fam.totalspec++;
//   }
// }
// chromo* cross(chromo** gen){
//   int r = (int)(rand()%genSize);
//   chromo* a;
//   chromo* b;
//   a = gen[r];
//   r = (int)(rand()%genSize);
//   b = gen[r];
//   nbit = bitset<36>;
//   r = (int)(rand ()%36);
//   * r will be used here to to take verything in 'a' up
//   to r. The difference between chromo lengh and r will then
//   be used to get the rest of the chromosome from 'b' 
//   Next gen's content should be sufficient to craft this. 
//   return a;
// }

void generate() {
  genArr[genNum] = new chromo*[genSize];
  int a;
  //char *input;
  bitset<36> input;
  //input = new char[39];
  if (genNum<1){
    for (int i = 0; i < genSize; i++) {


      for (int x = 0; x < 36; x++) {

      a = rand() % 2;
        if (a == 1) {
        input.set(x, 1);
        }
        else{
        input.set(x, 0);
        }
      }
    
    genArr[genNum][i] = new chromo(input);
    genArr[genNum][i]->fam = new genome(genomeNum);
    genomeNum++;
    
  }
}
 

  
  genNum++;
}

double selection(double tf, double fts[]){
  if (tf == 0){cout << "Warning: TotalFitness = 0";}
  tf = tf*10000;
  int tff = (int)tf;
  int len;
  for (len=0; fts[len] != '\0'; len++);
  double *ft;
  ft = new double[len];
  for (int i = 0; i<len; i++){
    ft[i] = 10000*fts[i];
  }
  double r = (rand() % tff); // This line is causing a floating point exception core dump
  int selection;
  for (selection = 0; r > 0; selection++){
    r = r - ft[selection];
  }
  return selection;
}

void nextGen(){
  genArr[genNum] = new chromo*[genSize];
  bool mutate = false;
  double fits[genSize];
  double totalfit=0;
  double odds[genSize];
  bool crossover = false;
  int a;
  bitset<36> input;
  for (int i = 0; i<genSize; i++){
    fits[i] = decode(*genArr[genNum-1][i],false);
    totalfit += fits[i];

  }
  for (int i =0; i<genSize; i++){
    odds[i] = fits[i]/totalfit; //This results in a weighted mutation probability for each chromosome relative to its fitness value.
  }
  int index  = '\0';
  for(int i =0; i < genSize; i++){
    // crossover = (rand () % 100) < crossChance;
    //if (crossover){
    //  cross(genArr[genNum]);
    //}

    index = selection(totalfit, fits);
    cout << "Chosen chromosome #: "<< index <<endl;;
    for(int x =0; x<36; x++){
      mutate = (rand () % 100) < mutationChance;
      if (genArr[genNum-1][index-1]->data[x] == 1){
        input.set(x,1);
      }
      else if(mutate){
        a = rand() % 2;
        cout << "MUTATION!\n";
        if (a == 1) {
          input.set(x, 1);
        }
        else{
          input.set(x, 0);
        }
      }
      else{
        input.set(x,0);
      }
    }
    genArr[genNum][i] = new chromo(input);
  }   
  genNum++;
}




double getNum(char n) {
  switch (n) {
  case'0': num3 = 0; break;
  case'1': num3 = 1; break;
  case'2': num3 = 2; break;
  case'3': num3 = 3; break;
  case'4': num3 = 4; break;
  case'5': num3 = 5; break;
  case'6': num3 = 6; break;
  case'7': num3 = 7; break;
  case'8': num3 = 8; break;
  case'9': num3 = 9; break;
  default: break;
  }
  return num3;

}

//DECODE(chromo)  This function will take a chromo argument and return the fitness value for that chromo
double decode(chromo c, bool console) {

  decoded = new char[10];
  counter = 0;
  fitness = 0;
  for (int i = 0; i < 32; i++) {

    for (int x = 0; x<4; x++) {
      gene.set(x, c.data[x + i]);// = c.data[i];
    }
    if ((i) % 4 == 0 || i == 31) {
      if (gene == (bitset<4>)(string("0000"))) {
        decoded[counter] = '0';
        counter++;
      }
      else if (gene == (bitset<4>)(string("0001"))) {
        decoded[counter] = '1';
        counter++;
      }
      else if (gene == (bitset<4>)(string("0010"))) {
        decoded[counter] = '2';
        counter++;
      }
      else if (gene == (bitset<4>)(string("0011"))) {
        decoded[counter] = '3';
        counter++;
      }
      else if (gene == (bitset<4>)(string("0100"))) {
        decoded[counter] = '4';
        counter++;
      }
      else if (gene == (bitset<4>)(string("0101"))) {
        decoded[counter] = '5';
        counter++;
      }
      else if (gene == (bitset<4>)(string("0110"))) {
        decoded[counter] = '6';
        counter++;
      }
      else if (gene == (bitset<4>)(string("0111"))) {
        decoded[counter] = '7';
        counter++;
      }
      else if (gene == (bitset<4>)(string("1000"))) {
        decoded[counter] = '8';
        counter++;
      }
      else if (gene == (bitset<4>)(string("1001"))) {
        decoded[counter] = '9';
        counter++;
      }
      else if (gene == (bitset<4>)(string("1010"))) {
        decoded[counter] = '+';
        counter++;
      }
      else if (gene == (bitset<4>)(string("1011"))) {
        decoded[counter] = '-';
        counter++;
      }
      else if (gene == (bitset<4>)(string("1100"))) {
        decoded[counter] = '*';
        counter++;
      }
      else if (gene == (bitset<4>)(string("1101"))) {
        decoded[counter] = '/';
        counter++;
      }
      else { //This is serving as our null character in the string if the data is unintelligble.
        decoded[counter] = 'a';
        counter++;
      }
    }





  }


  decoded[9] = '\0';
  val = 0;
  num = 0;
  number = false;
  op = true;
  first = true;
  counter = 0;
  type = 'n';

  for (int i = 0; i < 9; i++) {
    if (type == 'n') {
      switch (decoded[i]) {
      case'0': type = 'o'; counter++; break;
      case'1': type = 'o'; counter++; break;
      case'2': type = 'o'; counter++; break;
      case'3': type = 'o'; counter++; break;
      case'4': type = 'o'; counter++; break;
      case'5': type = 'o'; counter++; break;
      case'6': type = 'o'; counter++; break;
      case'7': type = 'o'; counter++; break;
      case'8': type = 'o'; counter++; break;
      case'9': type = 'o'; counter++; break;
      default: type = 'n'; break;
      }
    }
    else if (type == 'o'&&i != 8) {
      switch (decoded[i]) {
      case'+': type = 'n'; counter++; break;
      case'-': type = 'n'; counter++; break;
      case'*': type = 'n'; counter++; break;
      case'/': type = 'n'; counter++; break;
      default: type = 'o'; break;
      }
    }



  }
  isType = true;
  yesNum = false;
  prevNum = false;
  function = new char[counter + 1];
  function[counter] = '\0';
  counter = 0;
  type = 'n';

  for (int i = 0; i < 9; i++) {
    if (type == 'n') {
      switch (decoded[i]) {
      case'0': type = 'o'; function[counter] = decoded[i]; counter++; break;
      case'1': type = 'o'; function[counter] = decoded[i]; counter++; break;
      case'2': type = 'o'; function[counter] = decoded[i]; counter++; break;
      case'3': type = 'o'; function[counter] = decoded[i]; counter++; break;
      case'4': type = 'o'; function[counter] = decoded[i]; counter++; break;
      case'5': type = 'o'; function[counter] = decoded[i]; counter++; break;
      case'6': type = 'o'; function[counter] = decoded[i]; counter++; break;
      case'7': type = 'o'; function[counter] = decoded[i]; counter++; break;
      case'8': type = 'o'; function[counter] = decoded[i]; counter++; break;
      case'9': type = 'o'; function[counter] = decoded[i]; counter++; break;
      default: type = 'n'; break;
      }
    }
    else if (type == 'o'&&i != 8) {
      switch (decoded[i]) {
      case'+': type = 'n'; function[counter] = decoded[i]; counter++; break;
      case'-': type = 'n'; function[counter] = decoded[i]; counter++; break;
      case'*': type = 'n'; function[counter] = decoded[i]; counter++; break;
      case'/': type = 'n'; function[counter] = decoded[i]; counter++; break;
      default: type = 'o'; break;
      }
    }




  }








  for (int i = 0; i < counter; i++) {
    switch (function[i]) {
    case'+': num2 = getNum(function[i + 1]); val += num2; break;
    case'-': num2 = getNum(function[i + 1]); val -= num2; break;
    case'*': num2 = getNum(function[i + 1]); val *= num2; break;
    case'/': num2 = getNum(function[i + 1]); if (num2 != 0) { val /= num2; }
         else {} break;
    default:  break;
    }
    if (first) {
      val = getNum(function[i]);
      first = false;
    }

  }



  if (target == val){
    fitness = 1;
  }
  else {
    fitness = (1 / (target - val));
  }

  if (console){
  cout << endl;
  cout << "---------------------------------------------------------" << endl;
  //if (val == target) {
  //  fitness = 1;
  //  cout << "solution found: " << endl;
    
  //}
  //else {
    
    
//  }
  cout << "Chromosome data: " << c.data << endl;
  cout << "characters: " << decoded << endl;
  cout << "function: "<< function << endl;
  cout << "solution: " << val << endl;
  cout << "Fitness: " << fitness << endl;
  cout << "---------------------------------------------------------" << endl;
}


  



  


  delete[] decoded;
  delete[] function;

  return fitness;
}

void decrypt(int currentGen){
  int maxFitness = 0;
  int fit = 0;
  int fitnum;
  chromo *fittest;
  for (int i = 0; i < genSize; i++) {
    fit = decode(*genArr[currentGen][i],true);    //Note deserved here. Because Decode prints the data, we're getting a ton of values, Want to make this more efficient.
    if (maxFitness < fit) {
      maxFitness = fit;
      fittest = genArr[currentGen][i];
      fitnum = i;

    }
  }

}




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
	       yvalues2[i][j] = decode(*genArr[i][j],false);
	       //yvalues2[i][j] = (sqrt(100*(i+1))) + j;
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
  plotPoints2();

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
  generate();
  cout << "Generation complete. Decoding..." << endl;
  decrypt(0);
  cout << "generation #: "<<genNum;
  cout << endl;
  nextGen();//2nd Gen should start here
  decrypt(1);
  int w=0;
  while (w<totalGens-1){
    cout << "generation #: " << genNum << endl;
    nextGen();
    decrypt(w);
    w++;
  }
  /*
    setValues();
    printVals();
    cout << endl;
  */  
  setValues2();
  printVals2();
  setModifiers();
  init_gl_window();
  
  cout << endl  << w;



}
