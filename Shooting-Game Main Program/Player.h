#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#ifndef PLAYER
#define PLAYER
class Battlefield;
class bullet ;
class monster;
#include"struct.cpp"
#include"health.h"
#include"Battlefield.h"
class player: public health
{
private:
	int px, py;
	int maxbullet;
	vector<bullet> Blist;
	
	Battlefield *BF_ptr;
	edir face;
	void clear()
	{
		gotoxy(px, py);
		printf(" ");
	}
	void emerge()
	{
		printf("\033[38;5;199m");
		gotoxy(px, py);
		putchar('I');
		printf("\033[0;37m");
	}

public:
	
	player();

inline int getx() {return px;}
inline int gety() { return py; }
inline int getface() { return face; }
	
	void action(char act);
	void mhurt(edir d){
		switch(d){
			case Up:
				py-=3;
				break;
			case Down:
				py+=3;
				break;
			case Right:
				px+=3;
				break;
			case Left:
				px-=3;
				break;
		}
		BF_Bound_Checker(px,py);
		gotoxy(px,py);
		cout<<'G';
	}
	void act(char ch, bool Bmove, Battlefield &BF);
	void bullet_renew(Battlefield &BF);
	bool Bhurt(int mx, int my);
	void show(){emerge();}
	void reset();
	void reset(int HP_inc, int Bullet_inc);

	friend class bullet;
};
#endif

