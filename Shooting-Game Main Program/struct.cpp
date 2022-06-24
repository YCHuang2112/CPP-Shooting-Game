#ifndef STRUCTURE
#define STRUCTURE

#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>
#include<termios.h>
#include<time.h>
#include<cstdio>
using namespace std;

#define height  20
#define width   40
#define minh     3
#define minw     3

 enum edir{Stop,Up,Left,Right,Down,Attack};


void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0X1B, y, x);
	fflush(stdout);
}

void BF_Bound_Checker(int &horizon, int &verticle)
{
//cout << "verticle = " << verticle << " horizon = " << horizon << endl;	
		if (horizon < 3)					horizon  =  width;
		else if (horizon > width)			horizon -=  width-2;
		else if (verticle < 3)				verticle  =  height;
		else if (verticle > height)	    verticle -=  height-2 ;
}




#endif
