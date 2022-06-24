#ifndef TRAP_H
#define TRAP_H
#include<cstdlib>
#include<iostream>
#include"struct.cpp"
//#include"Battlefield.h"
#include<iostream>
using namespace std;

class trap{
	private:
		int tx, ty;
		friend class player;
	public:
		void show();
		trap();
		void settrap(int, int);
		inline int getx(){return tx;}
		inline int gety(){return ty;}

};

#endif
