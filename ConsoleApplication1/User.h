#ifndef __USER_H__
#define __USER_H__

#include <vector>
#include <cstring>
#include "Card.h"
#include "var.h"

using namespace std;
class Game;

class User {
private:
	//유저정보
	string name;
	int userMoney;

	bool isButtonPlayer; //선플레이어인지 아닌지
	bool alive; // 다이 or Alive
	string beforeBetting; // 이전 배팅 상태

	//카드정보
	vector<Card> userCard; //유저 카드리스트
	cnum HighNum; // 높은 숫자
	cshape HighShape; // 높은 모양
	cgrade HighGrade; // 높은 패조합

public:
	User(string name) {
		this->name = name;
		userMoney = 10000;
		HighNum = TWO;
		HighGrade = TOP;
		HighShape = CLOVER;
	}

	//유저정보
	bool SetUserName(string name);
	string GetUserName();

	void SetUserMoney(int amount);
	void AddUserMoney(int amount);
	int GetUserMoney();

	void SetBeforeBetting(string bet);
	string GetBeforeBetting();

	void SetButtonPlayer();
	bool GetButtonPlayer();
	void SetAlive(bool status);
	bool GetAlive();

	//카드
	void SetUserCard(vector<Card> v);
	vector<Card> GetUserCard();

	void SetHighNum(cnum num);
	cnum GetHighNum();
	void SetHighShape(cshape shape);
	cshape GetHighShape();
	void SetHighGrade(cgrade grade);
	cgrade GetHighGrade();
	void FindCardGrade(Game& game);

	//액션
	

	//조건
	bool IsRSTF(Game& game);
	bool IsSTF(Game& game);
	bool IsFourCard(Game& game);
	bool IsFullHouse(Game& game);
	bool IsFlush(Game& game);
	bool IsStraight(Game& game);
	bool IsTriple(Game& game);
	bool IsTwoPair(Game& game);
	bool IsOnePair(Game& game);
};
#endif
