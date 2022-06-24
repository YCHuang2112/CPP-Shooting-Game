#include<vector>
#include<iostream>
#include<unordered_set>

using namespace std;

#ifndef BATTLEFIELD_H
#define	BATTLEFIELD_H
class Battlefield;
class monster;
class player;
class bullet;
class trap;
#include"Monster.h"
#include"Bullet.h"
#include"Player.h"
#include"struct.cpp"
#include"Trap.h"
#include"terminal_ctrl_func.cpp"
#include"parameters.h"

/*
struct Pos{
	string id;
	int idx;
	int x,y;
	
	bool operator()(const struct Pos &a, const struct Pos &b){
		return (a.x != b.x)? (a.x < b.x) : (a.y < b.y);
	}
};
*/

class Battlefield
{
	public:
		Battlefield();
		void BattleStart();
		void BattleReset(int HP_inc, int Bullet_inc, int Monster_inc, int Trap_inc, int Score_Target_inc);

//		int eventUserInput(player &p, bool &PBmove, Battlefield &BF, int cond);
		int EventUserInput(player &p, bool &PBmove, Battlefield &BF);
	bool BshotM(bullet &B);

		bool gotone(player &, trap &);
		void Mmove(player &P);
		void monster_show();
		void player_show();
		void leave_player(int &mx, int &my);
		
		int get_Stage_ID(){return Stage_ID;} 
		int get_Score(){return score;} 
		string get_Player_Name(){return pp->get_Name();} 
		void set_Player_Name(string name){return pp->set_Name(name);} 
		bool get_Player_Dead(){return player_dead;}
	private:
        int score_target = PARA_TARGET_SCORE_INIT_VAL;
        //const int score_target = PARA_TARGET_SCORE_INIT_VAL;

		vector<monster> Mlist;
		//vector<player> Plist;
		vector<trap> Tlist;
		
		//map<pair<int,int>, List<Monster>> M_Pos_Monsters;
 		
		int Mmax, Tmax;
//		player &p;
		int Stage_ID = 1;
		int score;
		int mwidth, mheight;
		bool player_dead = false;

		player *pp;
		friend class monster;
		friend class player;
		friend class bullet;
		friend class trap;
};
#endif

