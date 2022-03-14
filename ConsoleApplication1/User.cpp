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
void User::FindCardGrade(Game& game) {

	cgrade value;

	if (User::IsRSTF(game))
		value = ROYAL;
	else if (User::IsSTF(game))
		value = STF;
	else if (User::IsFourCard(game))
		value = FOURCARD;
	else if (User::IsFullHouse(game))
		value = FULLHOUSE;
	else if (User::IsFlush(game))
		value = FLUSH;
	else if (User::IsStraight(game))
		value = STRAIGHT;
	else if (User::IsTriple(game))
		value = TRIPLE;
	else if (User::IsTwoPair(game))
		value = TWOPAIR;
	else if (User::IsOnePair(game))
		value = ONEPAIR;
	else {
		value = TOP;
		Card temp[7];
		for (int i = 0; i < 5; i++) {
			temp[i] = game.tableCard[i];
		}
		for (int i = 0; i < 2; i++) {
			temp[i + 5] = userCard[i];
		}
		bool deck[4][13];
		for (int i = 0; i < 7; i++) {
			deck[temp[i].GetShape()][temp[i].GetNum()] = true;
		}
		for (int i = 0; i < 4; i++) {
			if (deck[i][0]) SetHighNum(ACE);
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 12; j > 1; j--) {
				if (deck[i][j]) SetHighNum((cnum)j);
			}
		}
	}
	User::SetHighGrade(value);
}



//조건
bool User::IsRSTF(Game& game) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = game.tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = userCard[i];
	}
	bool deck[4][13];
	for (int i = 0; i < 7; i++) {
		deck[temp[i].GetShape()][temp[i].GetNum()]=true;
	}
	for (int i = 3; i > 0; i--) {
		if (deck[i][0] && deck[i][12] && deck[i][11] && deck[i][10] && deck[i][9]) {
			SetHighNum(ACE);
			SetHighShape((cshape)i);
			return true;
		}
	}
	return false;
}
bool User::IsSTF(Game &game) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = game.tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = userCard[i];
	}
	vector<int> v[4];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetShape()].push_back(temp[i].GetNum());
	}
	for (int i = 0; i < 4; i++) {
		if (v[i].size() >= 5) {
			sort(v[i].begin(), v[i].end());
			for (int j = 0; j < v[i].size() - 4; j++) {
				if (((((v[i].at(j)) == (v[i].at(j + 1) - 1) == (v[i].at(j + 2) - 2)) == (v[i].at(j + 3) - 3)) == v[i].at(j + 4) - 4)) {
					SetHighNum((cnum)v[i].at(j + 4));
					SetHighShape((cshape)i);
					return true;
				}
			}
		}
	}
		return false;
}
bool User::IsFourCard(Game& game) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = game.tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = userCard[i];
	}
	vector<int> v[13];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetNum()].push_back(temp[i].GetShape());
	}
	for (int i = 12; i > 0; i--) {
		if (v[i].size() == 4) {
			SetHighNum((cnum)i);
			sort(v[i].begin(), v[i].end());
			SetHighShape((cshape)v[i].back());
			return true;
		}
	}
	return false;
}
bool User::IsFullHouse(Game& game) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = game.tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = userCard[i];
	}
	vector<int> v[13];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetNum()].push_back(temp[i].GetShape());
	}

	for (int i = 12; i > 0; i--) {
		if (v[i].size() == 3) {
			for (int j = 12; j > 0; j--) {
				if (i == j) continue;
				if (v[j].size() == 2) {
					sort(v[i].begin(), v[i].end());
					SetHighNum((cnum)i);
					SetHighShape((cshape)v[i].back());
					return true;
				}
			}
		}
	}
	return false;
}
bool User::IsFlush(Game& game) {
	Card temp[7];

	for (int i = 0; i < 5; i++) {
		temp[i] = game.tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = userCard[i];
	}

	vector<int> v[4];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetShape()].push_back(temp[i].GetNum());
	}

	for (int i = 0; i < 4; i++) {
		if (v[i].size() >= 5) {
			sort(v[i].begin(), v[i].end());
			SetHighNum((cnum)v[i].back());
			SetHighShape((cshape)i);
			return true;
		}
	}
	return false;
}
bool User::IsStraight(Game& game) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = game.tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = userCard[i];
	}
	vector<int> v[13];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetNum()].push_back(temp[i].GetShape());
	}
	for (int i = 12; i >4; i--) {
		if (v[i].size() > 0 && v[i - 1].size() > 0 && v[i - 2].size() > 0 && v[i - 3].size() > 0 && v[i - 4].size() > 0) {
			SetHighNum((cnum)i);
			sort(v[i].begin(), v[i].end());
			SetHighShape((cshape)v[i].back());
			return true;
		}
	}
	return false;
}
bool User::IsTriple(Game& game) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = game.tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = userCard[i];
	}
	vector<int> v[13];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetNum()].push_back(temp[i].GetShape());
	}
	for (int i = 12; i > 0; i--) {
		if (v[i].size() == 3) {
			SetHighNum((cnum)i);
			SetHighShape((cshape)v[i][2]);
			return true;
		}
	}
	return false;
}
bool User::IsTwoPair(Game& game) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = game.tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = userCard[i];
	}
	vector<int> v[13];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetNum()].push_back(temp[i].GetShape());
	}

	int pair = 0;
	int high = 0;
	for (int i = 12; i > 0; i--) {
		if (v[i].size() == 2) {
			pair++;
			if (pair == 1) high = i;
		}
		if (pair == 2) {
			SetHighNum((cnum)high);
			SetHighShape((cshape)v[high][1]);
			return true;
		}
	}
	return false;
}
bool User::IsOnePair(Game& game) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = game.tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = userCard[i];
	}
	vector<int> v[13];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetNum()].push_back(temp[i].GetShape());
	}
	for (int i = 12; i > 0; i--) {
		if (v[i].size() == 2) {
			SetHighNum((cnum)i);
			SetHighShape((cshape)v[i][1]);
			return true;
		}
	}
	return false;
}