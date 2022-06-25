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

bool Battlefield::Encounter_Trap(player &p, trap &t){
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

void Battlefield::Print_BF(){
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
}

bool Battlefield::User_action_handler(bool PBmove){
	//User_action_handler
	player &p = *pp;
	if( kbhit() ){
		bool player_is_trapped = false;
		for(int i = 0;i < Tmax;i++){
			player_is_trapped =  (player_is_trapped || Tlist[i].is_Activated());
		}
		if(player_is_trapped){ 
			getchar();
			p.show();
		}else if( EventUserInput(p, PBmove, *this) ){ 
			player_halt = true;
			clearScreen();
			return false;
		}
	}
	return true;
}

void Battlefield::Trap_action_handler(){
	//Trap_action_handler
	player &p = *pp;
	for(int i = 0;i < Tmax;i++){
		if(Encounter_Trap(p, Tlist[i])){
			if(!Tlist[i].is_Activated()){
				Tlist[i].set_Activated_Time(clock());
				Tlist[i].set_Activated(true);
				Tlist[i].show();
			}
		}
		if(Tlist[i].is_Activated()){
			bool Time_out = (int)((clock()-Tlist[i].get_Activated_Time())/CLOCKS_PER_SEC) >= PARA_TRAPPED_TIME;
			if(Time_out){
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
				Tlist[i].set_Activated_Time(0);
				Tlist[i].set_Activated(false);
				p.show();
			}
		}
	}
}

void Battlefield::Human_safety_checker_handler(){
	//Human_safety_checker_handler
	player &p = *pp;
	for(int i=0;i<Mlist.size();i++){
		if(Mlist[i].getx()==p.getx()&&Mlist[i].gety()==p.gety()){
			gotoxy(Mlist[i].getx(),Mlist[i].gety());
			cout<<"C";
			p.HP_Dec();
			p.mhurt(Mlist[i].getdir());
		}
	}
}

void Battlefield::Monster_action_handler(){
	//Monster_action_handler
	player &p = *pp;
	if(Mlist.size()){
		Mmove(p);
		for(int i = 0; i < Mlist.size(); i++)
			Mlist[i].changedir(p);
	}
}

void Battlefield::Bullet_action_handler(){
	//Bullet_action_handler
	player &p = *pp;
	p.bullet_renew(*this);
}

void Battlefield::Game_End_handler(){
	//Game_End_handler
	player &p = *pp;
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

void Battlefield::BattleStart()
{
	set_conio_terminal_mode();
	int i = 0; 
	long long start = clock(), MBTcounter = 0;
	bool PBmove = false;
	clearScreen();
	hideCursor();
	fflush(stdout);

	Print_BF();
	
	player &p = *pp;

	start = clock();
	long long subsor = clock();	
	monster_show();
	player_show();
	while(p.Is_Dead()==false&&score<score_target)
	{
		
		if(User_action_handler(PBmove) == false){
			clearScreen();
			break;
		}
		
		
		Trap_action_handler();
		
		Human_safety_checker_handler();
		
		if( clock() - start > 1000)
		{
			MBTcounter++;
			if(MBTcounter >  (1 << 8) ) 
			{
				Monster_action_handler();

				MBTcounter = 0;

				gotoxy(40, 0);
				printf("\033[0;33m""score: %d", score);
				printf("\033m");
				
				//Bullet_action_handler
				Bullet_action_handler();
			}

			gotoxy(0, 0);
			printf("\033[1;33m" "%lld   seconds""\033[m", (clock() - subsor)/ CLOCKS_PER_SEC);			
		
			fflush(stdout);
			start += 1000;
		}
	}
	
	Game_End_handler();

}



void Battlefield::BattleReset(int HP_inc, int Bullet_inc, int Monster_inc, int Trap_inc, int Score_Target_inc){
	if(player_halt){
		player_halt = false;
		return;
	}
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
