#ifndef C2048_H
#define C2048_H

#include <time.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

typedef unsigned int uint;
using namespace std;

enum movDir { UP, DOWN, LEFT, RIGHT };
class tile
{
public:
    tile() : val( 0 ), blocked( false ) {}
    uint val;
    bool blocked;
};

class g2048{

public:
  g2048() : done( false ), win( false ), moved( true ), score( 0 ) {}
  void loop();
private:
  void drawBoard();
  void waitKey();
  void addTile();
  bool canMove();
  bool testAdd(int,int,uint);
  void moveVert(int,int,int);
  void moveHori(int,int,int);
  void move(movDir);
  tile board[4][4];
  bool win, done, moved;
  uint score;
};

#endif
