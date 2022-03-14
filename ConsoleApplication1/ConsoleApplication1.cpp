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

Game game;

int main()
{
	system("mode con: cols=100 lines=35");

	char mode;

	printf("모드를 선택하세요 1 - 클라이언트, 2 - 서버, q - 종료 : ");

	while (1) {
		cin >> mode;

		if (mode == '1') {
			//Clinet

			WSADATA wsaData;
			SOCKET hSocket;
			SOCKADDR_IN servAddr;

			char msg[BUFSIZE] = "";
			char message[BUFSIZE] = "";
			bool sign = false;
			int clientNum = 0;
			int clientStatus = 0;
			bool isButton = false;

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
				memset(message, 0, BUFSIZE * sizeof(char));
				string str(message, message + BUFSIZE);
				str[0] = clientNum;
				//char cstr[10] = "";
				string cstr = "";

				if (sign) {
					cout << "명령을 입력하세요.\n";
					cin >> cstr;
					if (clientNum == 1 && cstr[0] == '9') str[1] = '9';
					if (isButton && cstr[0] == '8') str[1] = '8';
					
				}
				else {
					//str[0] = '0';
					//str[1] = '1';
					str = "01";

					cout << "이름 입력 : ";
					cin >> cstr;

					//str = str.append(cstr);
					str = str + cstr;
					sign = true;
				}
				
				str[str.size() - 1] = '\0';

				strcpy_s(msg, str.c_str());
				int len = strlen(msg);

				send(hSocket, msg, len, 0);
				

				recv(hSocket, message, BUFSIZE, 0);

				printf("--- 서버로 부터 전송된 메세지 --- \n%s \n", message);
				clientNum = message[0] - '0';
				clientStatus = message[1] - '0';

				if(clientStatus == 1)


				//cout << "--------" << endl;
				//printf("이름을 입력하세요(5자) : ");
				//fputs("클라이언트 (q to quit) : ", stdout);

				//fgets(message, BUFSIZE, stdin);
				//cin >> message;

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
			SOCKET hClientSock[2];
			int idx = 0;
			SOCKADDR clientAddr;

			int ret;

			//#Server
			int servStatus = 0;
			int playerNum = 0;
			vector<string> playerName;
			//#Client
			int clientNum = 0;
			//#Game
			bool isBetting = false;


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
			hClientSock[idx++] = accept(hServSock, (SOCKADDR*)&clientAddr, &clientLen);

			printf("accept() 클라이언트 접속 성공\n");

			int strLen = 0;

			while ((strLen = recv(hClientSock[0], message, BUFSIZE, 0)) != 0|| (strLen = recv(hClientSock[1], message, BUFSIZE, 0)) != 0) {
				//메세지 [플레이어번호][응답번호][....][....
				printf("err\n");

				string str(message, message + BUFSIZE);
				
				cout << str << endl;

				//send(hClientSock, "잘못된 입력이거나 차례가 아닙니다.\n", 36, 0);
				//게임대기상태
				if (servStatus == 0) {
					if (message[1] == '1') {
						playerNum++;
						playerName[playerNum - 1] = str.substr(2, 10);

						string completeMessage;
						completeMessage += "등록되었습니다. 플레이어 ";
						completeMessage += to_string(playerNum);
						completeMessage += '\n';
						if (playerNum == 1) completeMessage += "1번 플레이어 -> (9 : 방닫고 현재인원 고정)";
						send(hClientSock[playerNum], completeMessage.c_str(), strlen(completeMessage.c_str()), 0);
					}
					else if (message[1] == '9') {
						send(hClientSock[0], "방을 닫습니다(인원고정 게임시작 가능상태).", 43, 0);
						send(hClientSock[1], "방을 닫습니다(인원고정 게임시작 가능상태).", 43, 0);
						
						for (int i = 0; i < playerNum; i++) {
							game.AddGameUser(User(playerName[i]));
						}
						
						servStatus = 1;

						send(hClientSock[0], str.c_str(), strlen(str.c_str()), 0);
						send(hClientSock[1], str.c_str(), strlen(str.c_str()), 0);
					}

					/*string numMessage = "00";
					numMessage +="현재 인원은 ";
					numMessage += to_string(playerNum);
					numMessage += "명 입니다. 2명 이상일시 시작가능합니다.\n";
					send(hClientSock, numMessage.c_str(), strlen(numMessage.c_str()), 0);*/

					//send(hClientSock, message, strlen(message), 0);
				}
				//게임상태
				else if (servStatus == 1) {
					int player = message[0] - '0';
					int action = message[1] - '0';
					bool bet = false;

					if (isBetting) {
						if (player == game.GetNowTurn()) {
							if (action == 1) {
								game.GetGameUser()[player].SetAlive(false);
								bet = true;
							}
							else if(action == 2) {
								game.GetGameUser()[player].AddUserMoney(-100);
								game.AddTableMoney(100);
								bet = true;
							}
							else if (action == 3) {
								game.GetGameUser()[player].AddUserMoney(-300);
								game.AddTableMoney(300);
								bet = true;
							}
							else if (action == 4) {
								game.GetGameUser()[player].AddUserMoney(-1000);
								game.AddTableMoney(1000);
								bet = true;
							}
							else {
								game.vision->append("잘못된 입력입니다.\n");
							}
							if (bet) {
								game.vision->append(to_string(player));
								game.vision->append(" 플레이어 배팅완료 \n");
								int num = (game.GetNowTurn() + 1) % game.turnIdx;
								game.SetNowTurn(num);
								if (game.GetButtonPlayer() != player)
									game.vision->append(to_string(num) + " 플레이어 배팅차례 (1~4 입력)\n");
							}
						}
						else {

						}
					}
					
						if (action == 8 && game.GetNowStep() == 0) {
							game.InitialGame();
							printf("게임초기화\n");
							game.SetNowStep(1);
							game.SetButtonPlayer(1);
							game.turnNum = game.GetActivePlayerNum();
						}
						else if (game.GetNowStep() == 1) {
							//프리플랍
							game.AllocateHand();
							game.Betting();
							game.SetNowStep(2);
						}
						else if (game.GetNowStep() == 2) {
							//플랍
							game.AllocateFolpCard();
							game.Betting();
							game.SetNowStep(3);
						}
						else if (game.GetNowStep() == 3) {
							//턴
							game.AllocateTurnCard();
							game.Betting();
							game.SetNowStep(4);
						}
						else if (game.GetNowStep() == 4) {
							//리버
							game.AllocateRiverCard();
							game.Betting();
							game.SetNowStep(5);
						}
						else if (game.GetNowStep() == 5) {
							//엔드
							game.EndGame();
						}

					

					game.Update();
					for (int i = 0; i < playerNum; i++) {
						send(hClientSock[i], game.vision->c_str(), strlen(game.vision->c_str()), 0);
					}

				}
				memset(message, 0, 1024);

			}

			printf("서버가 종료되었습니다. \n");

			closesocket(hClientSock[0]);
			closesocket(hClientSock[1]);
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

