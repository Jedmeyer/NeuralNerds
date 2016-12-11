#include <iostream>
#include <time.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "C2048.h"

using namespace std;

int main(){
	cout<<"HELP ME"<<endl;

	srand( static_cast<uint>( time( NULL ) ) );
	g2048 g;
	g.loop();
	
	return 0;
}
