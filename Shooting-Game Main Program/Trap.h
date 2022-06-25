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
		bool Activated = false;
		long long Activated_Time = 0;
		
		friend class player;
	public:
		void show();
		trap();
		void settrap(int, int);
		void set_Activated(bool status){Activated = status;}
		void set_Activated_Time(long long time){Activated_Time = time;}
		
		inline int getx(){return tx;}
		inline int gety(){return ty;}
		inline bool is_Activated() { return Activated;}
		inline long long get_Activated_Time() { return Activated_Time;}
		
};

#endif
