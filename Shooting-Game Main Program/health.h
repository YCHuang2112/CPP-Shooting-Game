
#ifndef HEALTH_H
#define HEALTH_H

#include<iostream>
#include<cstring>
#include"parameters.h"
#include"struct.cpp"
#include<string>

class health
{
private:
	int y;
	int HP;
	string name;
public:
	health() {};
	//void seth(int h, int p, string x) {
	//void HP_Setter(int h, int p, string x) {
	//	HP = h; y = p; name = x;
	//}
	void HP_Setter(int h) {HP = h;}
	
	int HP_Getter(){return HP;}
	string get_Name(){return name;};
	void set_Name(string name){this->name = name;};

	//void printh() {
	void Print_HP() {
		gotoxy(15, 1);
		std::cout << name.substr(0,PARA_PLAYER_NAME_MAX_LEN) << ":";
		for (int i = 0; i < HP; i++)
			std::cout << '*';

		std::cout << std::endl;
	}
	
	//void mhealth() {
	void HP_Dec() {
		HP--;

		gotoxy(14 + (HP + name.size() + 2), 1);
		cout<<' ';
	}
	//void phealth() {
	void HP_Inc() {
		HP++;
		gotoxy(15 + (HP + name.size() +1), 1);
		cout<<'*';
	}
	//bool gg(){
	bool Is_Dead(){
		if(HP<=0)return true;
		else return false;
	}
};

#endif
