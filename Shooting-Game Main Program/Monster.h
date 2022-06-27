#include<vector>
#include<cstdio>
#include<cstdlib>
#include"struct.cpp"
#include<iostream>
using namespace std;

#ifndef MONSTER_H
#define MONSTER_H
class Battlefield;
class monster;
class player;
#include"struct.cpp"
#include"Battlefield.h"
class monster {

	private:
		int mx,my;
		int x_ambiguous, y_ambiguous;
		bool show;
		void clearm()
		{
			gotoxy(mx, my);
			printf(" ");
		}
		void emerge()
		{
			//printf("\033[38;5;204m");
			gotoxy(mx, my);
			putchar('C');
			printf("\033[0;37m");
		}
		
		Battlefield *BF_ptr;
		edir dir;
		friend class player;
		friend class Battlefield;
	protected:

	public:
		monster()
		{
			dir = Stop;
			show = false;
		}

/*		monster(const Battlefield & BF) {
			born(B);
		}
*/
		void born( Battlefield &BF);
		void killed();
		
		void changedir(player &p);
		void set_show(bool direct_show){show=direct_show;}
		inline int getx() { return mx; }
		inline int gety() { return my; }
		inline edir getdir() { return dir; }
		inline bool getshow() { return show; }
		bool move_death_check(player &P);
		friend class Battlefield;

};
#endif

