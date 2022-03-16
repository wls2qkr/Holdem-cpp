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
void Game::AddTableMoney(int num) {
	this->tableMoney += num;
}

//게임정보업데이트메소드
void Game::PrintGameStatus() {
	UpdateInfoUserCard(1);
	for (int i = 0; i < 29; i++) {
		cout << vision[i];
	}
	if (GetNowStep() == 2) cout << "플랍 스테이지 시작\n";
	else if (GetNowStep() == 3) cout << "턴 스테이지 시작\n";
	else if (GetNowStep() == 4) cout << "리버 스테이지 시작\n";
	else if (GetNowStep() == 5) cout << "엔드 스테이지\n";
}

void Game::Update() {
	vision2.clear();
	UpdatePlayerStatus();
	UpdateGameStatus();
	UpdateInfoTableMoney();
	UpdateInfoTableCardNum();
	UpdateInfoTableCardShape();
	PrintGameStatus();
	if (GetButtonPlayer() == 0) cout << "클라이언트의 승리\n";
	else if (GetButtonPlayer() == 1) cout << "서버의 승리\n";
	UpdateInfoUserCard(0);
	for (int i = 0; i < 30; i++) {
		vision2 += vision[i];
	}
}

void Game::UpdateInfoTableMoney() {
	string money = to_string(tableMoney);
	int size = 7;
	vision[18].replace(56, money.length(), money);
	fill(vision[18].begin() + 56 + money.length(), vision[18].begin() + 56 + size, ' ');

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
		if (tableCard[i].GetShape() == 0)
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
void Game::UpdateInfoUserCard(int num) {
	int idx = 0;
	for (int i = 0; i < 2; i++) {
		
		if (GetGameUser()[num].GetUserCard()[i].GetShape() == 0)
			vision[4].replace(47 + idx, 2, "♣");
		else if (GetGameUser()[num].GetUserCard()[i].GetShape() == 1)
			vision[4].replace(47 + idx, 2, "♥");
		else if (GetGameUser()[num].GetUserCard()[i].GetShape() == 2)
			vision[4].replace(47 + idx, 2, "◆");
		else if (GetGameUser()[num].GetUserCard()[i].GetShape() == 3)
			vision[4].replace(47 + idx, 2, "♠");
		idx += 9;
	}
	idx = 0;

	for (int i = 0; i < 2; i++) {
		if (GetGameUser()[num].GetUserCard()[i].GetNum() == 0)
			vision[2].replace(47 + idx, 2, "Ａ");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 1)
			vision[2].replace(47 + idx, 2, "２");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 2)
			vision[2].replace(47 + idx, 2, "３");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 3)
			vision[2].replace(47 + idx, 2, "４");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 4)
			vision[2].replace(47 + idx, 2, "５");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 5)
			vision[2].replace(47 + idx, 2, "６");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 6)
			vision[2].replace(47 + idx, 2, "７");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 7)
			vision[2].replace(47 + idx, 2, "８");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 8)
			vision[2].replace(47 + idx, 2, "９");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 9)
			vision[2].replace(47 + idx, 2, "10");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 10)
			vision[2].replace(47 + idx, 2, "Ｊ");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 11)
			vision[2].replace(47 + idx, 2, "Ｑ");
		else if (GetGameUser()[num].GetUserCard()[i].GetNum() == 12)
			vision[2].replace(47 + idx, 2, "Ｋ");
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
		vision[7].replace(idx, 7, str);

		string name = gameUser[i-1].GetUserName();
		vision[8].replace(idx, name.length(), name);

		string money = "$";
		money += to_string(gameUser[i - 1].GetUserMoney());
		vision[9].replace(idx, money.length(), money);
		int size = 8;
		fill(vision[9].begin() + idx + money.length(), vision[9].begin() + idx + size, ' ');
		

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

	//스텝
	int nowStep = GetNowStep();
	string str;
	if (nowStep == 1) str = "프리플랍";
	else if (nowStep == 2) str = "플랍    ";
	else if (nowStep == 3) str = "턴      ";
	else if (nowStep == 4) str = "리버    ";
	else if (nowStep == 5) str = "엔드    ";
	vision[2].replace(12, str.length(), str);

	//턴
	string nowTurn = to_string(GetNowTurn());
	vision[3].replace(14, nowTurn.length(), nowTurn);
	int step = GetNowStep();

	//남은 플레이어 수
	string remainPlayer = to_string(GetActivePlayerNum());
	vision[4].replace(20, remainPlayer.length(), remainPlayer);
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

//액션
bool Game::Betting(int player, int num) {
	if (gameUser.size() >= player) {
		int money = GetGameUser()[player - 1].GetUserMoney();
		if (num == 1) {
			gameUser[player - 1].SetAlive(false);
			if (player == 2) vision2.append("서버의 배팅 -> Fold");
			return true;
		}
		else if (num == 2) {
			money -= 100;
			gameUser[player - 1].SetUserMoney(money);
			AddTableMoney(100);
			if (player == 2) vision2.append("서버의 배팅 -> $100");
			return true;
		}
		else if (num == 3) {
			money -= 300;
			gameUser[player - 1].SetUserMoney(money);
			AddTableMoney(300);
			if (player == 2) vision2.append("서버의 배팅 -> $300");
			return true;
		}
		else if (num == 4) {
			money -= 1000;
			gameUser[player - 1].SetUserMoney(money);
			AddTableMoney(1000);
			if (player == 2) vision2.append("서버의 배팅 -> $1000");
			return true;
		}
		else return false;
	}
	else return false;
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
	tableCard.clear();

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
		gameUser[i].userCard.push_back(GetDummy());
		gameUser[i].userCard.push_back(GetDummy());
	}
}
void Game::AllocateFolpCard() {
	for (int i = 0; i < 3; i++) {
		tableCard.push_back(GetDummy());
	}
}
void Game::AllocateTurnCard() {
	tableCard.push_back(GetDummy());
}
void Game::AllocateRiverCard() {
	tableCard.push_back(GetDummy());
}

bool Game::CheckActivePlayer() {
	if (activePlayerNum == 1) return true;
	else false;
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

void Game::FindCardGrade(int num) {

	cgrade value;

	if (IsRSTF(num))
		value = ROYAL;
	else if (IsSTF(num))
		value = STF;
	else if (IsFourCard(num))
		value = FOURCARD;
	else if (IsFullHouse(num))
		value = FULLHOUSE;
	else if (IsFlush(num))
		value = FLUSH;
	else if (IsStraight(num))
		value = STRAIGHT;
	else if (IsTriple(num))
		value = TRIPLE;
	else if (IsTwoPair(num))
		value = TWOPAIR;
	else if (IsOnePair(num))
		value = ONEPAIR;
	else {
		value = TOP;
		Card temp[7];
		for (int i = 0; i < 5; i++) {
			temp[i] = tableCard[i];
		}
		for (int i = 0; i < 2; i++) {
			temp[i + 5] = GetGameUser()[num].userCard[i];
		}
		bool deck[4][13];
		for (int i = 0; i < 7; i++) {
			deck[temp[i].GetShape()][temp[i].GetNum()] = true;
		}
		for (int i = 0; i < 4; i++) {
			if (deck[i][0]) GetGameUser()[num].SetHighNum(ACE);
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 12; j > 1; j--) {
				if (deck[i][j]) GetGameUser()[num].SetHighNum((cnum)j);
			}
		}
	}
	gameUser[num].SetHighGrade(value);
}

void Game::EndGame() {
	//정산
	FindCardGrade(0);
	FindCardGrade(1);

	int winner = JudgeWinner();
	if (winner == 0) vision[29].append("클라이언트의 승리");
	else if(winner == 1) vision[29].append("서버의 승리");

	gameUser[winner].AddUserMoney(tableMoney);
	tableMoney = 0;
	//선플레이어 선정
	SetButtonPlayer(winner);
	//턴 초기화
	SetNowStep(0);
	SetNowTurn(0);
}

//조건
bool Game::IsRSTF(int num) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = gameUser[num].userCard[i];
	}
	bool deck[4][13] = { false, };
	for (int i = 0; i < 7; i++) {
		deck[temp[i].GetShape()][temp[i].GetNum()] = true;
	}
	for (int i = 3; i > 0; i--) {
		if (deck[i][0] && deck[i][12] && deck[i][11] && deck[i][10] && deck[i][9]) {
			gameUser[num].SetHighNum(ACE);
			gameUser[num].SetHighShape((cshape)i);
			return true;
		}
	}
	return false;
}
bool Game::IsSTF(int num) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = gameUser[num].userCard[i];
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
					gameUser[num].SetHighNum((cnum)v[i].at(j + 4));
					gameUser[num].SetHighShape((cshape)i);
					return true;
				}
			}
		}
	}
	return false;
}
bool Game::IsFourCard(int num) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = gameUser[num].userCard[i];
	}
	vector<int> v[13];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetNum()].push_back(temp[i].GetShape());
	}
	for (int i = 12; i > 0; i--) {
		if (v[i].size() == 4) {
			gameUser[num].SetHighNum((cnum)i);
			sort(v[i].begin(), v[i].end());
			gameUser[num].SetHighShape((cshape)v[i].back());
			return true;
		}
	}
	return false;
}
bool Game::IsFullHouse(int num) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = gameUser[num].userCard[i];
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
					gameUser[num].SetHighNum((cnum)i);
					gameUser[num].SetHighShape((cshape)v[i].back());
					return true;
				}
			}
		}
	}
	return false;
}
bool Game::IsFlush(int num) {
	Card temp[7];

	for (int i = 0; i < 5; i++) {
		temp[i] = tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = gameUser[num].userCard[i];
	}

	vector<int> v[4];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetShape()].push_back(temp[i].GetNum());
	}

	for (int i = 0; i < 4; i++) {
		if (v[i].size() >= 5) {
			sort(v[i].begin(), v[i].end());
			gameUser[num].SetHighNum((cnum)v[i].back());
			gameUser[num].SetHighShape((cshape)i);
			return true;
		}
	}
	return false;
}
bool Game::IsStraight(int num) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = gameUser[num].userCard[i];
	}
	vector<int> v[13];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetNum()].push_back(temp[i].GetShape());
	}
	for (int i = 12; i > 4; i--) {
		if (v[i].size() > 0 && v[i - 1].size() > 0 && v[i - 2].size() > 0 && v[i - 3].size() > 0 && v[i - 4].size() > 0) {
			gameUser[num].SetHighNum((cnum)i);
			sort(v[i].begin(), v[i].end());
			gameUser[num].SetHighShape((cshape)v[i].back());
			return true;
		}
	}
	return false;
}
bool Game::IsTriple(int num) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = gameUser[num].userCard[i];
	}
	vector<int> v[13];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetNum()].push_back(temp[i].GetShape());
	}
	for (int i = 12; i > 0; i--) {
		if (v[i].size() == 3) {
			gameUser[num].SetHighNum((cnum)i);
			gameUser[num].SetHighShape((cshape)v[i][2]);
			return true;
		}
	}
	return false;
}
bool Game::IsTwoPair(int num) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = gameUser[num].userCard[i];
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
			gameUser[num].SetHighNum((cnum)high);
			gameUser[num].SetHighShape((cshape)v[high][1]);
			return true;
		}
	}
	return false;
}
bool Game::IsOnePair(int num) {
	Card temp[7];
	for (int i = 0; i < 5; i++) {
		temp[i] = tableCard[i];
	}
	for (int i = 0; i < 2; i++) {
		temp[i + 5] = gameUser[num].userCard[i];
	}
	vector<int> v[13];
	for (int i = 0; i < 7; i++) {
		v[temp[i].GetNum()].push_back(temp[i].GetShape());
	}
	for (int i = 12; i > 0; i--) {
		if (v[i].size() == 2) {
			gameUser[num].SetHighNum((cnum)i);
			gameUser[num].SetHighShape((cshape)v[i][1]);
			return true;
		}
	}
	return false;
}
