#include"Bullet.h"

bullet::bullet() {
		dir = Stop;
		bx = by = 100;
	};

bullet::bullet(edir d, int x, int y) 
		:dir(d), bx(x), by(y), show(false)
	{};

/*	bullet::bullet(player &p) {
		dir = p.face;
		bx = p.x;
		by = p.y;
		show = false;
	}
	void bullet::kill() {
		show = false;
		bx = by = 70;
		dir = Stop;
	}
	void bullet::attack(palyer &p)
	{
		bx = p.px;
		by = p.py;
		dir = p.face;
		show = false;
	}
*/
/*	void bullet::atk(player &p) {
		if (p.getdir() == Attack) {
			bx = p.getx();
			by = p.gety();
			dir = p.getface();
			show = false;
		}
	}
*/
	
	bool bullet::move_shot(Battlefield &BF) {
		
		if(show) clear();
		switch (dir) {
			case Down : by-=1; break;
			case Up   : by+=1; break;
			case Right: bx+=1; break;
			case Left : bx-=1; break;
		}
		show = true;
		if( BF.BshotM(*this)) return true;
		/*BF_Bound_Checker(bx, by);*/  if(bx < minw || bx > width || by < minh || by > height) return true;		
		//emerge();
		return false;
	}
