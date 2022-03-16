#include <iostream>
#include <cstring>
#include "User.h"
#include "Game.h"
#include <vector>
#include <algorithm>

using namespace std;

#pragma warning(disable:4996)

bool User::SetUserName(string name) {
	if (name.length() > 20 || name.length() < 0) {
		cout << "길이가 맞지 않습니다." << endl;
		return false;
	}
	else {
		this->name = name;
		cout << "name: " << this->name << endl;
		return true;
	}
}
string User::GetUserName() {
	return this->name;
}

void User::SetUserMoney(int amount) {
	this->userMoney = amount;
}
void User::AddUserMoney(int amount) {
	this->userMoney += amount;
}
int User::GetUserMoney() {
	return this->userMoney;
}

void User::SetBeforeBetting(string bet) {
	this->beforeBetting = bet;
}
string User::GetBeforeBetting() {
	return this->beforeBetting;
}

//void User::SetButtonPlayer() {
//	this->isButtonPlayer = !this->isButtonPlayer;
//}

void User::SetUserCard(vector<Card> v) {
	this->userCard = v;
}
vector<Card> User::GetUserCard() {
	return this->userCard;
}
void User::SetAlive(bool status) {
	this->alive = status;
}
bool User::GetAlive() {
	return this->alive;
}

//카드
void User::SetHighNum(cnum num) {
	this->HighNum = num;
}
cnum User::GetHighNum() {
	return this->HighNum;
}
void User::SetHighShape(cshape shape) {
	this->HighShape = shape;
}
cshape User::GetHighShape() {
	return this->HighShape;
}
void User::SetHighGrade(cgrade grade) {
	this->HighGrade = grade;
}
cgrade User::GetHighGrade() {
	return this->HighGrade;
}




