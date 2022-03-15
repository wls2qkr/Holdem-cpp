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
	vector<User> gameUser; //유저 리스트
	int activePlayerNum; //활동플레이어(살아있는 플레이어)
	int buttonPlayer; //선플레이어 정보

	//게임정보
	int remainTime; //남은시간
	int nowStep; //현재 단계(프리플랍->플랍->턴->리버->엔드)
	int nowTurn; //현재 플레이어 턴
	vector<Card> dummy; // 카드 더미 (52장)
	int winner;
	int callMoney;
	
public:
	string vision2 = "";
	string vision[30]; // 프린트 배열
	int actionType;
	int turnIdx;
	int turnNum;
	int tableMoney; //게임 테이블 머니
	vector<Card> tableCard; // 테이블 카드 리스트
	Game() {
		tableMoney = 0;
		vision[0] =  "프리플랍->플랍->턴->리버->END|                 MY CARD               | ┌┐┌┐┌──┐┌┐  ┌─┐  ┌──┐┌┐  ┌┐ \n" ;
		vision[1] =  "                             |             ┌─────┐┌─────┐            | │││││┌┐│││  │ └┐ │┌─┘│└──┘│ \n" ;
			vision[2] = "현재 스텝 :                  |  TOP CARD   │     ││     │            | │└┘│││││││  │  │ │└─┐│┌┐┌┐│ \n" ;
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
			vision[14] = {"│                                                          │         |   \n" };
			vision[15] = {"│    ┌─────┐┌─────┐┌─────┐┌─────┐┌─────┐                   │         |   CALL MONEY\n" };
			vision[16] = {"│    │     ││     ││     ││     ││     │    TABLE MONEY    │         |   $\n" };
			vision[17] = {"│    │     ││     ││     ││     ││     │                   │         |\n" };
			vision[18] = {"│    │     ││     ││     ││     ││     │    $              │         |   BUTTON PLAYER(선플레이어)\n" };
			vision[19] = {"│    └─────┘└─────┘└─────┘└─────┘└─────┘                   │         |   >>PLAYER\n" };
			vision[20] = {"│                                                          │         |\n" };
			vision[21] = {"│   ○               ○               ○               ○  │         |   WINNER\n" };
			vision[22] = {"└  ┘ └  ──────────  ┘ └  ──────────  ┘ └  ──────────  ┘ └  ┘         |   >>PLAYER\n" };
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
	void UpdateInfoUserCade();

	string ReturnCardNum(cnum num);
	string ReturnCardShape(cshape shape);
	string ReturnCardGrade(cgrade grade);

	//액션
	bool Betting(int player, int num);

	//진행메소드
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