#include "Console.h"
using namespace std;

HANDLE hConsole;




// �ܼ� ȭ�� â �ʱ�ȭ
void Initial(void) {
	CONSOLE_CURSOR_INFO Cursor;

	Cursor.bVisible = FALSE;
	Cursor.dwSize = 1;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &Cursor);
	
}

// �ܼ��� Ŀ�� ��ġ ����
void MoveCursor(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

// Ŀ������
void DeleteCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void ClearScreen(void) {
	int x, y;
	for (y = 0; y < HEIGHT; y++) {
		MoveCursor(0, y);
		for (x = 0; x < WIDTH; x++) {
			printf("%c", ' ');
		}
	}
}
