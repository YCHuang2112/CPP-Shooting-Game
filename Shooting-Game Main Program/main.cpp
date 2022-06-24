#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>
#include<termios.h>
#include<time.h>
#include<vector>
#include<map>
#include<utility>
#include<algorithm>

#include"battlefield.cpp"
#include"monster.cpp"
#include"player.cpp"
#include"bullet.cpp"
#include"trap.cpp"
#include"terminal_ctrl_func.cpp"
#include"parameters.h"
using namespace std;

using pii = pair<int,int>;

void Ask_User_Name(Battlefield &BF){
	string name;
	cout << "please enter your name" << endl;
	cin >> name;
	name = name.substr( 0,min((int)name.size(),PARA_PLAYER_NAME_MAX_LEN) );
	cout << "Your name: " << name << endl;
	BF.set_Player_Name(name);
}


void load_record( map<pii, string, greater<pii>> &Score_Board){
	FILE* fp = fopen("score_board.txt", "a+");
	int score, stage;
	char ch[40];
	while(fscanf(fp,"%d %d %s", &score, &stage, ch) == 3){
		Score_Board[ pii(score,stage) ] = string(ch, PARA_PLAYER_NAME_MAX_LEN);
	}
	fclose(fp);
}

void write_record( map<pii, string, greater<pii>> &Score_Board){
	FILE* fp = fopen("score_board.txt", "w");
	int i = PARA_TOP_RECORD_NUM;
	for(auto &SB: Score_Board){
		i--;
		auto &score_stage = SB.first;
		fprintf(fp,"%d %d %s\n", score_stage.first, score_stage.second, SB.second.c_str() );
		if(i==0){break;}
	}
	fclose(fp);
}

int main() {
	srand(time(NULL));	
	Battlefield BF;
	
	Ask_User_Name(BF);
	
	map<pii, string, greater<pii>> Score_Board;
	load_record(Score_Board);
	
//here:
	while(1){
		BF.BattleStart();
		
		int i = PARA_TOP_RECORD_NUM;
		gotoxy(width/2 - 10 < 0 ? 0 : width/2 - 10, height/2 - 1-i -1);
		printf(" \033[m %20s","Highest Score");
		gotoxy(width/2 - 10 < 0 ? 0 : width/2 - 10, height/2 - 1-i);
		printf(" \033[m %6s %6s %10s","Score", "Stage", "Name");
		for(auto &SB: Score_Board){
			i--;
			gotoxy(width/2 - 10 < 0 ? 0 : width/2 - 10, height/2 - 1-i);
			auto &score_stage = SB.first;
			printf(" \033[m %6d %6d %10s",score_stage.first, score_stage.second, SB.second.c_str());
			if(i==0){break;}
		}
		
		gotoxy(width/2 - 10 < 0 ? 0 : width/2 - 10, height/2 +2);
		cout << "Press \"" "\033[1;33m" "Backspace" "\033[m" "\" to quit!" << endl;
		gotoxy(width/2 - 10 < 0 ? 0 : width/2 - 10, height/2 +3);
		cout << "Press \"" "\033[1;33m" "Ctrl+s" "\033[m" "\" to start a new game!" << endl;
		while(char c = getchar()	){
//cout << ((int) c) << endl;		
			if(c == 0X7f){  //Backspace
				reset_terminal_mode();
				clearScreen();
				gotoxy(0, 0);
				showCursor();
				
				Score_Board[ pii(BF.get_Score(), BF.get_Stage_ID()) ] = BF.get_Player_Name();
				write_record(Score_Board);
				
				return 0;		
			}
			
			if(c == 19){  //Ctrl+s
				if(BF.get_Player_Dead()){
					Score_Board[ pii(BF.get_Score(), BF.get_Stage_ID()) ] = BF.get_Player_Name();
				}
				
				reset_terminal_mode();
				
				int HP_inc = 1;
				int Bullet_inc = 2;
				int Monster_inc = 3;
				int Trap_inc = 1;
				int Score_Target_inc = 10 + BF.get_Stage_ID();
				BF.BattleReset(HP_inc, Bullet_inc, Monster_inc, Trap_inc, Score_Target_inc);
				break;
			}
			//if(c == 0X7f){break;}
		}
	}
	


/*
	reset_terminal_mode();
	clearScreen();
	gotoxy(0, 0);
	showCursor();
*/
	return 0;
}











