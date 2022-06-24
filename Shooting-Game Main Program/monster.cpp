#include"Monster.h"
#include"iostream"
using namespace std;

		void monster::born( Battlefield &BF) {
			mx = rand() % width;
			my = rand() % height;
			int &x = mx, &y = my;              // ?????????????????????????

			BF.leave_player(mx, my);            // ???????????????????????????
			BF_Bound_Checker(mx, my);
			dir = Stop;
			show = false;
		}
		void monster::changedir(player &p) {
			int dx = p.getx() - mx;
			int dy = p.gety() - my;
			int r = rand() % 2;
			if(!dx) r = 1;
			if(!dy) r = 0;
			switch(r)
			{
				case 0:
					if(dx < 0) dir = Left;
					else if(dx>0)		dir = Right;
					return;
				case 1: 
					if(dy < 0) dir = Up;
					else if(dy>0) 		dir = Down;
					return;
			}
		}


		bool monster::move_death_check(player &P) {
			if(!show) return false;

			clearm();
//gotoxy(20, 1); cout << "fowehf" << endl;
			int r=rand()%3;
			if(r!=0){
			switch (dir) {
				case Down  :	    my+=1; break;
				case Up	   :	    my-=1; break;
				case Right :	    mx+=1; break;
				case Left  :	    mx-=1; break;
				default    : changedir(P); break;
			}
			}

			if( P.Bhurt(mx, my) )
			 {
//				 cout << "I'm reallllllllllllllly hurt"<< endl;
			 	 return true;
			}			
			BF_Bound_Checker(mx, my);
			//		dir = stop;
			emerge();
			return false;
		}


		void monster::killed() {
			clearm();
//			show = false;
//.			mx = my = 60;
		//		dir = Stop;
		}
		 
