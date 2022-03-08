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
	//유저정보
	vector<User> gameUser;
	int activePlayerNum;
	int buttonPlayer;

	//게임정보
	int remainTime;
	int nowStep;
	int nowTurn;
	vector<Card> dummy;
	int winner;
	
public:
	string vision[30];
	int actionType;
	int tableMoney;
	vector<Card> tableCard;
	Game() {
		tableMoney = 0;
		gameUser.push_back(User("GOOD"));
		gameUser.push_back(User("EXCELEN"));
		gameUser.push_back(User("EXCELEN"));
		gameUser.push_back(User("EXCELEN"));
		gameUser.push_back(User("EXCELEN"));
		gameUser.push_back(User("EXCELEN"));
		gameUser.push_back(User("EXCELEN"));
		gameUser[1].SetBeforeBetting("FOLD");
		gameUser[2].SetBeforeBetting("FOLD");
		
		
		vision[0] = { "프리플랍->플랍->턴->리버->END|                 MY CARD               | ┌┐┌┐┌──┐┌┐  ┌─┐  ┌──┐┌┐  ┌┐ \n" };
		vision[1] = { "                             |             ┌─────┐┌─────┐            | │││││┌┐│││  │ └┐ │┌─┘│└──┘│ \n" };
			vision[2] = {"현재 스텝 :                  |  TOP CARD   │     ││     │            | │└┘│││││││  │  │ │└─┐│┌┐┌┐│ \n" };
			vision[3] = {"플레이어 턴 :                |             │     ││     │            | │┌┐│││││││  │　│ │┌─┘││││││ \n" };
			vision[4] = {"남은 플레이어 수 :           |             │     ││     │            | │││││└┘││└─┐│ ┌┘ │└─┐││││││ \n" };
			vision[5] = {"                             |             └─────┘└─────┘            | └┘└┘└──┘└──┘└─┘  └──┘└┘└┘└┘ \n" };
			vision[6] = {"=============================|=======================================|=============================\n" };
			vision[7] = {"                                                                     |      \n" };
			vision[8] = {"                                                                     |   BETTING   \n" };
			vision[9] = {"                                                                     |   ① FOLD  \n" };
			vision[10] = {"                                                                     |   ② $100  \n" };
			vision[11] = {"                                                                     |   ③ $300  \n" };
			vision[12] = {"    ○               ○               ○               ○            |   ④ $1000 \n" };
			vision[13] = {"┌  ┘ └  ──────────  ┘ └  ──────────  ┘ └  ──────────  ┘ └  ┐         |   ⑤ $ALL-IN\n" };
			vision[14] = {"│                                                          │\n" };
			vision[15] = {"│    ┌─────┐┌─────┐┌─────┐┌─────┐┌─────┐                   │\n" };
			vision[16] = {"│    │     ││     ││     ││     ││     │    TABLE MONEY    │\n" };
			vision[17] = {"│    │     ││     ││     ││     ││     │                   │\n" };
			vision[18] = {"│    │     ││     ││     ││     ││     │    $              │\n" };
			vision[19] = {"│    └─────┘└─────┘└─────┘└─────┘└─────┘                   │\n" };
			vision[20] = {"│                                                          │\n" };
			vision[21] = {"│   ○               ○               ○               ○  │\n" };
			vision[22] = {"└  ┘ └  ──────────  ┘ └  ──────────  ┘ └  ──────────  ┘ └  ┘\n" };
			vision[23] = {"                                                                  \n" };
			vision[24] = {"                                                                  \n" };
			vision[25] = {"                                                                  \n" };
			vision[26] = {"                                                                  \n" };
			vision[27] = {"                                                                  \n" };
			vision[28] = { "===================================================================================================\n" };
			
	}

	//유저정보
	void AddGameUser(User u);
	vector<User> GetGameUser();
	void SetActivePlayerNum(int num);
	int GetActivePlayerNum();
	void SetButtonPlayer(int num);
	int GetButtonPlayer();


	//게임정보

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


	//게임정보변경메소드
	void PrintGameStatus();

	void Update();
	void UpdateInfoTableMoney();
	void UpdateInfoTableCardNum();
	void UpdateInfoTableCardShape();
	void UpdateUserCard();
	void UpdatePlayerStatus();
	void UpdateGameStatus();

	string ReturnCardNum(cnum num);
	string ReturnCardShape(cshape shape);
	string ReturnCardGrade(cgrade grade);

	//진행메소드
	void InitialGame();
	Card GetDummy();
	void AllocateHand();
	void AllocateFolpCard();
	void AllocateTurnCard();
	void AllocateRiverCard();

	bool CheckActivePlayer();

	bool Action(int num);

	void Betting();
	int JudgeWinner();
	void EndGame();
};
#endif