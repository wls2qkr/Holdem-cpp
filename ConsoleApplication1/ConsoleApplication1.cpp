#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <cstdio>
#include <WinSock2.h>
#include <cstring>
#include <stdlib.h>
#include "console.h"
#include "Game.h"
#include "var.h"

#define BUFSIZE 1024

Game game;

int main()
{
	system("mode con: cols=100 lines=40");

	char mode;


	while (1) {
		printf("모드를 선택하세요 1 - 클라이언트, 2 - 서버, q - 종료 : ");
		cin >> mode;

		if (mode == '1') {
			//Clinet

			WSADATA wsaData;
			SOCKET hSocket;
			SOCKADDR_IN servAddr;

			char msg[4096] = "";

			//char message[BUFSIZE] = "";
			
			bool sign = false;
			bool isButton = false;

			WSAStartup(MAKEWORD(2, 2), &wsaData);
			hSocket = socket(PF_INET, SOCK_STREAM, 0);

			memset(&servAddr, 0, sizeof(servAddr));
			servAddr.sin_family = AF_INET;
			//servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
			servAddr.sin_addr.s_addr = inet_addr("210.181.148.40");
			servAddr.sin_port = htons(5555);

			int ret = connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr));
			if (ret != 0) {
				printf("connet 실패\n");
				exit(1);
			}
			printf("connet 성공\n");

			while (1) {
				memset(msg, 0, 4096);
				string str(msg, msg + BUFSIZE);

				string cstr = "";

				if (sign) {
					str = "2";
					cout << "1 ~ 4 배팅 번호를 입력하세요.\n";
					cin >> cstr;

					
				}
				else {
					str = "1";

					cout << "이름 입력 : ";
					cin >> cstr;

					sign = true;
				}
				str = str + cstr;
				
				send(hSocket, str.c_str(), strlen(str.c_str()), 0);

				recv(hSocket, msg, 4096, 0);
				

				printf("--- 서버로 부터 전송된 메세지 --- \n");
					cout << msg << endl;

				if (cstr[0] == 'q') {
					break;
				}
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
			string playerName;
			//#Client
			int clientNum = 0;
			//#Game
			bool isBetting = false;

			bool good = false; // 클라이언트의 입력이 올바른지 판단

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

			while (strLen = recv(hClientSock, message, BUFSIZE, 0) != 0) {
				
				//메세지 [응답번호][....][....

				string str(message, message + BUFSIZE);
				string sstr;

				bool err = false;

				//cout << str << endl;

				//send(hClientSock, "잘못된 입력이거나 차례가 아닙니다.\n", 36, 0);
				 
				// 대기방 (유저등록)
				if (servStatus == 0) {
					if (message[0] == '1') {
						int size = strlen(str.substr(1, 10).c_str());
						game.AddGameUser(User(str.substr(1, size)));
						game.AddGameUser(User("Serv"));

						//send(hClientSock, "유저가 등록되었습니다.", 23, 0);

						servStatus = 1;
						game.InitialGame();

						game.AllocateHand();
						game.SetNowStep(1);
						game.Update();
						game.vision2.append("유저가 등록되었습니다.\n");
						game.vision2.append("게임을 시작합니다.\n");
						game.vision2.append("프리플랍 스테이지 핸드카드 획득.\n");
						game.vision2.append("클라이언트 배팅 턴\n");

						send(hClientSock, game.vision2.c_str(), strlen(game.vision2.c_str()), 0);
						game.UpdateInfoUserCard(1);
						game.PrintGameStatus();
					}
				}
				// 게임상태
				else if (servStatus == 1) {
					int action = message[1] - '0';

					// 플레이어 1 : 클라이언트, 플레이어 2 : 서버
					if (game.Betting(1, action)) {
						good = true;
					}
					else {
						err = true;
					}

					if (good) {

						// 서버 입력
						while (1) {
							cout << "서버의 배팅 차례 1 ~4 선택\n";
							cin >> sstr;
							if (sstr[0] - '0' >= 1 || sstr[0] - '0' < 5) {
								game.Betting(2, sstr[0] - '0');								
								break;
							}
							else cout << "잘못된 입력입니다.\n";
						}

				
						if (game.GetNowStep() == 1) {
							//플랍
							game.AllocateFolpCard();
							game.vision[29] = "플랍 스테이지 시작.\n";
							
							game.SetNowStep(2);
						}
						else if (game.GetNowStep() == 2) {
							//턴
							game.AllocateTurnCard();
							game.vision[29] = "턴 스테이지 시작.\n";
							
							game.SetNowStep(3);
						}
						else if (game.GetNowStep() == 3) {
							//리버
							game.AllocateRiverCard();
							game.vision[29] = "리버 스테이지 시작.\n";
							game.SetNowStep(4);
						}
						else if (game.GetNowStep() == 4) {
							//엔드
							game.vision[29] = "엔드 스테이지.";
							game.EndGame();
						}
						
						game.Update();
						good = false;
					}
					

					// INFO + 응답 전송
					if (err) send(hClientSock, "잘못된 입력입니다.\n", 20,0);
					else send(hClientSock, game.vision2.c_str(), strlen(game.vision2.c_str()), 0);
				}
				game.vision2.clear();
				memset(message, 0, BUFSIZE * sizeof(char));
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
	return 0;
}

