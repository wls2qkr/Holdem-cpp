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

void Print(string s[]) {
	for (int i = 0; i < 100; i++) {
		cout << s[i];
	}
}

int main()
{
	//Initial();

	//PrintLogo();
	system("mode con: cols=100 lines=50");

	Game game;
	game.tableCard.push_back(Card(TEN, DIA));
	game.tableCard.push_back(Card(NINE, DIA));
	game.tableCard.push_back(Card(KING, DIA));
	game.Update();
	Print(game.vision);
	


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

//#define BLACK 0 
//#define BLUE 1 
//#define GREEN 2 
//#define CYAN 3 
//#define RED 4 
//#define MAGENTA 5 
//#define BROWN 6 
//#define LIGHTGRAY 7 
//#define DARKGRAY 8 
//#define LIGHTBLUE 9 
//#define LIGHTGREEN 10 
//#define LIGHTCYAN 11 
//#define LIGHTRED 12 
//#define LIGHTMAGENTA 13 
//#define YELLOW 14 
//#define WHITE 15
//
//void textcolor(int foreground, int background)
//{
//	int color = foreground + background * 16;
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
//}