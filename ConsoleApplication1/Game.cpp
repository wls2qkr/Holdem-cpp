#include<iostream>
#include<cstdlib>
#include<ctime>
#include "Card.h"

#include "Game.h"

//유저정보
void Game::AddGameUser(User u) {
	this->gameUser.push_back(u);
}
vector<User> Game::GetGameUser() {
	return this->gameUser;
}
void Game::SetActivePlayerNum(int num) {
	this->activePlayerNum = num;
}
int Game::GetActivePlayerNum() {
	return this->activePlayerNum;
}
void Game::SetRemainTime(int num) {
	this->remainTime=num;
}
int Game::GetRemainTime() {
	return this->remainTime;
}
void Game::SetTableMoney(int num) {
	this->tableMoney;
}
int Game::GetTableMoney() {
	return this->tableMoney;
}
void Game::SetNowStep(int num) {
	this->nowStep=num;
}
int Game::GetNowStep() {
	return this->nowStep;
}
void Game::SetNowTurn(int num) {
	this->nowTurn = num;
}
int Game::GetNowTurn() {
	return this->nowTurn;
}
void Game::SetButtonPlayer(int num) {
	this->buttonPlayer = num;
}
int Game::GetButtonPlayer() {
	return this->buttonPlayer;
}

//게임정보/
vector<Card> Game::GetTableCard() {
	return this->tableCard;
}
void Game::AddTableMoney(int num) {
	this->tableMoney += num;
}


//게임정보업데이트메소드
//한글깨짐확인
void Game::PrintGameStatus() {
	for (int i = 1; i < 27; i++) {
		cout << vision[i];
	}
}

void Game::Update() {
	UpdatePlayerStatus();
	UpdateGameStatus();
	UpdateInfoTableMoney();
	UpdateInfoTableCardNum();
	UpdateInfoTableCardShape();
}

void Game::UpdateInfoTableMoney() {
	string money = to_string(tableMoney);
	vision[18].replace(56, money.length(), money);
}
void Game::UpdateInfoTableCardNum() {
	int idx = 0;
	for (int i = 0; i < tableCard.size(); i ++) {
		if(tableCard[i].GetNum() == 0)
			vision[16].replace(10 + idx, 2, "Ａ");
		else if(tableCard[i].GetNum() == 1)
			vision[16].replace(10 + idx, 2, "２");
		else if (tableCard[i].GetNum() == 2)
			vision[16].replace(10 + idx, 2, "３");
		else if (tableCard[i].GetNum() == 3)
			vision[16].replace(10 + idx, 2, "４");
		else if (tableCard[i].GetNum() == 4)
			vision[16].replace(10 + idx, 2, "５");
		else if (tableCard[i].GetNum() == 5)
			vision[16].replace(10 + idx, 2, "６");
		else if (tableCard[i].GetNum() == 6)
			vision[16].replace(10 + idx, 2, "７");
		else if (tableCard[i].GetNum() == 7)
			vision[16].replace(10 + idx, 2, "８");
		else if (tableCard[i].GetNum() == 8)
			vision[16].replace(10 + idx, 2, "９");
		else if (tableCard[i].GetNum() == 9)
			vision[16].replace(10 + idx, 2, "10");
		else if (tableCard[i].GetNum() == 10)
			vision[16].replace(10 + idx, 2, "Ｊ");
		else if (tableCard[i].GetNum() == 11)
			vision[16].replace(10 + idx, 2, "Ｑ");
		else if (tableCard[i].GetNum() == 12)
			vision[16].replace(10 + idx, 2, "Ｋ");
		idx += 9;
	}
}
void Game::UpdateInfoTableCardShape() {
	int idx = 0;
	for (int i = 0; i < tableCard.size(); i++) {
		if (tableCard[i].GetNum() == 0)
			vision[18].replace(10 + idx, 2, "♣");
		else if (tableCard[i].GetShape() == 1)
			vision[18].replace(10 + idx, 2, "♥");
		else if (tableCard[i].GetShape() == 2)
			vision[18].replace(10 + idx, 2, "◆");
		else if (tableCard[i].GetShape() == 3)
			vision[18].replace(10 + idx, 2, "♠");
		idx += 9;
	}
}
void Game::UpdatePlayerStatus() {
	int idx = 0;
	int num = 0;
	if (gameUser.size() > 4) num = 4;
	else num = gameUser.size();

	for (int i = 1; i <= num; i++) {
		string str = "PLAYER";
		str += to_string(i);
		vision[7].replace(idx, 5, str);

		string name = gameUser[i-1].GetUserName();
		vision[8].replace(idx, name.length(), name);

		string money = "$";
		money += to_string(gameUser[i - 1].GetUserMoney());
		vision[9].replace(idx, money.length(), money);

		string status = gameUser[i - 1].GetBeforeBetting();
		vision[10].replace(idx, status.length(), status);

		
		string grade = ReturnCardShape(gameUser[i - 1].GetHighShape());
		grade += ReturnCardNum(gameUser[i - 1].GetHighNum());
		grade += "";
		grade += ReturnCardGrade(gameUser[i - 1].GetHighGrade());
		vision[11].replace(idx, grade.length(), grade);

		idx += 17;
	}

	if (gameUser.size() > 4) {
		idx = 51;
		for (int i = 5; i <= gameUser.size(); i++) {
			string str = "PLAYER";
			str += to_string(i);
			vision[23].replace(idx, 7, str);

			string name = gameUser[i - 1].GetUserName();
			vision[24].replace(idx, name.length(), name);

			string money = "$";
			money += to_string(gameUser[i - 1].GetUserMoney());
			vision[25].replace(idx, money.length(), money);

			string status = gameUser[i - 1].GetBeforeBetting();
			vision[26].replace(idx, status.length(), status);

			string grade = ReturnCardShape(gameUser[i - 1].GetHighShape());
			grade += ReturnCardNum(gameUser[i - 1].GetHighNum());
			grade += "";
			grade += ReturnCardGrade(gameUser[i - 1].GetHighGrade());
			vision[27].replace(idx, grade.length(), grade);


			idx -= 17;
		}
	}
}
void Game::UpdateGameStatus() {

	//남은 플레이어 수
	string remainPlayer = to_string(GetActivePlayerNum());
	vision[3].replace(20, remainPlayer.length(), remainPlayer);
	string nowTurn = to_string(GetNowTurn());
	vision[2].replace(14, nowTurn.length(), nowTurn);
	int step = GetNowStep();

}

string Game::ReturnCardNum(cnum num) {
	if (num == 0) return "Ａ";
	else if (num == 1) return "２";
	else if (num == 2) return "３";
	else if (num == 3) return "４";
	else if (num == 4) return "５";
	else if (num == 5) return "６";
	else if (num == 6) return "７";
	else if (num == 7) return "８";
	else if (num == 8) return "９";
	else if (num == 9) return "10";
	else if (num == 10) return "Ｊ";
	else if (num == 11) return "Ｑ";
	else return "Ｋ";
}
string Game::ReturnCardShape(cshape shape) {
	if (shape == 0) return "♣";
	else if (shape == 1) return "♥";
	else if (shape == 2) return "◆";
	else return "♠";
}
string Game::ReturnCardGrade(cgrade grade) {
	if (grade == 0) return "TOP";
	else if (grade == 1) return "ONEPAIR";
	else if (grade == 2) return "TWOPAIR";
	else if (grade == 3) return "TRIPLE";
	else if (grade == 4) return "STRAIGHT";
	else if (grade == 5) return "FLUSH";
	else if (grade == 6) return "FULLHOUSE";
	else if (grade == 7) return "FOURCARD";
	else if (grade == 8) return "STF";
	else return "ROYAL";
}

//진행메소드
void Game::InitialGame() {
	this->dummy.clear();
	this->dummy = {
		Card(ACE, SPADE), Card(TWO,SPADE),Card(THREE,SPADE), Card(FOUR,SPADE), Card(FIVE,SPADE), Card(SIX,SPADE), Card(SEVEN,SPADE), Card(EIGHT,SPADE), Card(NINE,SPADE),Card(TEN,SPADE),Card(JACK,SPADE),Card(QUEEN,SPADE),Card(KING,SPADE),
		Card(ACE, HEART), Card(TWO,HEART),Card(THREE,HEART), Card(FOUR,HEART), Card(FIVE,HEART), Card(SIX,HEART), Card(SEVEN,HEART), Card(EIGHT,HEART), Card(NINE,HEART),Card(TEN,HEART),Card(JACK,HEART),Card(QUEEN,HEART),Card(KING,HEART),
		Card(ACE, DIA), Card(TWO,DIA),Card(THREE,DIA), Card(FOUR,DIA), Card(FIVE,DIA), Card(SIX,DIA), Card(SEVEN,DIA), Card(EIGHT,DIA), Card(NINE,DIA),Card(TEN,DIA),Card(JACK,DIA),Card(QUEEN,DIA),Card(KING,DIA),
		Card(ACE, CLOVER), Card(TWO,CLOVER),Card(THREE,CLOVER), Card(FOUR,CLOVER), Card(FIVE,CLOVER), Card(SIX,CLOVER), Card(SEVEN,CLOVER), Card(EIGHT,CLOVER), Card(NINE,CLOVER),Card(TEN,CLOVER),Card(JACK,CLOVER),Card(QUEEN,CLOVER),Card(KING,CLOVER)
	};

	//테이블 카드초기화
	GetTableCard().clear();

	//유저 카드초기화
	for (int i = 0; i < gameUser.size(); i++) {
		gameUser[i].GetUserCard().clear();
	}
}
Card Game::GetDummy() {
	srand((unsigned int)time(NULL));
	int num = rand() % this->dummy.size() - 1;
	Card value = this->dummy.at(num);
	this->dummy.erase(this->dummy.begin()+num);
	return value;
}

void Game::AllocateHand() {
	for (int i = 0; i < gameUser.size(); i++) {
		gameUser[i].GetUserCard().push_back(GetDummy());
		gameUser[i].GetUserCard().push_back(GetDummy());
	}
}
void Game::AllocateFolpCard() {
	for (int i = 0; i < 3; i++) {
		GetTableCard().push_back(GetDummy());
	}
}
void Game::AllocateTurnCard() {
	GetTableCard().push_back(GetDummy());
}
void Game::AllocateRiverCard() {
	GetTableCard().push_back(GetDummy());
}

bool Game::CheckActivePlayer() {
	if (activePlayerNum == 1) return true;
	else false;
}

//bool Game::Action(int num) {
//	switch (num) {
//
//		//FOLD
//	case 0:
//		Game::actionType = 0;
//		this->alive = false;
//		break;
//
//		//100
//	case 1:
//		if (Game::actionType <= 1) {
//			Game::actionType = 1;
//			Game::tableMoney += 100;
//			this->userMoney -= 100;
//			return true;
//		}
//		else return false;
//		break;
//
//		//300
//	case 2:
//		if (Game::actionType <= 2) {
//			Game::actionType = 2;
//			Game::tableMoney += 300;
//			this->userMoney -= 300;
//			return true;
//		}
//		else return false;
//		break;
//
//		//1000
//	case 3:
//		if (Game::actionType <= 3) {
//			Game::actionType = 3;
//			Game::tableMoney += 1000;
//			this->userMoney -= 1000;
//			return true;
//		}
//		else return false;
//		break;
//		//ALL-IN
//	case 4:
//		if (Game::actionType <= 4) {
//			Game::actionType = 4;
//			Game::tableMoney += this->userMoney;
//			this->userMoney = 0;
//			return true;
//		}
//		else return false;
//		break;
//	}
//	return false;
//}


void Game::Betting() {
	int idx = GetButtonPlayer(); // 2번이 선이라면 2번 인덱스인 1을 저장
	int num = activePlayerNum;
	for (int i = 0; i < num; i++) {
		idx = idx++ % num;
		if (gameUser[idx].GetAlive()) {
			while (1) {/*
				if (gameUser[idx].Action(1)) {
					break;
				}*/
				//유저에게 응답을 받는 메소드
				/*else {
					cout << "다시" << endl;
				}*/
			}
		}
	}
}

int Game::JudgeWinner() {
	int winner = -1;
	int grade = -1;
	int number = -1;
	int shape = -1;

	for (int i = 0; i < gameUser.size(); i++) {
		if (!gameUser[i].GetAlive()) continue;
		if (gameUser[i].GetHighGrade() > grade) {
			grade = gameUser[i].GetHighGrade();
			number = gameUser[i].GetHighNum();
			shape = gameUser[i].GetHighShape();
			winner = i;
		}
		else if (gameUser[i].GetHighGrade() == grade) {
			if (gameUser[i].GetHighNum() > number) {
				grade = gameUser[i].GetHighGrade();
				number = gameUser[i].GetHighNum();
				shape = gameUser[i].GetHighShape();
				winner = i;
			}
			else if (gameUser[i].GetHighNum() == number) {
				if (gameUser[i].GetHighShape() > shape) {
					grade = gameUser[i].GetHighGrade();
					number = gameUser[i].GetHighNum();
					shape = gameUser[i].GetHighShape();
					winner = i;
				}
			}
		}
	}
	return winner;
}

void Game::EndGame() {
	//정산
	int winner = JudgeWinner();
	gameUser[winner].AddUserMoney(tableMoney);
	tableMoney = 0;
	//선플레이어 선정
	Game::SetButtonPlayer(winner);
	//턴 초기화
	Game::SetNowStep(0);
	Game::SetNowTurn(0);
}
