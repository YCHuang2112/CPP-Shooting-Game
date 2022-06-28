#include"Trap.h"

trap::trap(){
	tx = rand() % width;
	ty = rand() % height;
	Activated = false;
	Activated_Time = 0;
}
void trap::show(){
	if(tx+1 < width+1){
		gotoxy(tx+1, ty);
		cout << "X";
	}
	if(tx-1 > 2){
		gotoxy(tx-1, ty);
		cout << "X";
	}
	if(ty+1 < height+1){
		gotoxy(tx, ty+1);
		cout << "X";
	}
	if(ty-1 > 2){
		gotoxy(tx, ty-1);
		cout << "X";
	}
}
void trap::disappear(){
	if(tx+1 < width+1){
		gotoxy(tx+1, ty);
		cout << " ";
	}
	if(tx-1 > 2){
		gotoxy(tx-1, ty);
		cout << " ";
	}
	if(ty+1 < height+1){
		gotoxy(tx, ty+1);
		cout << " ";
	}
	if(ty-1 > 2){
		gotoxy(tx, ty-1);
		cout << " ";
	}
}

void trap::settrap(int px, int py){
	tx = rand() % width;
	ty = rand() % height;
	if (tx - 8 < px && tx > px)
	{
		tx += 8;
		if (tx > width)
			tx -= (width-2);
	}
	else if (tx + 8 >= px && tx <= px)
	{
		tx -= 8;
		if (tx < 3)
			tx += (width-2);
	}
	if (ty - 8 < py && ty > py)
	{
		ty += 8;
		if (ty > height)
			ty -= (height-2);
	}
	else if (ty + 8 >= py && ty <= py)
	{
		tx -= 8;
		if (ty < 3)
			ty += (height-2);
	}	
}

