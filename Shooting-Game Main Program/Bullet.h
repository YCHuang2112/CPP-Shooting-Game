#ifndef BULLET
#define BULLET
class Battlefield;
#include"Battlefield.h"
#include"struct.cpp"
class bullet {

private:
	int bx, by;
	bool show;
	friend class player;
	void clear()
	{
		gotoxy(bx, by);
		printf(" ");
	}
	void emerge()
	{
		printf("\033[38;5;201m");
		gotoxy(bx, by);
		putchar('o');
		printf("\033[0;37m");
	}
	
	Battlefield *BF_ptr;
	edir dir;

public:
	bullet();
	bullet( edir d, int x, int y);

	inline int getx() { return bx; }
	inline int gety() { return by; }
	inline edir getdir() { return dir; }
	inline bool getshow() { return show; }
	
	bool move_shot(Battlefield &BF);
	void Bshow(){ emerge();}
	
	friend class monster;		
	friend class Battlefield;
};
#endif

