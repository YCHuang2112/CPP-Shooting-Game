#include"Battlefield.h"
using namespace std;

Battlefield::Battlefield()
	:Mmax(PARA_MAX_MONSTER_NUM_INIT), Tmax(PARA_MAX_TRAP_NUM_INIT),score(0), mwidth(width), mheight(height), Stage_ID(1), player_dead(false)
	{
		pp = new player;
		
		Mlist.resize(Mmax);
		for(int i = 0; i < Mmax; i++) 
			Mlist[i].born(*this); 
		
		Tlist.resize(Tmax);
		for(int i = 0;i < Tmax;i++) Tlist[i].settrap(width/2, height/2);
	}

bool Battlefield::gotone(player &p, trap &t){
	if(p.getx()==t.getx()&&p.gety()==t.gety()){
		return true;
	}
	else
		return false;
}

bool Battlefield::BshotM(bullet &B)
{
	bool haveshoot =  false;
	int size = Mlist.size();
	for(int i = Mlist.size() - 1; i >= 0; i--){
		if( Mlist[i].mx == B.bx && Mlist[i].my == B.by)
		{
			if(!Mlist.size()) break;
			Mlist[i].killed();
			Mlist.erase( Mlist.begin() + i );
			haveshoot = true;
			score++;
		}
	}

	if(haveshoot) return true;
	return false;
}


void Battlefield::Mmove(player &P)
{
	for(int i = 0; i < Mlist.size(); i++)
	{
		int gseed =rand() % 32;
		if(gseed > 10 && Mlist.size() < Mmax)
		{
			Mlist.push_back(monster());
			bool direct_show = true;
			Mlist[ Mlist.size()-1 ].born(*this);
			Mlist[ Mlist.size()-1 ].set_show(direct_show);
		}	
		if( Mlist[i].move_death_check(P) )
		{
			Mlist[i].killed();
			Mlist.erase( Mlist.begin() + i );
			score++;
		}
	}
}	

void Battlefield::monster_show()
{
	for(int i = 0; i < Mlist.size(); i++)
		Mlist[i].show = true;
}

void Battlefield::player_show()
{
	pp->show();
}

void Battlefield::leave_player(int &mx, int &my)
{
	player &p = *pp;
	if (mx - 10 < p.getx() && mx >= p.getx() )
		mx += 15;
	else if (mx + 10 > p.getx() && mx < p.getx() )
		mx -= 15;
	if (my - 10 < p.gety() && my >= p.gety() )
		my += 15;
	else if (my + 10 > p.gety() && my < p.gety())
		my -= 15;
}

//int Battlefield::eventUserInput(player &p, bool &PBmove, Battlefield &BF, int cond)
int Battlefield::EventUserInput(player &p, bool &PBmove, Battlefield &BF)
{
	char ch = getch();

	//if(ch == 27) //ESC
	if(ch == 0X7f)  //Backspace
		return 1;

	p.act(ch, PBmove, BF);

	fflush(stdout);

	return 0;
}



void Battlefield::BattleStart()
{
	set_conio_terminal_mode();
	int i = 0; 
	long long start = clock(), MBTcounter = 0;
	bool PBmove = false;
	clearScreen();
	hideCursor();
	fflush(stdout);

	gotoxy(mwidth/2 - 10 < 0 ? 0 : mwidth/2 - 10, mheight/2-3);
	cout << "      Stage " << Stage_ID << endl;
	gotoxy(mwidth/2 - 10 < 0 ? 0 : mwidth/2 - 10, mheight/2);
	cout << " Press any key to start" << endl;
	while(1) 
		if(kbhit()){ 
			clearScreen();
			break;
		}
	player &p = *pp;
	p.Print_HP();
printf("\033[1;36m");
	for(int i = 1 ; i < mwidth + 1; i++)	
	{
		gotoxy(1+i,2);
		cout << '-';
		gotoxy(1+i,mheight+1);		cout << '-';
	}
printf("\033[1;35m");
	for(int i = 2; i < mheight; i++)
	{
		gotoxy(2, 1+i);
		cout << '|';
		gotoxy(width+1, i+1);
		cout << '|';
	}


	start = clock();
	long long subsor = clock();
	
	long long ttime[Tmax] = {0};
//	ttime[0] = 0;ttime[1] = 0;ttime[2] = 0;
	bool Trap_flag[Tmax] = {false};
//	Trap_flag[0] = false; Trap_flag[1] = false; Trap_flag[2] = false;
	
	monster_show();
	player_show();
	while(p.Is_Dead()==false&&score<score_target)
	{
		
		//User_action_handler
		if( kbhit() ){
//			if((flag[0]||flag[1]||flag[2])){
//				getchar();
//			}
			bool player_is_trapped = false;
			for(int i = 0;i < Tmax;i++){
				player_is_trapped =  (player_is_trapped || Trap_flag[i]);
			}
			//if( eventUserInput(p, PBmove, *this, (!flag[0]&&!flag[1]&&!flag[2])) ){
			if(player_is_trapped){ getchar();}
			else if( EventUserInput(p, PBmove, *this) ){ 
				clearScreen();
				break;
			}
		}
		
		//Trap_action_handler
		for(int i = 0;i < Tmax;i++){
			if(gotone(p, Tlist[i])){
				if(!Trap_flag[i]){
					ttime[i] = clock();
					Trap_flag[i] = true;
					Tlist[i].show();
				}
				if((int)((clock()-ttime[i])/CLOCKS_PER_SEC) >= PARA_TRAPPED_TIME){
					fflush(stdin);
					gotoxy(Tlist[i].getx()+1, Tlist[i].gety());
					cout << " ";
					gotoxy(Tlist[i].getx()-1, Tlist[i].gety());
					cout << " ";
					gotoxy(Tlist[i].getx(), Tlist[i].gety()+1);
					cout << " ";
					gotoxy(Tlist[i].getx(), Tlist[i].gety()-1);
					cout << " ";
					Tlist[i].settrap(p.getx(), p.gety());
					ttime[i] = 0;
					Trap_flag[i] = false;
					p.show();
				}
			}
		}

		//Human_safety_checker_handler
		for(int i=0;i<Mlist.size();i++){
			if(Mlist[i].getx()==p.getx()&&Mlist[i].gety()==p.gety()){
				gotoxy(Mlist[i].getx(),Mlist[i].gety());
				cout<<"C";
				p.HP_Dec();
				p.mhurt(Mlist[i].getdir());
			}
		}
		
		
		if( clock() - start > 1000)
		{
			MBTcounter++;
			if(MBTcounter >  (1 << 8) ) 
			{
				//Monster_action_handler
				if(Mlist.size())
				{
					Mmove(p);
					for(int i = 0; i < Mlist.size(); i++)
						Mlist[i].changedir(p);
				}

				MBTcounter = 0;

				gotoxy(40, 0);
				printf("\033[0;33m""score: %d", score);
				printf("\033m");
				
				//Bullet_action_handler
				p.bullet_renew(*this);
			}

			gotoxy(0, 0);
			printf("\033[1;33m" "%lld   seconds""\033[m", (clock() - subsor)/ CLOCKS_PER_SEC);			
		
			fflush(stdout);
			start += 1000;
		}
	}

	if(p.Is_Dead()==true){
		player_dead = true;
		
		clearScreen();
		printf("\033[1;31m");
		gotoxy(width/2 - 4 < 0 ? 0 : width/2 - 4, height/2);
		cout << " GAMEOVER" << endl;
		printf("\033[m");
		//reset_terminal_mode();
	}
	if(score>=score_target){
		clearScreen();
		printf("\033[1;33m");
		gotoxy(width/2 - 3 < 0 ? 0 : width/2 - 3, height/2);
		cout << "YOU WIN!!" << endl;
		printf("\033[m");
        //reset_terminal_mode();
	}

}



void Battlefield::BattleReset(int HP_inc, int Bullet_inc, int Monster_inc, int Trap_inc, int Score_Target_inc){
	if(player_dead){
		pp->reset();
		Mmax = PARA_MAX_MONSTER_NUM_INIT;
		Tmax = PARA_MAX_TRAP_NUM_INIT;
		score = 0;
		score_target = PARA_TARGET_SCORE_INIT_VAL;
		Stage_ID = 1;
		player_dead = false;
	}
	else{
		pp->reset(HP_inc, Bullet_inc);
		Mmax += Monster_inc;
		Tmax += Trap_inc;
		score_target += Score_Target_inc;
		Stage_ID++;
	}
	
	Mlist.clear();
	Mlist.resize(Mmax);
	for(int i = 0; i < Mmax; i++) 
		Mlist[i].born(*this); 
	
	
	Tlist.clear();
	Tlist.resize(Tmax);
	for(int i = 0;i < Tmax;i++){ Tlist[i].settrap(width/2, height/2);}
}