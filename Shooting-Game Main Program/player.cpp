#include"Player.h"

	player::player() 
		:py(height/2), px(width/2), maxbullet(PARA_MAX_BULLET_NUM_INIT), face(Down)
		{
			//health::HP_Setter(PARA_PLAYER_HP_INIT_VAL, height + 5, "Player");
			health::HP_Setter(PARA_PLAYER_HP_INIT_VAL);
			//emerge();
		}


	void player::action(char act) {
		if(act == ' ' && Blist.size() >= maxbullet) return;
		clear();
		switch (act) {
			
			case 'A': py-=1;	 face = Down;    break;
			case 'B': py+=1;	 face = Up;  break;
			case 'C': px+=1;	 face = Right;  break;
			case 'D': px-=1;	 face = Left; break;
			case ' ': Blist.push_back( bullet(face, px, py));

		}

		BF_Bound_Checker(px, py);
		emerge();
	}

	void player::act(char ch, bool Bmove, Battlefield &BF)
	{	
			
		if(ch >= 'A' && ch <= 'D'  || ch == ' ')
		{
			action(ch);
			//BF.monster_show();
		}
	}
	void player::bullet_renew(Battlefield &BF)
	{
		for(int i = Blist.size() -1 ; i >= 0; i--)
			if( Blist[i].move_shot(BF) ) Blist.erase( Blist.begin() + i );
	}

	bool player::Bhurt(int mx, int my)
	{
		bool haveshoot = false;
		for(int i = Blist.size()-1; i  >= 0; i--)
			
			if(Blist[i].bx == mx && Blist[i].by == my)
			{	
				if(!Blist.size()) break;
				Blist[i].clear();
				Blist.erase( Blist.begin() + i);
				haveshoot = true;
			}
		if(haveshoot)		return true;
		return false;
	}
	
	void player::reset() {
		py = height/2;
		px = width/2;
		
		maxbullet = PARA_MAX_BULLET_NUM_INIT;
		Blist.clear();
		
		face = Down;
		//HP_Setter(PARA_PLAYER_HP_INIT_VAL, height + 5, "Player");
		HP_Setter(PARA_PLAYER_HP_INIT_VAL);
	}
	void player::reset(int HP_inc, int Bullet_inc) {
		py = height/2;
		px = width/2;
		
		maxbullet = min(maxbullet+Bullet_inc,12);
		Blist.clear();
		
		face = Down;
		//HP_Setter( min(HP_Getter()+HP_inc,16), height + 5, "Player");
		HP_Setter(min(HP_Getter()+HP_inc,16));
	}