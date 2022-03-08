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
	//��������
	string name;
	int userMoney;

	bool isButtonPlayer; //���÷��̾����� �ƴ���
	bool alive; // ���� or Alive
	string beforeBetting; // ���� ���� ����

	//ī������
	vector<Card> userCard; //���� ī�帮��Ʈ
	cnum HighNum; // ���� ����
	cshape HighShape; // ���� ���
	cgrade HighGrade; // ���� ������

public:
	User(string name) {
		this->name = name;
		userMoney = 10000;
		HighNum = TWO;
		HighGrade = TOP;
		HighShape = CLOVER;
	}

	//��������
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

	//ī��
	void SetUserCard(vector<Card> v);
	vector<Card> GetUserCard();

	void SetHighNum(cnum num);
	cnum GetHighNum();
	void SetHighShape(cshape shape);
	cshape GetHighShape();
	void SetHighGrade(cgrade grade);
	cgrade GetHighGrade();
	void FindCardGrade(Game& game);

	//�׼�
	

	//����
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
