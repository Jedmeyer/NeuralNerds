
#include <time.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "C2048.h"

typedef unsigned int uint;
using namespace std;
//enum movDir { UP, DOWN, LEFT, RIGHT };

g2048::g2048(){
  srand(time(NULL));
  done = false;
  win = false;
  moved = false;
  score = 0;
}

void g2048::loop(){
  addTile();
  while( true )
  {
    if( moved ) addTile();
    drawBoard();
    if( done ) break;
    waitKey();
  }
  string s = "Game Over!";
  if( win ) s = "You've made it!";
  cout << s << endl << endl;
}

vector<double> g2048::toVector(){

  vector<double> vecBoard;

  for(int i = 0; i < 4; ++i){

    for(int j = 0; j < 4; ++j){

      vecBoard.push_back(board[i][j].val);

    }
  }

  return vecBoard;
}

vector<double> g2048::toInput(){

  //Return Weights of board
  vector<double> weights;

  //Storage for the current board
  vector<double> curBoard = toVector();

  double largestTile = 0;

  //Find largest value
  for(int i = 0; i < curBoard.size(); ++i){
    if(curBoard[i]>largestTile){
      largestTile=curBoard[i];

    }
  }

  //Log base 2 all
  for(int i = 0; i < curBoard.size(); ++i){
    if(curBoard[i]==0){
      weights.push_back(0);
    }
    else{
      weights.push_back(log2(curBoard[i]));
    }
  }
  //Save Logbase 2 of largest
  double topLog = log2(largestTile);
  // divide by log base 2 of largest
  for(int i = 0; i < curBoard.size(); ++i){
    weights[i] = weights[i] / topLog;
  }
  return weights;
}

void g2048::drawBoard(){
  //system( "cls" );
  cout << "SCORE: " << score << endl << endl;
  for( int y = 0; y < 4; y++ )
  {
    cout << "+------+------+------+------+" << endl << "| ";
    for( int x = 0; x < 4; x++ )
    {
  if( !board[x][y].val ) cout << setw( 4 ) << " ";
  else cout << setw( 4 ) << board[x][y].val;
  cout << " | ";
    }
    cout << endl;
  }
  cout << "+------+------+------+------+" << endl << endl;
}

void g2048::netMove(vector<double> output){
  ///////////// Set up With only 2 Output Neurons ///////////////
  //     11 = UP // 00 = DOWN // 10 = LEFT // 01 = RIGHT       //
  ///////////////////////////////////////////////////////////////
  moved = false;

  if(output[0] == 1){
    if(output[1] == 1) move( UP );
    else move( LEFT );
  }
  else{
    if(output[1] == 1) move( RIGHT );
    else move( DOWN );
  }

  for( int y = 0; y < 4; y++ )
    for( int x = 0; x < 4; x++ )
      board[x][y].blocked = false;

  ///////////// Set up With 4 Output Neurons ///////////////
  //  UP, DOWN, LEFT, RIGHT
  //////////////////////////////////////////////////////////
  /*
  moved = false;

  if(output[0] == 1) move( UP );
  else if(output[1] == 1) move( DOWN );
  else if(output[2] == 1) move( LEFT );
  else if(output[3] == 1) move( RIGHT);
  else cout<<"ERROR READING MOVE"<<endl;

  for( int y = 0; y < 4; y++ )
    for( int x = 0; x < 4; x++ )
      board[x][y].blocked = false;

  */

}

void g2048::randMove(){
  moved = false;

  int r = rand()%4;

  switch(r)
  {
    case 0:move( UP    );break;
    case 1:move( LEFT  );break;
    case 2:move( DOWN  );break;
    case 3:move( RIGHT );
  }

  for( int y = 0; y < 4; y++ )
    for( int x = 0; x < 4; x++ )
      board[x][y].blocked = false;

  for(int i = 0; i < 50000000; ++i);

}

void g2048::waitKey(){
  moved = false; char c;
  cout << "(W)Up (S)Down (A)Left (D)Right "; cin >> c; c &= 0x5F;

  switch( c )
  {
    case 'W': move( UP );break;
    case 'A': move( LEFT ); break;
    case 'S': move( DOWN ); break;
    case 'D': move( RIGHT );
  }

  for( int y = 0; y < 4; y++ )
    for( int x = 0; x < 4; x++ )
  board[x][y].blocked = false;
}

void g2048::addTile(){
  for( int y = 0; y < 4; y++ )
    for( int x = 0; x < 4; x++ )
  if( !board[x][y].val )
  {
      uint a, b;
      do
      { a = rand() % 4; b = rand() % 4; }
      while( board[a][b].val );

      int s = rand() % 100;
      if( s > 89 ) board[a][b].val = 4;
      else board[a][b].val = 2;
      if( canMove() ) return;
  }
  done = true;
}

bool g2048::canMove(){
  for( int y = 0; y < 4; y++ )
    for( int x = 0; x < 4; x++ )
  if( !board[x][y].val ) return true;

  for( int y = 0; y < 4; y++ )
    for( int x = 0; x < 4; x++ )
    {
  if( testAdd( x + 1, y, board[x][y].val ) ) return true;
  if( testAdd( x - 1, y, board[x][y].val ) ) return true;
  if( testAdd( x, y + 1, board[x][y].val ) ) return true;
  if( testAdd( x, y - 1, board[x][y].val ) ) return true;
    }
  return false;
}

bool g2048::testAdd( int x, int y, uint v ){
  if( x < 0 || x > 3 || y < 0 || y > 3 ) return false;
  return board[x][y].val == v;
}

void g2048::moveVert( int x, int y, int d ){
  if( board[x][y + d].val && board[x][y + d].val == board[x][y].val && !board[x][y].blocked && !board[x][y + d].blocked  )
  {
    board[x][y].val = 0;
    board[x][y + d].val *= 2;
    score += board[x][y + d].val;
    board[x][y + d].blocked = true;
    moved = true;
  }
  else if( !board[x][y + d].val && board[x][y].val )
  {
    board[x][y + d].val = board[x][y].val;
    board[x][y].val = 0;
    moved = true;
  }
  if( d > 0 ) { if( y + d < 3 ) moveVert( x, y + d,  1 ); }
  else        { if( y + d > 0 ) moveVert( x, y + d, -1 ); }
}

void g2048::moveHori( int x, int y, int d ){
  if( board[x + d][y].val && board[x + d][y].val == board[x][y].val && !board[x][y].blocked && !board[x + d][y].blocked  )
  {
    board[x][y].val = 0;
    board[x + d][y].val *= 2;
    score += board[x + d][y].val;
    board[x + d][y].blocked = true;
    moved = true;
  }
  else if( !board[x + d][y].val && board[x][y].val )
  {
    board[x + d][y].val = board[x][y].val;
    board[x][y].val = 0;
    moved = true;
  }
  if( d > 0 ) { if( x + d < 3 ) moveHori( x + d, y,  1 ); }
  else        { if( x + d > 0 ) moveHori( x + d, y, -1 ); }
}

void g2048::move( movDir d ){
  switch( d )
  {
      case UP:
        for( int x = 0; x < 4; x++ )
    {
        int y = 1;
        while( y < 4 )
        { if( board[x][y].val ) moveVert( x, y, -1 ); y++;}
    }
    break;
      case DOWN:
    for( int x = 0; x < 4; x++ )
    {
        int y = 2;
        while( y >= 0 )
        { if( board[x][y].val ) moveVert( x, y, 1 ); y--;}
    }
    break;
      case LEFT:
    for( int y = 0; y < 4; y++ )
    {
        int x = 1;
        while( x < 4 )
        { if( board[x][y].val ) moveHori( x, y, -1 ); x++;}
    }
    break;
      case RIGHT:
    for( int y = 0; y < 4; y++ )
    {
        int x = 2;
        while( x >= 0 )
        { if( board[x][y].val ) moveHori( x, y, 1 ); x--;}
    }
  }
}
