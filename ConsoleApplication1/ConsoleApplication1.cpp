#include <iostream>
#include "console.h"
#include "Game.h"
#include "var.h"
#include <cstring>



char Screen[HEIGHT][WIDTH]=

{ 
"#########0#########0#########0#########0#########0#########0#########0\n"
, "#########0#########0#########0#########0#########0#########0#########0\n"
, "#########0#########0#########0#########0#########0#########0#########0\n"
, "#########0#########0#########0#########0#########0#########0#########0\n"
, "#########0#########0#########0#########0#########0#########0#########0\n"
, "#########0#########0#########0#########0#########0#########0#########0\n"
, "#########0#########0#########0#########0#########0#########0#########0\n"
, "#########0#########0#########0#########0#########0#########0#########0\n"
, "#########0#########0#########0#########0#########0#########0#########0\n"
, "#########0#########0#########0#########0#########0#########0#########0\n"
, "#########0#########0#########0#########0#########0#########0#########0\n"
};

void Draw(void);

int main()
{
	//Initial();

	//PrintLogo();
	system("mode con: cols=100 lines=35");

	Game game;
	game.tableCard.push_back(Card(TEN, DIA));
	game.tableCard.push_back(Card(NINE, DIA));
	game.tableCard.push_back(Card(KING, DIA));
	game.Update();
	game.PrintGameStatus();
	


	while (0) {
		//buttonplayer 시작
		//start
		Game game;
		//게임 초기화
		game.InitialGame();

		//프리플랍카드 핸드2
		game.AllocateHand();
		game.Betting();
		game.CheckActivePlayer(); // while에 따라 고쳐야함

		//플랍 테이블3
		game.AllocateFolpCard();
		game.Betting();
		game.CheckActivePlayer();

		//턴 테이블1
		game.AllocateTurnCard();
		game.Betting();
		game.CheckActivePlayer();

		//리버 테이블1
		game.AllocateRiverCard();
		game.Betting();
		game.CheckActivePlayer();

		//앤드
		game.EndGame();
	}
	return 0;
}

void Draw(void) {
	int i;

	for (i = 0; i < HEIGHT; i++) {
		//memset(Screen[i], ' ', WIDTH);
		//Screen[i][WIDTH - 1] = 0;
	}

	for (i = 0; i < HEIGHT; i++) {
		printf(Screen[i]);
		//MoveCursor(0, i);
	}
}


