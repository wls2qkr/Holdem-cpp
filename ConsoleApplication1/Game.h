#ifndef __GAME_H__
#define __GAME_H__
#include "Card.h"
#include "var.h"
#include "User.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#pragma once
using namespace std;

class Game {
private:
	//��������
	vector<User> gameUser; //���� ����Ʈ
	int activePlayerNum; //Ȱ���÷��̾�(����ִ� �÷��̾�)
	int buttonPlayer; //���÷��̾� ����

	//��������
	int remainTime; //�����ð�
	int nowStep; //���� �ܰ�(�����ö�->�ö�->��->����->����)
	int nowTurn; //���� �÷��̾� ��
	vector<Card> dummy; // ī�� ���� (52��)
	int winner;
	int callMoney;
	
public:
	string vision2 = "";
	string vision[30]; // ����Ʈ �迭
	int actionType;
	int turnIdx;
	int turnNum;
	int tableMoney; //���� ���̺� �Ӵ�
	vector<Card> tableCard; // ���̺� ī�� ����Ʈ
	Game() {
		tableMoney = 0;
		vision[0] =  "�����ö�->�ö�->��->����->END|                 MY CARD               | ��������������������  ������  ������������  ���� \n" ;
		vision[1] =  "                             |             ����������������������������            | ��������������������  �� ���� �������������������� \n" ;
			vision[2] = "���� ���� :                  |  TOP CARD   ��     ����     ��            | ��������������������  ��  �� �������������������� \n" ;
			vision[3] = {"�÷��̾� �� :                |             ��     ����     ��            | ��������������������  ������ �������������������� \n" };
			vision[4] = {"���� �÷��̾� �� :           |             ��     ����     ��            | �������������������������� ���� �������������������� \n" };
			vision[5] = {"                             |             ����������������������������            | ������������������������������  �������������������� \n" };
			vision[6] = {"=============================|=======================================|=============================\n" };
			vision[7] = {"                                                                     |      \n" };
			vision[8] = {"                                                                     |   BETTING   \n" };
			vision[9] = {"                                                                     |   �� FOLD  \n" };
			vision[10] = {"                                                                     |   �� $100  \n" };
			vision[11] = {"                                                                     |   �� $300  \n" };
			vision[12] = {"    ��               ��               ��               ��            |   �� $1000 \n" };
			vision[13] = {"��  �� ��  ��������������������  �� ��  ��������������������  �� ��  ��������������������  �� ��  ��         |   �� $ALL-IN\n" };
			vision[14] = {"��                                                          ��         |   \n" };
			vision[15] = {"��    ����������������������������������������������������������������������                   ��         |   CALL MONEY\n" };
			vision[16] = {"��    ��     ����     ����     ����     ����     ��    TABLE MONEY    ��         |   $\n" };
			vision[17] = {"��    ��     ����     ����     ����     ����     ��                   ��         |\n" };
			vision[18] = {"��    ��     ����     ����     ����     ����     ��    $              ��         |   BUTTON PLAYER(���÷��̾�)\n" };
			vision[19] = {"��    ����������������������������������������������������������������������                   ��         |   >>PLAYER\n" };
			vision[20] = {"��                                                          ��         |\n" };
			vision[21] = {"��   ��               ��               ��               ��  ��         |   WINNER\n" };
			vision[22] = {"��  �� ��  ��������������������  �� ��  ��������������������  �� ��  ��������������������  �� ��  ��         |   >>PLAYER\n" };
			vision[23] = {"                                                                     |\n" };
			vision[24] = {"                                                                     |\n" };
			vision[25] = {"                                                                     |\n" };
			vision[26] = {"                                                                     |\n" };
			vision[27] = {"                                                                     |\n" };
			vision[28] = { "===================================================================================================\n" };
			for (int i = 0; i < 30; i++) {
				vision2 += vision[i];
			}
	}

	//��������
	void AddGameUser(User u);
	vector<User> GetGameUser();
	void SetActivePlayerNum(int num);
	int GetActivePlayerNum();
	void SetButtonPlayer(int num);
	int GetButtonPlayer();


	//��������

	void SetRemainTime(int num);
	int GetRemainTime();
	void SetTableMoney(int num);
	void AddTableMoney(int num);
	int GetTableMoney();
	void SetNowStep(int num);
	int GetNowStep();
	void SetNowTurn(int num);
	int GetNowTurn();
	vector<Card> GetTableCard();


	//������������޼ҵ�
	void PrintGameStatus();

	void Update();
	void UpdateInfoTableMoney();
	void UpdateInfoTableCardNum();
	void UpdateInfoTableCardShape();
	void UpdateUserCard();
	void UpdatePlayerStatus();
	void UpdateGameStatus();
	void UpdateInfoUserCade();

	string ReturnCardNum(cnum num);
	string ReturnCardShape(cshape shape);
	string ReturnCardGrade(cgrade grade);

	//�׼�
	bool Betting(int player, int num);

	//����޼ҵ�
	void InitialGame();
	Card GetDummy();
	void AllocateHand();
	void AllocateFolpCard();
	void AllocateTurnCard();
	void AllocateRiverCard();

	bool CheckActivePlayer();

	void ReturnUserAction();

	//bool Action(int num, User &user);

	void Betting();
	int JudgeWinner();
	void EndGame();
};
#endif