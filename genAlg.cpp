// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <stdexcept>
#include <bitset>
using namespace std;

class chromo {
public:
	bitset<36> data;
	int fitness;
	chromo(bitset<36> in) {
		data = in;
	}

};

chromo** generation;

char* decoded;
bitset<4> gene;
int counter;
double target = 10;
double num;
double val;
double num2;
int genSize = 10000;
bool op = true;
bool number = false;
bool first = true;
bool isType = true;
bool yesNum = false;
bool prevNum = false;
char* function;
char type;
int num3;
double fitness;

void start() {
	generation = new chromo*[genSize];
	int a;
	//char *input;
	bitset<36> input;
	//input = new char[39];
	for (int i = 0; i < genSize; i++) {

		for (int x = 0; x < 36; x++) {
			a = rand() % 2;
			if (a == 1) {
				input.set(x, 1);
			}
			else {
				input.set(x, 0);
			}
		}
		//cout << input << endl;
		generation[i] = new chromo(input);
		//cout << generation[i]->data << endl;
	}
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

//DECODE(chromo)  This function will take a chromo argument and return a string containing the decoded characters
double decode(chromo c) {
	
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
			else {
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
		else if (type == 'o'&&i!=8) {
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
	function = new char[counter+1];
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
		else if (type == 'o'&&i!=8) {
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



	/*

	cout << endl;

	cout << "\\/" << endl;
	cout << decoded << endl;
	cout << function << endl;
	cout << val << endl;
	cout << "/\\" << endl;



	*/



	fitness = (1 / (target - val));


	delete[] decoded;
	delete[] function;

	return fitness;
}





int main()
{
	start();
	//bitset<4> test;
	//test.set(1, 1);
	//bitset<4> t2(string("0010"));
	//if (test == (bitset<4>)(string("0010"))) {//I can compare bitsets like this
											  //if (test == t2) {
	//	cout << "Success" << endl;
	//}
	//cout << test << endl;
	int maxFitness = 0;
	int fit = 0;
	chromo *fittest;
	for (int i = 0; i < genSize; i++) {
		fit = decode(*generation[i]);
		if (maxFitness < fit) {
			maxFitness = fit;
			fittest = generation[i];
		}
		//cout << "pass" << endl;
	}
	cout << "Max fitness: " << fitness << endl;
	//int l = 0 % 4;
	//cout << l << endl;
	//cout << "pass" << endl;
	int end;
	cin >> end;
	return 0;
}

