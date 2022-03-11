#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <WinSock2.h>
#include <cstring>
#include <stdlib.h>
#include "console.h"
#include "Game.h"
#include "var.h"

#define BUFSIZE 1024

int main()
{
	system("mode con: cols=100 lines=35");

	char mode;
	int clientStatus = 0;

	printf("모드를 선택하세요 1 - 클라이언트, 2 - 서버, q - 종료 : ");

	while (1) {
		cin >> mode;

		if (mode == '1') {
			//Clinet

			WSADATA wsaData;
			SOCKET hSocket;
			SOCKADDR_IN servAddr;

			char message[BUFSIZE] = "";

			WSAStartup(MAKEWORD(2, 2), &wsaData);
			hSocket = socket(PF_INET, SOCK_STREAM, 0);

			memset(&servAddr, 0, sizeof(servAddr));
			servAddr.sin_family = AF_INET;
			//servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
			servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
			servAddr.sin_port = htons(5555);

			int ret = connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr));
			if (ret != 0) {
				printf("connet 실패\n");
				exit(1);
			}
			printf("connet 성공\n");

			while (1) {
				memset(message, 0, BUFSIZE*sizeof(char));


				message[0] = '1';
				char str[11];
				printf("이름을 입력하세요(5자) : ");
				fputs("클라이언트 (q to quit) : ", stdout);

				printf("메세지 : %s", message);
				//fgets(message, BUFSIZE, stdin);
				cin >> message;

				if (!strcmp(message, "q\n")) {
					break;
				}

				//전송
				int strLen = send(hSocket, message, strlen(message), 0);

				printf("전송\n");

				//받기
				strLen = recv(hSocket, message, BUFSIZE, 0);

				printf("받기\n");

				message[strLen] = 0;
				printf("서버로 부터 전송된 메세지 : %s \n", message);

			}
			printf("연결이 종료되었습니다. \n");
			closesocket(hSocket);
			WSACleanup();
		}
		else if (mode == '2') {
			//Server

			WSADATA wsaData;
			SOCKET hServSock;
			SOCKADDR_IN servAddr;

			char message[BUFSIZE] = "";

			int clientLen;
			SOCKET hClientSock;
			SOCKADDR clientAddr;

			int ret;

			//#Server
			int servStatus = 0;
			int playerNum = 0;
			vector<string> playerName;
			//#Client
			int clientNum = 0;


			WSAStartup(MAKEWORD(2, 2), &wsaData);
			
			hServSock = socket(PF_INET, SOCK_STREAM, 0);
			printf("socket() 소켓 생성 성공\n");

			servAddr.sin_family = AF_INET;
			servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
			servAddr.sin_port = htons(5555);

			ret = bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
			if (ret != 0) {
				printf("bind error");
				exit(1);
			}
			printf("bind() 성공\n");

			ret = listen(hServSock, 5);
			if (ret != 0) {
				printf("listen error");
				exit(1);
			}
			printf("listen() 성공\n");

			clientLen = sizeof(clientAddr);
			hClientSock = accept(hServSock, (SOCKADDR*)&clientAddr, &clientLen);

			printf("accept() 클라이언트 접속 성공\n");

			int strLen = 0;

			while ((strLen = recv(hClientSock, message, BUFSIZE, 0)) != 0) {
				//메세지 [플레이어번호][응답번호][....][....
				string str(message, message + BUFSIZE);
				
				if (servStatus == 0) {
					if (message[0] == '1') {
						playerNum++;
						playerName[playerNum - 1] = str.substr(2, 10);
					}

					string numMessage = "00";
					numMessage +="현재 인원은 ";
					numMessage += to_string(playerNum);
					numMessage += "명 입니다. 2명 이상일시 시작가능합니다.\n";
					send(hClientSock, numMessage.c_str(), strlen(message), 0);

					string completeMessage = to_string(playerNum);
					completeMessage += '0';
					completeMessage += "등록되었습니다. 플레이어 ";
					completeMessage += to_string(playerNum);
					completeMessage += '\n';

					send(hClientSock, message, strlen(message), 0);
				}
				else if (servStatus == 1) {
					send(hClientSock, "게임을 시작합니다.", 19, 0);
					Game game;
					for (int i = 0; i < playerNum; i++) {
						game.AddGameUser(User(playerName[i]));
					}
					game.InitialGame();



				}
				memset(message, 0, 1024);

			}

			printf("서버가 종료되었습니다. \n");
			closesocket(hClientSock);
			WSACleanup();

		}
		else if (mode == 'q') {
			return 0;
		}
		else {
			printf("다시 입력하세요.\n");
		}
	}


	//Game game;
	//game.tableCard.push_back(Card(TEN, DIA));
	//game.tableCard.push_back(Card(NINE, DIA));
	//game.tableCard.push_back(Card(KING, DIA));
	//game.Update();
	//game.PrintGameStatus();
	//


	//while (0) {
	//	//buttonplayer 시작
	//	//start
	//	Game game;
	//	//게임 초기화
	//	game.InitialGame();

	//	//프리플랍카드 핸드2
	//	game.AllocateHand();
	//	game.Betting();
	//	game.CheckActivePlayer(); // while에 따라 고쳐야함

	//	//플랍 테이블3
	//	game.AllocateFolpCard();
	//	game.Betting();
	//	game.CheckActivePlayer();

	//	//턴 테이블1
	//	game.AllocateTurnCard();
	//	game.Betting();
	//	game.CheckActivePlayer();

	//	//리버 테이블1
	//	game.AllocateRiverCard();
	//	game.Betting();
	//	game.CheckActivePlayer();

	//	//앤드
	//	game.EndGame();
	//}

	
	return 0;
}

