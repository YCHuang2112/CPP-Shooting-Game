#include"Trap.h"

trap::trap(){
	tx = rand() % width;
	ty = rand() % height;
}
void trap::show(){
	gotoxy(tx+1, ty);
		cout << "X";
	gotoxy(tx-1, ty);
		cout << "X";
	gotoxy(tx, ty+1);
		cout << "X";
	gotoxy(tx, ty-1);
		cout << "X";
}
void trap::settrap(int px, int py){
	tx = rand() % width;
	ty = rand() % height;
	if (tx - 8 < px && tx > px)
	{
		tx += 8;
		if (tx > width)
			tx -= width;
	}
	else if (tx + 8 >= px && tx <= px)
	{
		tx -= 8;
		if (tx < 0)
			tx += width;
	}
	if (ty - 8 < py && ty > py)
	{
		ty += 8;
		if (ty > height)
			ty -= height;
	}
	else if (ty + 8 >= py && ty <= py)
	{
		tx -= 8;
		if (ty < 0)
			ty += height;
	}
}

