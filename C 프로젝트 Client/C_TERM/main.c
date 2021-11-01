#define _CRT_SECURE_NO_WARNINGS //strcpy때문에
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "def.h"
#include "struct.h"
#include "function.h"
#include <fmod.h>
#include "fmod_set.h"

////////////////// 서버 사용 함수 ////////////////////
#pragma comment (lib,"ws2_32.lib")

//클라꺼
#define BUFSIZE 1024
#define SIZE 25

////////////////////////// 함수 및 전역변수 정의 //////////////////////////

////////////////////////// 초기화 함수 ////////////////////////////////
void Zone_init(zone_head* ZONE, int bal);						// 지역 초기화
void player_init(int num, int money, player* user, zone_head* ZONE);// 플레이어 초기화
void golden_key_init(golden_key_head* G_KEY,int bal);			// 황금열쇠 초기화
void dice_init(int* dice1, int* dice2);					// 주사위 초기화

///////////////////////// 지역관련함수 //////////////////////////////
void insertZone(zone_head* Z, char* name, int num, int Y, int X, int Z_cost, int H_cost, int B_cost, int V_cost, int Z_toll, int H_toll, int B_toll, int V_toll,char color);	// 지역노드삽입
zone_list* GetZone(void);					// 메모리할당
zone_head* createZoneList(void);			// 지역연결리스트생성
void free_zone(zone_head* Z);				// 메모리할당해제
void BUY_ZONE(zone_list* Z, int turn); //땅 구매
int SELL_LIST(int PLAYER, zone_head* ZONE); //땅 판매
void STRUCTURE_DRAW(zone_list* Z, int S, int turn); //건물 생성
int check_line(gray_num, white_num, sky_num, blue_num, violet_num, purple_num, lred_num, red_num); //라인 독점 확인

///////////////////////// 황금열쇠 관련함수 /////////////////////////////
void insertKey(golden_key_head* G, int num, char* name, char* content);		// 황금열쇠 노드삽입
void take_golden_key(golden_key_head* G_KEY, int num);						// 맨 윗장 카드 열기
void show_golden_key(golden_key* G);
void free_key(golden_key_head* G);											// 메모리할당해제
golden_key* GetGoldenKey(void);												// 메모리할당
golden_key_head* createGoldenList(void);									// 황금열쇠연결리스트생성


///////////////////////// 주사위관련함수 ///////////////////////////////				
void casting_dice(int* dice1, int* dice2, int* dice_sum, int* OE_KEY, int* OE, int use); //주사위 굴리기
void print_dice_num(int x, int y, int dice_num);							//주사위 눈 출력
void print_dice(int dice1, int dice2);										// 주사위결과출력
int dice_rand(void);														// 주사위 굴리는 화면
int mini(void);														        //미니게임 주사위


//////////////////////// 말이동관련함수 /////////////////////////////////
void move_player(player* user, player* player, int turn, int user_set,int bal); //말 이동 함수				//주사위 합에 의한 말의 이동
void MOVING_init(player* player, int turn);								//임의의 말의 이동


//////////////////////// 화면 갱신 관련 함수 ////////////////////////////
void game_size();
void info_size();
void intro_size();

int draw_intro(int state);								// 인트로 출력
void draw_map(void);									// 보드 출력
int infor(void);									// 게임 정보 출력
void setMapcolor(int i);							// 지역 컬러 출력

void MONEY_SHOW(player* player, int user_set); // 보유머니 , 보유 아이템 출력

void island_CLR(void); // 무인도 문구 CLR
void gk_CLR(void); //황금 열쇠 문구 CLR

void ZONE_LIST_SHOW(zone_head* ZONE); //지역 리스트 출력
void ZONE_LIST_SHOW_CLR(void); //지역 리스트 문구 CLR

void SELL_LIST_CLR(void); // 판매 지역 리스트 문구 CLR
void zone_NAME_CLR(zone_list* Z); //지역 이름 문구 CLR
void MENU_CLR(void); //메뉴 문구 CLR
void DICE_CLR(void); //주사위 문구 CLR

enum state {
	INTRO,
	INIT,
	INFO,
	EXIT_GAME,
	P_TURN,
	NEXT_TURN,
	IN_ISLAND,
	re_map,
	GOLDEN_KEY,
	ISLAND,
	BEH_MASTERLESS,
	BEH_NOTMINE,
	BEH_MINE,
	NOT_ENOUGH_MONEY,
	ENOUGH_MONEY,
	BEH,
	SELL_ZONE,
	SPACESHIP,
	MINI_GAME,
	KEY1, KEY2, KEY3, KEY4, KEY5, KEY6, KEY7, KEY8, KEY9, KEY10, KEY11, KEY12, KEY13, KEY14, KEY15, KEY16, KEY17, KEY18, KEY19, KEY20, KEY21, KEY22, KEY23, KEY24,
	FREE,
	GAME_OVER
}STATE;
enum state STATE;
enum state PRE_STATE;
enum state KEY_STATE;

//전역변수
int welfare = 0;
int color = 0;	
int dice1 = 0, dice2 = 0, dice_sum = 0;
int sum=0; //KEY 20번 
int g_cnt = 0;

golden_key_head* createGoldenList(void);	// 황금열쇠연결리스트생성

zone_head* ZONE;

golden_key_head* G_KEY;

void voidBuffer(SOCKET s) {
	u_long tmpl, i;
	char tmpc;
	ioctlsocket(s, FIONREAD, &tmpl);
	for (i = 0; i < tmpl; i++) recv(s, &tmpc, sizeof(char), 0);
}

void player_init(int num, int bal, player* user, zone_head* ZONE) {
	for (int i = 0; i < num; i++) {
		(user + i)->pre_X = 4; //출발 x좌표
		(user + i)->pre_Y = 44; //출발 y좌표
		(user + i)->location = ZONE->head;
		(user + i)->money = bal;
		(user + i)->escape = 0;
		(user + i)->island_index = 0;
		(user + i)->spaceship = 0;
		(user + i)->passcard = 0;
		(user + i)->gameover = 0;
		(user + i)->OE = 0;
		MOVING_init(user + i, i + 1);
	}
}
void move_player(player* user,player* player, int turn, int user_set, int bal) {
	player->pre_X = player->location->zone_X;
	player->pre_Y = player->location->zone_Y;
	for (int i = 0; i < dice_sum; i++) {
			player->pre_X = player->location->zone_X;
		player->pre_Y = player->location->zone_Y;
		player->location = player->location->F_link; //플레이어의 위치를 앞으로 옮긴다.
		MOVING_init(player, turn); //플레이어 말 정렬
		
		if (player->location -> zone_name=="출발"){
			gotoxy(44, 19);
			player->money += bal / 10;
			Violet1;
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &channel[1]); // 반환점
			printf("한 바퀴를 돌았습니다. 월급 %d만원을 지급합니다.", bal / 10);
			White1;
		}
		Sleep(150);
	}
	//MOVING_init(player, turn);
	MONEY_SHOW(user, user_set);
	if (turn == P2_TURN) {
		gotoxy(57, 21);
		printf("ENTER를 입력해주세요.");
		while (_getch() != ENTER);
		gotoxy(57, 21); //ENTER를 입력해주세요 CLR
		printf("                                      ");
	}
	gotoxy(44, 19); printf("                                                "); //한바퀴 CLR
	gotoxy(57, 21); printf("                                      ");  //ENTER를 입력해주세요 CLR
	gotoxy(50, 33); printf("                                      "); //주사위 굴린 결과입니다 CLR
}


void main() 
{
	// 커서 지우기
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	SOCKET cs;			
	WSADATA wsaData;
	SOCKADDR_IN sin;

	char sAddr[15];
	int sPort = 0;

	if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0) {
		printf("WSAStartup 실패, 에러코드 : %d\n", WSAGetLastError());
		return 0;
	}

	cs = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (cs == INVALID_SOCKET) {
		printf("소켓 생성 실패, 에러코드 : %d\n", WSAGetLastError());
		WSACleanup(); return 0;
	}

	/*  //서버 연결관련 부분
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(5001);
	*/

	system("mode con cols=45 lines=7 | title 부르마블 Client");
	printf("\n\n　　　   서버 IP Addr : ");
	scanf("%s", sAddr);
	fflush(stdin);
	printf("　　　　　  서버 Port : ");
	scanf("%d", &sPort);
	fflush(stdin);

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(sAddr);
	sin.sin_port = htons(sPort);

	if (connect(cs, (SOCKADDR*)&sin, sizeof(sin)) != 0)
	{
		system("mode con cols=70 lines=15 | title 브루마블 Client");
		system("cls");
		printf("접속 실패, 서버의 상태를 확인해주세요.\n에러코드 : %d\n\n", WSAGetLastError());
		closesocket(cs); WSACleanup();
		return 0;
	}

	zone_head* ZONE = createZoneList();	//zonelist 생성

	golden_key_head* G_KEY = createGoldenList(); //goldenlist 생성

	int i = 0, user_set = 0;												//인덱스
	int TURN = P1_TURN;														//턴
	char SEL_BEH = 0;														//메뉴에서 행동선택
	char Zone_NUM[3] = { 0, };												//메뉴에서 번호선택
	int SUM_TOLL = 0;														//통행료
	int SUM_VAL = 0;														//땅값
	int SELL_MONEY = 0;														//매각
	int key_flag = NULL;													//황금열쇠
	int input_zone = 0;														//매각시 선택지역
	int max = 0, bal = 0;													//황금열쇠 반액대매출
	int fine = 0;															//방범비,수리비,소득세
	int gameover_cnt = 0;
	int OE_KEY = 0;															//홀짝 사용
	int use=0;		
	int sel_OE = 0;															//홀짝 사용 유무
	int sel_g = 0;															//홀짝 게임 유무
	int result = 0;
	int prize = 0;															//홀짝게임 상금
	int COLOR_WIN = NULL;										//컬러독점 승리
	int LINE_WIN = NULL;										//라인독점 승리
	int sel = 0;												//땅 구입 선택
	srand((unsigned int)time(NULL));
	int intro_status;

	int check = 0; //라인 독점, 트리플 독점 관련

	int pick = 0; //황금열쇠 뽑기

	int pas=0; //ENTER_Buf

	zone_list* tmp_zone; //현재 장소 저장
	zone_list* max_zone; //가장 비싼 땅 판매할때 사용

	player* user = NULL;	//유저 수
	player* stat = NULL;	//유저 상태

	char message[BUFSIZE];
	int recvByte=0;
		
	char user_buf[BUFSIZE + 1];			//서버에서 인원수 배정 받을 때 쓰이는 함수
	char bal_buf[BUFSIZE + 1];			//서버에서 게임머니 배정 받을 때 쓰이는 함수
	char STATE_buf[BUFSIZE + 1]; //STATE 주고 받을때
	char tmp_buf[BUFSIZE + 1]; //값 주고 받을때

	char selOE_buf[BUFSIZE + 1]; //값 주고 받을때
	char OEKEY_buf[BUFSIZE + 1]; //값 주고 받을때

	char zone_buf[BUFSIZE + 1]; //값 주고 받을때

	char res_buf[BUFSIZE + 1]; //값 주고 받을때

	char sel_buf[BUFSIZE + 1]; //값 주고 받을때

	char ENTER_buf[BUFSIZE + 1]; //값 주고 받을때

	char dice1_buf[BUFSIZE + 1]; //dice1값 주고 받을때
	char dice2_buf[BUFSIZE + 1]; //dice2값 주고 받을때

	char sel_p_buf[BUFSIZE + 1]; //값 주고 받을때

	char key_buf[BUFSIZE + 1]; //값 주고 받을때

	char use_buf[BUFSIZE + 1]; //홀짝 값 주고 받을때

	char sel_g_buf[BUFSIZE + 1]; //미니게임 한번 더 값 주고 받을때

	char result_buf[BUFSIZE + 1]; //미니게임 주사위 값

	char win_buf[BUFSIZE + 1]; //이긴 결과 값

	char res; //예비

	STATE = INTRO;

	int nRcv = 0;

	while (1)
	{
		switch (STATE)
		{
			case INTRO:
			{
				fmod_Init();
				FMOD_Channel_Stop(channel[0]);
				FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[8], 0, &channel[0]);
				system("mode con cols=50 lines=7 | title 부르마블 Client");
				printf("\n\n");
				printf("　　　　　서버가 현재 게임을 설정중입니다.\n");
				printf("　　　　　　　　　Please wait.....\n");

				//----------------------------------------------------------------------------------------------------------------
				recv(cs, user_buf, strlen(user_buf), 0);		// 서버에서 클라이언트로 게임 인원수 user_set 부분을 받는다.
				user_set = atoi(user_buf);

				recv(cs, bal_buf, strlen(bal_buf), 0);			// 서버에서 클라이언트로 게임 머니수 bal 부분을 받는다.
				bal = atoi(bal_buf);

				//----------------------------------------------------------------------------------------------------------------

				system("cls");
				if (bal >= 1000)
				{
					printf("\n");
					printf("　　┌───★ 게임 설정이 완료되었습니다.★───┐\n", user_set);
					printf("　　│        설정된 플레이어의 수 : %d      │\n", user_set);
					printf("　　│      설정된 게임 시작 금액: %d     │\n", bal);
					printf("　　│         Enter키를 눌러주세요.        │\n");
					printf("　　└──────────────────────────────────────┘\n");

					recv(cs, message, 1024, 0);

					if (_getch() == ENTER) {
						STATE = INIT;
						system("cls");
						printf("게임 시작!!");
					}

				}
				else if (bal < 1000 && bal >= 500)
				{
					printf("\n");
					printf("　　┌───★ 게임 설정이 완료되었습니다.★───┐\n", user_set);
					printf("　　│        설정된 플레이어의 수 : %d      │\n", user_set);
					printf("　　│      설정된 게임 시작 금액: %d      │\n", bal);
					printf("　　│         Enter키를 눌러주세요.        │\n");
					printf("　　└──────────────────────────────────────┘\n");

					recv(cs, message, 1024, 0);

					if (_getch() == ENTER) {
						STATE = INIT;
						system("cls");
						printf("게임 시작!!");
						break;
					}
				}

			}
			case INIT:
			{
				
				FMOD_Channel_Stop(channel[0]);
				FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &channel[0]); // BGM
				rewind(stdin);
				gameover_cnt = user_set;

				info_size();
				system("cls");

				TURN = P1_TURN;				//플레이어턴 설정??
				dice_init(&dice1, &dice2);

				White1;// │ 추가시 제거

				Zone_init(ZONE, bal);
				game_size();
				golden_key_init(G_KEY, bal);
				draw_map();
				user = (player*)malloc(sizeof(player) * (user_set));
				player_init(user_set, bal, user, ZONE);
				MONEY_SHOW(user, user_set);

				

				Red1;
				gotoxy(23, 30); printf("                       　　　　　　　   ");
				gotoxy(23, 30); printf("플레이어%d의 차례입니다.", TURN);
				
				nRcv = recv(cs, res_buf, sizeof(res_buf) - 1, 0);
				if (nRcv == -1) {
					printf("값을 받지 못하였습니다.");
					_getch();
					system("cls");
					return;
				}
				res_buf[nRcv] = '\0';
				res = atoi(res_buf);
				while (res != ENTER);
				
				gotoxy(23, 30); printf("                  　　　　　　　      ");						//플레이어%d의 차례입니다. CLR
				STATE = P_TURN;
				//gotoxy(50, 50); printf("%d", STATE);				//값 확인용 출력
				break;
			}
			case INFO:
			{
				system("mode con cols=100 lines=33 | title 부르마불 Client");
				if (infor() == ESC)
					STATE = INTRO;
				else
					STATE = INFO;
				break;
			}
			case P_TURN:
			{
				use = 0;
				stat = user + TURN - 1;

				ZONE_LIST_SHOW_CLR();
				SELL_LIST_CLR();
				ZONE_LIST_SHOW(ZONE);

				if (TURN == P1_TURN) {
					//클라 우주1
					if (stat->spaceship == EXIST) {
						STATE = SPACESHIP;
						break;
					}
					//클라 홀짝1
					if (stat->location->zone_name != "무인도") {
						if (stat->OE == EXIST) {
							nRcv = recv(cs, selOE_buf, sizeof(selOE_buf) - 1, 0);
							if (nRcv == -1) {
								printf("값을 받지 못하였습니다.");
								_getch();
								system("cls");
								return;
							}
							selOE_buf[nRcv] = '\0';
							sel_OE = atoi(selOE_buf);


							gotoxy(45, 24);	printf("                                                     ");
							if (sel_OE == 50) {
								gotoxy(48, 24);	printf("                                                  ");
								sel_OE = 0;
							}
							else {
								gotoxy(48, 24);	printf("                                                  ");
								gotoxy(48, 24); printf("주사위 홀짝권을 사용했습니다");
								stat->OE = NON_EXIST;
							}
						}
					}
					//클라 주사위1
					nRcv = recv(cs, dice1_buf, sizeof(dice1_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					dice1_buf[nRcv] = '\0';
					dice1 = atoi(dice1_buf);
			
					nRcv = recv(cs, dice2_buf, sizeof(dice2_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					dice2_buf[nRcv] = '\0';
					dice2 = atoi(dice2_buf);
					dice_sum = dice1 + dice2;
	
					if (stat->location->zone_name == "무인도") {
						Green1;
						gotoxy(48, 17);
						printf("현재 당신은 무인도에서 표류중입니다.");
						White1;

						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);

						STATE = IN_ISLAND;
					}
					else {
						STATE = re_map;
						move_player(user, stat, TURN, user_set, bal);

					}	
					gotoxy(48, 33);
					printf("                                        "); //굴린 결과입니다 CLR
					break;
				}
				else {
					if (stat->spaceship == EXIST)
					{
						STATE = SPACESHIP;
						break;
					}
					if (stat->location->zone_name != "무인도") {
						if (stat->OE == EXIST) {
							White1;
							gotoxy(45, 24);	printf("주사위 홀짝권을 사용하시겠습니까?. 사용:1/미사용:2");
							do
								sel_OE = _getch();
							while (sel_OE != 49 && sel_OE != 50);

							//홀짝1
							_itoa(sel_OE, selOE_buf, 10);
							send(cs, selOE_buf, strlen(selOE_buf), 0);

							gotoxy(45, 24);	printf("                                                     ");
							if (sel_OE == 49) {
								use = 1;
								gotoxy(50, 24);	printf("                                                  ");
								gotoxy(50, 24); printf("주사위 홀짝권을 사용했습니다");
								gotoxy(50, 25);	printf("홀 짝을 정해주세요. 홀:1/짝:2");
								do
									sel_OE = _getch();
								while (sel_OE != 49 && sel_OE != 50);
								//안보내는 이유 : dice값이 어차피 홀 / 짝 나눠져서 나오기때문에 상대편에서 받을 필요 없음
								OE_KEY = sel_OE;
							}
						}
					}

					gotoxy(48, 21);
					printf("ENTER키를 입력하여 주사위를 멈춰주세요");
					while (1) {
						if (_kbhit()) {
							if (_getch() == ENTER)
								break;
						}
						else {
							DICE_CLR();
							print_dice(dice_rand(), dice_rand());
							Sleep(100);
						}
					}
					
					gotoxy(48, 21); //"ENTER키를 입력하여 주사위를 멈춰주세요 CLR
					printf("                                        ");
					casting_dice(&dice1, &dice2, &dice_sum, &OE_KEY, &stat->OE, use);
					FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &channel[1]); // 주사위
					_itoa(dice1, dice1_buf, 10);
					_itoa(dice2, dice2_buf, 10);

					send(cs, dice1_buf, strlen(dice1_buf), 0);
					send(cs, dice2_buf, strlen(dice2_buf), 0);

					Gold1; //P2_TURN

					gotoxy(48, 33);
					printf("플레이어%d의 주사위를 굴린 결과입니다.", TURN);
					White1;

					if (stat->location->zone_name == "무인도") {
						Green1;
						gotoxy(48, 17);
						printf("현재 당신은 무인도에서 표류중입니다.");
						White1;
						gotoxy(57, 20);	printf("ENTER를 입력하세요.");
						while ((pas = _getch()) != ENTER);

						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);

						STATE = IN_ISLAND;		
					}
					else {
						STATE = re_map;
						move_player(user, stat, TURN, user_set, bal);
					}
					gotoxy(48, 33);
					printf("                                        "); //굴린 결과입니다 CLR
				}	
				break;
			}
			case MINI_GAME: 
			{
				result = 0;
				if (TURN == P2_TURN) {
					gotoxy(61, 16); printf(" 1.홀 / 2.짝");
					gotoxy(43, 17); printf("랜덤으로 돌아가는 주사위의 홀 짝을 맞추시면 됩니다.");
					do
						use = _getch();
					while (use != 49 && use != 50);

					_itoa(use, use_buf, 10);
					send(cs, use_buf, strlen(use_buf), 0);

					gotoxy(43, 17); printf("                                                    ");
					gotoxy(52, 17); printf("ENTER를 눌러 결과를 확인하세요!");
				}
				else {
					gotoxy(52, 17); printf("플레이어 %d이 선택중입니다.", TURN);

					nRcv = recv(cs, use_buf, sizeof(use_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					use_buf[nRcv] = '\0';
					use = atoi(use_buf);

				}
				if (TURN == P2_TURN) {
					while (1) {
						if (_kbhit()) {
							if ((pas = _getch()) == ENTER) {
								_itoa(result, result_buf, 10);
								send(cs, result_buf, strlen(result_buf), 0);
								break;
							}
						}
						else {
							DICE_CLR();
							print_dice(dice_rand(), dice_rand());
							Sleep(100);
							result = mini();
						}
					}
				}
				else {
					nRcv = recv(cs, result_buf, sizeof(result_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					result_buf[nRcv] = '\0';
					result = atoi(result_buf);
				}
				if (use%2 == result % 2) {
					prize *= 2;
					gotoxy(61, 16); printf("                    ");
					gotoxy(52, 17); printf("                                  ");
					gotoxy(48, 16);printf("이겼습니다! 현재 상금은 %d만원 입니다.", prize);
					g_cnt++;
					if (g_cnt == 3) {
						DICE_CLR();
						gotoxy(48, 16); printf("                                          ");
						gotoxy(48, 16); printf("축하합니다! 홀짝게임을 승리하여 종료합니다.");
						if (TURN == P2_TURN) {
							gotoxy(48, 27);	printf("ENTER를 입력하세요.");
							while ((pas = _getch()) != ENTER);

							_itoa(pas, ENTER_buf, 10);
							send(cs, ENTER_buf, strlen(ENTER_buf), 0);
						}
						else {
							nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
							if (nRcv == -1) {
								printf("값을 받지 못하였습니다.");
								_getch();
								system("cls");
								return;
							}
							ENTER_buf[nRcv] = '\0';
							pas = atoi(ENTER_buf);
							while (pas != ENTER);
						}
						stat->money += prize;
						gotoxy(48, 16);
						printf("                             ");
						STATE = NEXT_TURN;
						break;
					}
					gotoxy(48, 18); printf("이어서 하시겠습니까? 한다:1/안한다:2");
					if (TURN == P2_TURN) {
						do
							sel_g = _getch();
						while (sel_g != 49 && sel_g != 50);

						_itoa(sel_g, sel_g_buf, 10);
						send(cs, sel_g_buf, strlen(sel_g_buf), 0);
					}
					else {
						nRcv = recv(cs, sel_g_buf, sizeof(sel_g_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						sel_g_buf[nRcv] = '\0';
						sel_g = atoi(sel_g_buf);

						while (sel_g != 49 && sel_g != 50);
					}
					DICE_CLR();
					gotoxy(48, 16); printf("                                       ");
					gotoxy(48, 18); printf("                                    ");

					if (sel_g == 49) {
						STATE = MINI_GAME;
					}
					else {
						gotoxy(48, 17);
						printf("상금 %d만원을 획득하셨습니다.", prize);
						if (TURN == P2_TURN) {
							gotoxy(48, 27);	printf("ENTER를 입력하세요.");
							while ((pas = _getch()) != ENTER);

							_itoa(pas, ENTER_buf, 10);
							send(cs, ENTER_buf, strlen(ENTER_buf), 0);
						}
						else {
							nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
							if (nRcv == -1) {
								printf("값을 받지 못하였습니다.");
								_getch();
								system("cls");
								return;
							}
							ENTER_buf[nRcv] = '\0';
							pas = atoi(ENTER_buf);
							while (pas != ENTER);
						}
						stat->money += prize;
						gotoxy(48, 17); printf("                                 ");
						gotoxy(48, 27);	printf("                       ");
						STATE = NEXT_TURN;
						break;
					}
				}
				else {
					gotoxy(61, 16); printf("               ");
					gotoxy(48, 16); printf("                                      ");
					gotoxy(52, 17); printf("                                                      ");
					gotoxy(62, 21); printf("졌습니다!");
					if (TURN == P2_TURN) {
						gotoxy(57, 30);	printf("ENTER를 입력하세요.");
						while ((pas = _getch()) != ENTER);

						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);
					}
					else {
						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);
					}
					DICE_CLR();
					STATE = NEXT_TURN;
				}
				gotoxy(48, 17);
				printf("                              ");
				break;
			}
			case re_map:
			{
				gotoxy(48, 20);	printf("                                      ");
				gotoxy(57, 19); printf("                           "); //무인도 탈출 초기화
				island_CLR(); //무인도 초기화
				DICE_CLR();
				MENU_CLR();
				gotoxy(55, 20);
				if (TURN == P1_TURN) {
					Red1;

					printf("%s 칸에 도착하였습니다.", stat->location->zone_name);
					gotoxy(48, 22);
					printf("현재 플레이어%d의 소지금 : %d 만원 입니다.", TURN, stat->money);

					White1;
					if (stat->location->zone_name == "출발") {
						gotoxy(45, 18);
						stat->money += bal / 5;
						Violet1;
						FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &channel[1]); // 반환점
						printf("한 바퀴를 돌았습니다. 월급 %d만원을 지급합니다.", bal / 5);
						White1;

						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);

						STATE = NEXT_TURN;
					}
					else if (stat->location->zone_name == "황금열쇠") {
						STATE = GOLDEN_KEY;
					}
					else if (stat->location->zone_name == "무인도") {
						STATE = ISLAND;
					}
					else if (stat->location->zone_name == "우주여행") {
						Green1;
						FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &channel[1]); // 우주선
						gotoxy(48, 24);	printf("플레이어 %d은 우주여행에 초대받았습니다.", TURN);
						gotoxy(48, 25);	printf("다음 턴에 원하는 장소로 이동할 수 있습니다.");
						White1;

						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);

						MENU_CLR();

						if (stat->money < bal / 10) {
							gotoxy(48, 24);	printf("보유금액이 부족합니다.");
							gotoxy(48, 25);	printf("다음 턴으로 넘어갑니다.");
						}
						else
						{
							stat->money -= bal / 10;
							gotoxy(stat->location->zone_X + (3 * TURN - 4), stat->location->zone_Y);
							printf("  ");
							if (TURN == P1_TURN)
							{
								gotoxy(138, 3);
								Red1;
								printf("①");
								White1;
							}
							else if (TURN == P2_TURN)
							{
								gotoxy(140, 3);
								Gold1;
								printf("②");
								White1;
							}

							Green1;
							gotoxy(48, 24);	printf("%d만원을 지불하였습니다.", bal / 10);
							gotoxy(48, 25);	printf("우주정거장으로 이동하였습니다.");
							gotoxy(48, 26);	printf("다음 턴에 원하는 장소로 이동합니다.");
							MONEY_SHOW(user, user_set);
							stat->spaceship = EXIST;
						}

						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);

						STATE = NEXT_TURN;
					}
					else if (stat->location->zone_name == "홀짝게임") {
						gotoxy(48, 24);	printf("플레이어 %d은 홀짝게임에 초대받았습니다.",TURN);
						gotoxy(48, 25);	printf("홀짝게임 주인에게 %d만원을 지불하시오.", bal / 10);

						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);

						White1;
						MENU_CLR();
						if (stat->money < bal / 10) {
							gotoxy(48, 24);	printf("보유금액이 부족합니다.");
							gotoxy(48, 25);	printf("다음 턴으로 넘어갑니다.");

							nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
							if (nRcv == -1) {
								printf("값을 받지 못하였습니다.");
								_getch();
								system("cls");
								return;
							}
							ENTER_buf[nRcv] = '\0';
							pas = atoi(ENTER_buf);
							while (pas != ENTER);

							STATE = NEXT_TURN;
						}
						else {
							Green1;
							gotoxy(40, 24);
							printf("홀짝 게임을 할 수 있습니다. 한다:1/안한다:2 (비용 : %d만원)", bal / 10);
							White1;

							nRcv = recv(cs, sel_g_buf, sizeof(sel_g_buf) - 1, 0);
							if (nRcv == -1) {
								printf("값을 받지 못하였습니다.");
								_getch();
								system("cls");
								return;
							}
							sel_g_buf[nRcv] = '\0';
							sel_g = atoi(sel_g_buf);

							while (sel_g != 49 && sel_g != 50);

							gotoxy(48, 22); printf("                                                 ");//도착하였습니다 초기화
							gotoxy(55, 20); printf("                                  ");//소지금 출력 초기화
							if (sel_g == 49) {
								stat->money -= (bal / 10);
								prize = bal / 10;
								gotoxy(40, 24);
								printf("                                                              ");
								STATE = MINI_GAME;
							}
							else {
								gotoxy(40, 24);
								printf("                                                               ");
								STATE = NEXT_TURN;
							}
						}
						break;
					}
					else {
						if (stat->location->owner == NULL) {
							STATE = BEH_MASTERLESS;
							//gotoxy(50, 50); printf("                             　　　　　　　　　　　　　　");
							//gotoxy(50, 50); printf("받은 STATE 값 %d  받은 STATE_buf 값 %d", STATE, atoi(STATE_buf));
						}
						else if (stat->location->owner == TURN) {
							STATE = BEH_MINE;
							//gotoxy(50, 50); printf("                             　　　　　　　　　　　　　　");
							//gotoxy(50, 50); printf("받은 STATE 값 %d  받은 STATE_buf 값 %d", STATE, atoi(STATE_buf));
						}
						else {
							gotoxy(48, 24);	printf("다른 사람의 땅입니다. 통행료를 지불하셔야 합니다.");

							nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
							if (nRcv == -1) {
								printf("값을 받지 못하였습니다.");
								_getch();
								system("cls");
								return;
							}
							ENTER_buf[nRcv] = '\0';
							pas = atoi(ENTER_buf);
							while (pas != ENTER);

							STATE = BEH_NOTMINE;
							gotoxy(50, 50); printf("                             　　　　　　　　　　　　　　");
							//gotoxy(50, 50); printf("받은 STATE 값 %d  받은 STATE_buf 값 %d", STATE, atoi(STATE_buf));

						}
					}
				}
				else {
					Gold1;

					printf("%s 칸에 도착하였습니다.", stat->location->zone_name);
					gotoxy(48, 22);
					printf("현재 플레이어%d의 소지금 : %d 만원 입니다.", TURN, stat->money);

					White1;

					if (stat->location->zone_name == "출발") {
						gotoxy(45, 18);
						stat->money += bal / 5;
						Violet1;
						FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &channel[1]); // 반환점
						printf("한 바퀴를 돌았습니다. 월급 %d만원을 지급합니다.", bal / 5);
						White1;
						gotoxy(56, 26);	printf("ENTER를 입력하세요.");
						while ((pas = _getch()) != ENTER);

						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);

						STATE = NEXT_TURN;
					}
					else if (stat->location->zone_name == "황금열쇠") {
						STATE = GOLDEN_KEY;
					}
					else if (stat->location->zone_name == "무인도") {
						STATE = ISLAND;
					}
					else if (stat->location->zone_name == "우주여행") {
						Green1;
						FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &channel[1]); // 우주선
						gotoxy(48, 24);	printf("당신은 우주여행에 초대받았습니다.");
						gotoxy(48, 25);	printf("우주정거장 주인에게 %d만원을 지불하시오.", bal / 10);
						gotoxy(48, 26);	printf("다음 턴에 원하는 장소로 이동할 수 있습니다.");
						White1;
						gotoxy(48, 28);	printf("ENTER를 입력하세요.");
						while ((pas = _getch()) != ENTER);

						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);

						MENU_CLR();

						if (stat->money < bal / 10) {
							gotoxy(48, 24);	printf("보유금액이 부족합니다.");
							gotoxy(48, 25);	printf("다음 턴으로 넘어갑니다.");
							gotoxy(48, 26);	printf("ENTER를 입력하세요.");
						}
						else
						{
							stat->money -= bal / 10;
							gotoxy(stat->location->zone_X + (3 * TURN - 4), stat->location->zone_Y);
							printf("  ");
							if (TURN == P1_TURN)
							{
								gotoxy(138, 3);
								Red1;
								printf("①");
								White1;
							}
							else if (TURN == P2_TURN)
							{
								gotoxy(140, 3);
								Gold1;
								printf("②");
								White1;
							}
							else if (TURN == P3_TURN)
							{
								gotoxy(142, 3);
								Sky1;
								printf("③");
								White1;
							}
							else if (TURN == P4_TURN)
							{
								gotoxy(144, 3);
								Green1;
								printf("④");
								White1;
							}
							Green1;
							gotoxy(48, 24);	printf("%d만원을 지불하였습니다.", bal / 10);
							gotoxy(48, 25);	printf("우주정거장으로 이동하였습니다.");
							gotoxy(48, 26);	printf("다음 턴에 원하는 장소로 이동합니다.");
							MONEY_SHOW(user, user_set);
							gotoxy(48, 28);	printf("ENTER를 입력하세요.");
							stat->spaceship = EXIST;
						}
						while ((pas = _getch()) != ENTER);

						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);

						STATE = NEXT_TURN;
					}
					else if (stat->location->zone_name == "홀짝게임") {
						gotoxy(48, 24);	printf("당신은 홀짝게임에 초대받았습니다.");
						gotoxy(48, 25);	printf("홀짝게임 주인에게 %d만원을 지불하시오.", bal / 10);
						White1;

						gotoxy(48, 27);	printf("ENTER를 입력하세요.");
						while ((pas = _getch()) != ENTER);

						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);

						MENU_CLR();
						if (stat->money < bal / 10) {
							gotoxy(48, 24);	printf("보유금액이 부족합니다.");
							gotoxy(48, 25);	printf("다음 턴으로 넘어갑니다.");
							gotoxy(48, 26);	printf("ENTER를 입력하세요.");
							while ((pas = _getch()) != ENTER);

							_itoa(pas, ENTER_buf, 10);
							send(cs, ENTER_buf, strlen(ENTER_buf), 0);

							STATE = NEXT_TURN;
				
						}
						else {
							Green1;
							gotoxy(40, 24); printf("홀짝 게임을 할 수 있습니다. 한다:1/안한다:2 (비용 : %d만원)", bal / 10);
							White1;
							do
								sel_g = _getch();
							while (sel_g != 49 && sel_g != 50);

							_itoa(sel_g, sel_g_buf, 10);
							send(cs, sel_g_buf, strlen(sel_g_buf), 0);

							gotoxy(48, 22); printf("                                                 ");//도착하였습니다 초기화
							gotoxy(55, 20); printf("                                  ");//소지금 출력 초기화
							if (sel_g == 49) {
								stat->money -= (bal / 10);
								prize = bal / 10;
								gotoxy(40, 24);
								printf("                                                              ");
								STATE = MINI_GAME;
							}
							else {
								gotoxy(40, 24);
								printf("                                                               ");
								STATE = NEXT_TURN;
							}
						}
						break;
					}
					else {
						if (stat->location->owner == NULL) {
							STATE = BEH_MASTERLESS;

						}
						else if (stat->location->owner == TURN) {
							STATE = BEH_MINE;
						}
						else {
							gotoxy(48, 24);	printf("다른 사람의 땅입니다. 통행료를 지불하셔야 합니다.");

								gotoxy(48, 25);	printf("ENTER를 입력하세요.");
								while ((pas = _getch()) != ENTER);
								_itoa(pas, ENTER_buf, 10);
								send(cs, ENTER_buf, strlen(ENTER_buf), 0);
								//while (_getch() != ENTER);
							

							STATE = BEH_NOTMINE;

						}
					}
				}
				break;
			}
			case BEH_MASTERLESS:
			{
				PRE_STATE = BEH_MASTERLESS;
				if (TURN == P1_TURN) {

					nRcv = recv(cs, sel_buf, sizeof(sel_buf) - 1, 0);
					//gotoxy(65, 65); printf("　　　　　　　　　");
					//gotoxy(65, 65); printf("nRcv값: %d", nRcv);

					if (nRcv == -1) {
						gotoxy(50, 50); printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					sel_buf[nRcv] = '\0';
					SEL_BEH = atoi(sel_buf);
					
					//gotoxy(50, 51); printf("                    　　　　　　　　　　    ");
					//gotoxy(50, 51); printf("받은 SEL_BEH %d", SEL_BEH);
					//gotoxy(50, 52); printf("                    　　　　　　　　　　    ");
					//gotoxy(50, 52); printf("받은 SEL_buf %d", atoi(sel_buf));

					if ((SEL_BEH == '2') | (SEL_BEH == '3') | (SEL_BEH == '4'))
					{
						MENU_CLR();
						gotoxy(48, 24);  printf("플레이어 %d의 땅이 아닙니다.",TURN);

						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);

						MENU_CLR();
						SEL_BEH = 0;
						STATE = PRE_STATE;
						break;
					}
					STATE = BEH;
					MENU_CLR();
					break;
				}
				else {
					gotoxy(55, 24); printf("주인이 없는 땅입니다.");
					gotoxy(55, 25); printf("행동을 선택하셔야 합니다. ");
					gotoxy(55, 26); printf("1. 땅을 구매한다. ( %d만원 )", stat->location->zone_cost);
					gotoxy(55, 27); printf("2. 호텔을 짓는다. ( %d만원 )", stat->location->hotel_cost);
					gotoxy(55, 28); printf("3. 빌딩을 짓는다. ( %d만원 )", stat->location->building_cost);
					gotoxy(55, 29); printf("4. 별장을 짓는다. ( %d만원 )", stat->location->villa_cost);
					gotoxy(55, 30); printf("5. 그냥 지나간다.");
					gotoxy(55, 31); printf("행동의 번호를 입력해주세요 : ");
					gotoxy(85, 31);
					while ((SEL_BEH = _getch()) == ENTER);

					_itoa(SEL_BEH, sel_buf, 10);
					send(cs, sel_buf, strlen(sel_buf), 0);			//10진수 문자열로된 sel_buf값을 전달 한다.
					//gotoxy(50, 51); printf("                      　　　　　　　　　　　　　　　　　　　　　　　　　   ");
					//gotoxy(50, 51); printf("보낸 SEL_BEH %d", SEL_BEH);
				
					if ((SEL_BEH == '2') | (SEL_BEH == '3') | (SEL_BEH == '4'))
					{
						MENU_CLR();
						gotoxy(48, 24);  printf("당신의 땅이 아닙니다. 행동을 다시 선택해주세요.");
						gotoxy(48, 25);	printf("ENTER를 입력하세요.");

						while ((pas = _getch()) != ENTER);

						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);

						MENU_CLR();
						SEL_BEH = 0;
						STATE = PRE_STATE;

						break;
					}
					STATE = BEH;
				
					break;
				}	
			}
			case BEH:
			{
				MENU_CLR();

				
					switch (SEL_BEH) {
					case '1':
					{
						if (stat->location->owner == TURN)
						{
							if (TURN == P1_TURN) {
								gotoxy(48, 24);	printf("이미 플레이어 %d의 땅입니다.", TURN);
								
								nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
								if (nRcv == -1) {
									printf("값을 받지 못하였습니다.");
									_getch();
									system("cls");
									return;
								}
								ENTER_buf[nRcv] = '\0';
								pas = atoi(ENTER_buf);
								while (pas != ENTER);

								STATE = PRE_STATE;
							}
							else {
								gotoxy(48, 24);	printf("이미 당신의 땅입니다.");
								gotoxy(48, 25);	printf("행동을 다시 선택해주세요.");
								gotoxy(48, 26);	printf("ENTER를 입력하세요.");

								while ((pas = _getch()) != ENTER);
								_itoa(pas, ENTER_buf, 10);
								send(cs, ENTER_buf, strlen(ENTER_buf), 0);

								STATE = PRE_STATE;

							}
							MENU_CLR();
						}
						else {
							if (stat->money < stat->location->zone_cost) {
								gotoxy(48, 24);	printf("돈이 부족합니다.");
								gotoxy(48, 25);	printf("다음 턴으로 넘어갑니다.");
								if (TURN == P1_TURN) {
									
									nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									ENTER_buf[nRcv] = '\0';
									pas = atoi(ENTER_buf);
									while (pas != ENTER);

									STATE = NEXT_TURN;
								}
								else {
									gotoxy(48, 26);	printf("ENTER를 입력하세요.");

									while ((pas = _getch()) != ENTER);
									_itoa(pas, ENTER_buf, 10);
									send(cs, ENTER_buf, strlen(ENTER_buf), 0);

									STATE = NEXT_TURN;

								}
							}
							else {
								stat->money -= stat->location->zone_cost;
								stat->location->owner = TURN;
								zone_NAME_CLR(stat->location);
								BUY_ZONE(stat->location, TURN);
								gotoxy(48, 24);	printf("%s 지역의 구매를 완료하였습니다.", stat->location->zone_name);

								zone_list* tmp = ZONE->head->F_link;

								check = check_(tmp, TURN);
								if (check == 2) {
									gotoxy(54, 18);
									printf("플레이어 %d의 트리플 독점 조심!!", TURN); //트리플 독점 조심!!
								}
								else if (check == LINE1 || check == LINE2 || check == LINE3 || check == LINE4) {
									LINE_WIN = TURN;

									if (TURN == P2_TURN) {
										_itoa(LINE_WIN, win_buf, 10);
										send(cs, win_buf, strlen(win_buf), 0);
									}
									else {
										nRcv = recv(cs, win_buf, sizeof(win_buf) - 1, 0);
										if (nRcv == -1) {
											printf("값을 받지 못하였습니다.");
											_getch();
											system("cls");
											return;
										}
										win_buf[nRcv] = '\0';
										LINE_WIN = atoi(win_buf);
									}

									STATE = GAME_OVER;
									break;
								}
								else if (check > 2) {
									COLOR_WIN = TURN;

									if (TURN == P2_TURN) {
										_itoa(COLOR_WIN, win_buf, 10);
										send(cs, win_buf, strlen(win_buf), 0);
									}
									else {
										nRcv = recv(cs, win_buf, sizeof(win_buf) - 1, 0);
										if (nRcv == -1) {
											printf("값을 받지 못하였습니다.");
											_getch();
											system("cls");
											return;
										}
										win_buf[nRcv] = '\0';
										COLOR_WIN = atoi(win_buf);
									}

									STATE = GAME_OVER;
									break;
								}		
								if(TURN==P2_TURN){
									gotoxy(48, 25);	printf("ENTER를 입력하세요.");
									while ((pas = _getch()) != ENTER);

									_itoa(pas, ENTER_buf, 10);
									send(cs, ENTER_buf, strlen(ENTER_buf), 0);
								}
								else {
									nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									ENTER_buf[nRcv] = '\0';
									pas = atoi(ENTER_buf);
									while (pas != ENTER);
								}
	
								STATE = NEXT_TURN;
								break;
								
							}

						}
						break;
					}
					case '2':
					{
						if (stat->location->hotel == EXIST) {
							gotoxy(48, 25);	printf("이미 호텔이 존재합니다.");
							if (TURN == P1_TURN) {

								nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
								if (nRcv == -1) {
									printf("값을 받지 못하였습니다.");
									_getch();
									system("cls");
									return;
								}
								ENTER_buf[nRcv] = '\0';
								pas = atoi(ENTER_buf);
								while (pas != ENTER);

								STATE = PRE_STATE;
								MENU_CLR();
							}
							else {
								gotoxy(48, 26);	printf("행동을 다시 선택해주세요.");
								gotoxy(48, 27);	printf("ENTER를 입력하세요.");

								while ((pas = _getch()) != ENTER);
								_itoa(pas, ENTER_buf, 10);
								send(cs, ENTER_buf, strlen(ENTER_buf), 0);

								MENU_CLR();
								STATE = PRE_STATE;

							}
						}
						else {
							if (stat->money >= stat->location->hotel_cost) {
								stat->location->hotel = EXIST;
								stat->money -= stat->location->hotel_cost;
								STRUCTURE_DRAW(stat->location, 1, TURN);
								gotoxy(48, 24);	printf("%s에 호텔을 지었습니다.", stat->location->zone_name);

								if (TURN == P1_TURN) {

									
									nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									ENTER_buf[nRcv] = '\0';
									pas = atoi(ENTER_buf);
									while (pas != ENTER);

									STATE = NEXT_TURN;
								}
								else {
									gotoxy(48, 25);	printf("ENTER를 입력하세요.");

									while ((pas = _getch()) != ENTER);
									_itoa(pas, ENTER_buf, 10);
									send(cs, ENTER_buf, strlen(ENTER_buf), 0);

									STATE = NEXT_TURN;

								}
							}
							else {
								gotoxy(48, 24);	printf("돈이 부족합니다.");
								if (TURN == P1_TURN) {
									
									nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									ENTER_buf[nRcv] = '\0';
									pas = atoi(ENTER_buf);
									while (pas != ENTER);

									STATE = PRE_STATE;
									MENU_CLR();
								}
								else {
									gotoxy(48, 25);	printf("행동을 다시 선택해주세요.");
									gotoxy(48, 26);	printf("ENTER를 입력하세요.");

									while ((pas = _getch()) != ENTER);
									_itoa(pas, ENTER_buf, 10);
									send(cs, ENTER_buf, strlen(ENTER_buf), 0);

									MENU_CLR();
									STATE = PRE_STATE;

								}
							}
						}
						break;
					}
					case '3':
					{
						if (stat->location->building == EXIST) {
							gotoxy(48, 24);	printf("이미 빌딩이 존재합니다.");
							if (TURN == P1_TURN) {
								
								nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
								if (nRcv == -1) {
									printf("값을 받지 못하였습니다.");
									_getch();
									system("cls");
									return;
								}
								ENTER_buf[nRcv] = '\0';
								pas = atoi(ENTER_buf);
								while (pas != ENTER);

								STATE = PRE_STATE;
								MENU_CLR();
							}
							else {
								gotoxy(48, 25);	printf("행동을 다시 선택해주세요.");
								gotoxy(48, 26);	printf("ENTER를 입력하세요.");

								while ((pas = _getch()) != ENTER);
								_itoa(pas, ENTER_buf, 10);
								send(cs, ENTER_buf, strlen(ENTER_buf), 0);

								MENU_CLR();
								STATE = PRE_STATE;

							}
						}
						else {
							if (stat->money >= stat->location->building_cost) {
								stat->location->building = EXIST;
								stat->money -= stat->location->building_cost;
								STRUCTURE_DRAW(stat->location, 2, TURN);
								gotoxy(48, 25);	printf("%s에 빌딩을 지었습니다.", stat->location->zone_name);

								if (TURN == P1_TURN) {
									//recv(cs, STATE_buf, strlen(STATE_buf), 0);
									nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									ENTER_buf[nRcv] = '\0';
									pas = atoi(ENTER_buf);
									while (pas != ENTER);

									STATE = NEXT_TURN;
								}
								else {
									gotoxy(48, 25);	printf("ENTER를 입력하세요.");

									while ((pas = _getch()) != ENTER);
									_itoa(pas, ENTER_buf, 10);
									send(cs, ENTER_buf, strlen(ENTER_buf), 0);

									STATE = NEXT_TURN;
								}
							}
							else {
								gotoxy(48, 24);	printf("돈이 부족합니다.");
								if (TURN == P1_TURN) {
									//recv(cs, STATE_buf, strlen(STATE_buf), 0);
									nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									ENTER_buf[nRcv] = '\0';
									pas = atoi(ENTER_buf);
									while (pas != ENTER);

									STATE = PRE_STATE;
									MENU_CLR();
								}
								else {
									gotoxy(48, 25);	printf("행동을 다시 선택해주세요.");
									gotoxy(48, 26);	printf("ENTER를 입력하세요.");

									while ((pas = _getch()) != ENTER);
									_itoa(pas, ENTER_buf, 10);
									send(cs, ENTER_buf, strlen(ENTER_buf), 0);

									MENU_CLR();
									STATE = PRE_STATE;
								}
							}
						}
						break;
					}
					case '4':
					{
						if (stat->location->villa == EXIST) {
							gotoxy(48, 24);	printf("이미 별장이 존재합니다.");
							if (TURN == P1_TURN) {
								
								nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
								if (nRcv == -1) {
									printf("값을 받지 못하였습니다.");
									_getch();
									system("cls");
									return;
								}
								ENTER_buf[nRcv] = '\0';
								pas = atoi(ENTER_buf);
								while (pas != ENTER);

								STATE = PRE_STATE;
								MENU_CLR();
							}
							else {
								gotoxy(48, 25);	printf("행동을 다시 선택해주세요.");
								gotoxy(48, 26);	printf("ENTER를 입력하세요.");
								while (_getch() != ENTER);
								MENU_CLR();
								STATE = PRE_STATE;

							}
						}
						else {
							if (stat->money >= stat->location->villa_cost) {
								stat->location->villa = EXIST;
								stat->money -= stat->location->villa_cost;
								STRUCTURE_DRAW(stat->location, 3, TURN);
								gotoxy(48, 25);	printf("%s에 별장을 지었습니다.", stat->location->zone_name);

								if (TURN == P1_TURN) {
									
									nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									ENTER_buf[nRcv] = '\0';
									pas = atoi(ENTER_buf);
									while (pas != ENTER);

									STATE = NEXT_TURN;
								}
								else {
									gotoxy(48, 25);	printf("ENTER를 입력하세요.");

									while ((pas = _getch()) != ENTER);
									_itoa(pas, ENTER_buf, 10);
									send(cs, ENTER_buf, strlen(ENTER_buf), 0);

									STATE = NEXT_TURN;

								}
							}
							else {
								gotoxy(48, 24);	printf("돈이 부족합니다.");
								if (TURN == P1_TURN) {
									
									nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									ENTER_buf[nRcv] = '\0';
									pas = atoi(ENTER_buf);
									while (pas != ENTER);

									STATE = PRE_STATE;
									MENU_CLR();
								}
								else {
									gotoxy(48, 25);	printf("행동을 다시 선택해주세요.");
									gotoxy(48, 26);	printf("ENTER를 입력하세요.");

									while ((pas = _getch()) != ENTER);
									_itoa(pas, ENTER_buf, 10);
									send(cs, ENTER_buf, strlen(ENTER_buf), 0);

									MENU_CLR();
									STATE = PRE_STATE;

								}
							}
						}
						break;
					}
					case '5':
					{
						STATE = NEXT_TURN;
						break;
					}
					default:
					{
						//gotoxy(50, 50); printf("    　　　　　　　　　　　　　　　            ");
						//gotoxy(50, 50); printf("SEL_BEH %d", SEL_BEH);
						gotoxy(48, 24);	printf("행동 선택이 잘못되었습니다.");
						if (TURN == P1_TURN) {
							
							nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
							if (nRcv == -1) {
								printf("값을 받지 못하였습니다.");
								_getch();
								system("cls");
								return;
							}
							ENTER_buf[nRcv] = '\0';
							pas = atoi(ENTER_buf);
							while (pas != ENTER);

							STATE = PRE_STATE;

						}
						else {
							gotoxy(48, 25);	printf("ENTER를 입력하세요.");

							while ((pas = _getch()) != ENTER);
							_itoa(pas, ENTER_buf, 10);
							send(cs, ENTER_buf, strlen(ENTER_buf), 0);

							MENU_CLR();
							STATE = PRE_STATE;

						}
						break;
					}
					}
					break;
				}
			case BEH_NOTMINE:
			{
				SUM_VAL = 0;
				SUM_TOLL = 0;
				SUM_TOLL += stat->location->zone_toll;
				SUM_VAL+= stat->location->zone_cost;
				if (stat->location->hotel == EXIST) {
					SUM_TOLL += stat->location->hotel_toll;
					SUM_VAL += stat->location->hotel_cost;
				}
				if (stat->location->building == EXIST) {
					SUM_TOLL += stat->location->building_toll;
					SUM_VAL += stat->location->building_cost;
				}
				if (stat->location->villa == EXIST) {
					SUM_TOLL += stat->location->villa_toll;
					SUM_VAL += stat->location->villa_cost;
				}
				if (TURN == P1_TURN) {
					{
						if (stat->passcard == EXIST) {
							MENU_CLR();
							gotoxy(48, 24);	printf("우대권을 사용하여 그냥 지나갑니다.");

							nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
							if (nRcv == -1) {
								printf("값을 받지 못하였습니다.");
								_getch();
								system("cls");
								return;
							}
							ENTER_buf[nRcv] = '\0';
							pas = atoi(ENTER_buf);
							while (pas != ENTER);

							gotoxy(48, 24);	printf("                            ");
							stat->passcard = NON_EXIST;

							STATE = NEXT_TURN;
							break;

						}
						if (stat->money < SUM_TOLL) {
							MENU_CLR();
							gotoxy(48, 24);	printf("통행료 %d만원에 대한 보유금액이 부족합니다.", SUM_TOLL);
							
							STATE = NOT_ENOUGH_MONEY;
							}
						else {
							
							STATE = ENOUGH_MONEY;
						}
						
						break;
					}
				}
				else {
							if (stat->passcard == EXIST) {
								MENU_CLR();
								gotoxy(48, 24);	printf("우대권을 사용하여 그냥 지나갑니다.");
								while ((pas = _getch()) != ENTER);

								_itoa(pas, ENTER_buf, 10);
								send(cs, ENTER_buf, strlen(ENTER_buf), 0);

								gotoxy(48, 24);	printf("                            ");
								gotoxy(48, 25);	printf("                      ");
								stat->passcard = NON_EXIST;
								
								STATE = NEXT_TURN;

								break;
							}

							if (stat->money < SUM_TOLL) {
								MENU_CLR();
								gotoxy(48, 24);	printf("통행료 %d만원에 대한 보유금액이 부족합니다.", SUM_TOLL);
								STATE = NOT_ENOUGH_MONEY;
							}
							else {
								STATE = ENOUGH_MONEY;
							}			
							break;
						}
					}
			case ENOUGH_MONEY:
			{
				MENU_CLR();
				gotoxy(48, 24);	printf("통행료 %d 만원을 지불합니다.", SUM_TOLL);
				stat->money -= SUM_TOLL;
				(user + (stat->location->owner) - 1)->money += SUM_TOLL;
				if (TURN == P2_TURN) {
					gotoxy(48, 25);	printf("ENTER를 입력해주세요.");
					while ((pas = _getch()) != ENTER);

					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);

				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}

				gotoxy(48, 24);	printf("                            ");
				gotoxy(48, 25);	printf("                      ");
				if (stat->money >= SUM_VAL) {
					gotoxy(48, 24);	printf("%d 만원에 해당 지역을 구매하실 수 있습니다.", SUM_VAL);
					if (TURN == P2_TURN) {
						gotoxy(48, 25);	printf("구매:1 / 지나감:2");
						do
							sel = _getch();
						while (sel != 49 && sel != 50);

						_itoa(sel, tmp_buf, 10);
						send(cs, tmp_buf, strlen(tmp_buf), 0);
					}
					else {
						//0614
						nRcv = recv(cs, tmp_buf, sizeof(tmp_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						tmp_buf[nRcv] = '\0';

						sel = atoi(tmp_buf);
					}
					if (sel == 49) {
						gotoxy(48, 24);	printf("                                                    ");
						stat->money -= SUM_VAL;
						(user + (stat->location->owner) - 1)->money += SUM_VAL;
						BUY_ZONE(stat->location, TURN);
						
						stat->location->owner = TURN;
						if (TURN == P2_TURN) {
							gotoxy(48, 24);
							printf("%d 만원에 %s 지역을 구매하셨습니다.", SUM_VAL, stat->location->zone_name);

							zone_list* tmp = ZONE->head->F_link;

							check = check_(tmp, TURN);
							if (check == 2) {
								gotoxy(54, 18);
								printf("플레이어 %d의 트리플 독점 조심!!", TURN); //트리플 독점 조심!!
							}
							else if (check == LINE1 || check == LINE2 || check == LINE3 || check == LINE4) {
								LINE_WIN = TURN;

								if (TURN == P2_TURN) {
									_itoa(LINE_WIN, win_buf, 10);
									send(cs, win_buf, strlen(win_buf), 0);
								}
								else {
									nRcv = recv(cs, win_buf, sizeof(win_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									win_buf[nRcv] = '\0';
									LINE_WIN = atoi(win_buf);
								}

								STATE = GAME_OVER;
								break;
							}
							else if (check > 2) {
								COLOR_WIN = TURN;

								if (TURN == P2_TURN) {
									_itoa(COLOR_WIN, win_buf, 10);
									send(cs, win_buf, strlen(win_buf), 0);
								}
								else {
									nRcv = recv(cs, win_buf, sizeof(win_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									win_buf[nRcv] = '\0';
									COLOR_WIN = atoi(win_buf);
								}

								STATE = GAME_OVER;
								break;
							}
							gotoxy(48, 25);	printf("                  ");
							gotoxy(48, 25);	printf("ENTER를 입력해주세요.");

							while (_getch() != ENTER);
							_itoa(_getch(), ENTER_buf, 10);
							send(cs, ENTER_buf, strlen(ENTER_buf), 0);
						}
						else {
							zone_list* tmp = ZONE->head->F_link;

							check = check_(tmp, TURN);
							if (check == 2) {
								gotoxy(54, 18);
								printf("플레이어 %d의 트리플 독점 조심!!", TURN); //트리플 독점 조심!!
							}
							else if (check == LINE1 || check == LINE2 || check == LINE3 || check == LINE4) {
								LINE_WIN = TURN;

								if (TURN == P1_TURN) {
									_itoa(LINE_WIN, win_buf, 10);
									send(cs, win_buf, strlen(win_buf), 0);
								}
								else {
									nRcv = recv(cs, win_buf, sizeof(win_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									win_buf[nRcv] = '\0';
									LINE_WIN = atoi(win_buf);
								}

								STATE = GAME_OVER;
								break;
							}
							else if (check > 2) {
								COLOR_WIN = TURN;

								if (TURN == P1_TURN) {
									_itoa(COLOR_WIN, win_buf, 10);
									send(cs, win_buf, strlen(win_buf), 0);
								}
								else {
									nRcv = recv(cs, win_buf, sizeof(win_buf) - 1, 0);
									if (nRcv == -1) {
										printf("값을 받지 못하였습니다.");
										_getch();
										system("cls");
										return;
									}
									win_buf[nRcv] = '\0';
									COLOR_WIN = atoi(win_buf);
								}

								STATE = GAME_OVER;
								break;
							}
							gotoxy(48, 24);
							printf("플레이어 %d가 %d 만원에 %s 지역을 구매하셨습니다.", TURN, SUM_VAL, stat->location->zone_name);
							nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
							if (nRcv == -1) {
								printf("값을 받지 못하였습니다.");
								_getch();
								system("cls");
								return;
							}
							ENTER_buf[nRcv] = '\0';
							pas = atoi(ENTER_buf);
							
							while (pas!= ENTER);
						}
					}
				}
				STATE = NEXT_TURN;
				break;
			}
			case NOT_ENOUGH_MONEY:
			{
				PRE_STATE = NOT_ENOUGH_MONEY;
				SELL_LIST_CLR();
				if (TURN == P1_TURN) {
					gotoxy(48, 25);	printf("건물을 매각중 입니다.");
					ZONE_LIST_SHOW_CLR();
					stat->gameover = SELL_LIST(TURN, ZONE);
					if (stat->gameover == GAMEOVER)
					{
						gotoxy(48, 27);	Violet1;	printf("이런..... 재산이 없네요?......");
						gotoxy(48, 28);	printf("플레이어%d는 파산입니다.", TURN);
						gameover_cnt--;
						(user + (stat->location->owner) - 1)->money += stat->money;
						stat->money = 0;
						while (_getch() != ENTER);
						gotoxy(stat->location->zone_X + (3 * TURN) - 4, stat->location->zone_Y); printf("  ");
						
						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);

						STATE = GAME_OVER;
						break;
					}

					nRcv = recv(cs, zone_buf, sizeof(zone_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					zone_buf[nRcv] = '\0';

					input_zone = atoi(zone_buf);

					tmp_zone = ZONE->head->F_link;
					while (tmp_zone->zone_name != "출발") {
						if (input_zone == tmp_zone->zone_num) {
							if (tmp_zone->owner == TURN) {
								STATE = SELL_ZONE;
								break;
							}
							else
							{					
								printf("플레이어 %d의 땅이 아닙니다.", TURN);
								STATE = PRE_STATE;;
								MENU_CLR();					
								break;
							}
						}
						else
							tmp_zone = tmp_zone->F_link;
					}
					if (tmp_zone->zone_name == "출발")
					{
						recv(cs, STATE_buf, strlen(STATE_buf), 0);
						STATE = atoi(STATE_buf);
						MENU_CLR();						
					}
				}
				else {
					gotoxy(48, 25);	printf("보유하고 있는 땅 중에 하나를 팔아야 합니다.");
					gotoxy(48, 26);	printf("현재 매각가능한 땅,건물 정보를 확인하세요.");
					ZONE_LIST_SHOW_CLR();
					stat->gameover = SELL_LIST(TURN, ZONE);
					if (stat->gameover == GAMEOVER)

					{
						gotoxy(48, 27);	Violet1;	printf("이런..... 재산이 없네요?......");
						gotoxy(48, 28);	printf("플레이어%d는 파산입니다.", TURN);
						gotoxy(48, 29);	printf("ENTER를 입력하세요.");
						gameover_cnt--;
						(user + (stat->location->owner) - 1)->money += stat->money;
						stat->money = 0;
						while (_getch() != ENTER);
						gotoxy(stat->location->zone_X + (3 * TURN) - 4, stat->location->zone_Y); printf("  ");
						STATE = NEXT_TURN;

						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);
						STATE = GAME_OVER;
						break;
					}
					gotoxy(48, 27);	printf("팔고 싶은 땅의 번호를 입력해 주세요 : ");
					for (i = 0; i < 3; i++)
						Zone_NUM[i] = NULL;
					for (i = 0; i < 3; i++) {
						Zone_NUM[i] = _getch();
						if ((Zone_NUM[0] < 48) || (Zone_NUM[0] > 57)) {
							i--;
							gotoxy(88, 27); printf("    ");
							gotoxy(88, 27);
						}
						else if (Zone_NUM[1] == ENTER)
							break;
						else if ((Zone_NUM[i] < 48) || (Zone_NUM[i] > 57)) {
							if (i == 1)
								strcpy(Zone_NUM, ERR);
							break;
						}
						else
							printf("%c", Zone_NUM[i]);
					}
					input_zone = atoi(Zone_NUM);

					gotoxy(48, 29);

					if (Zone_NUM == ERR)
					{
						printf("정확한 번호를 입력하세요.");
						printf("ENTER를 입력해주세요.");
						while (_getch() != ENTER);
						MENU_CLR();
						STATE = PRE_STATE;
						break;
					}
					else
					{
						_itoa(input_zone, zone_buf, 10);
						send(cs, zone_buf, strlen(zone_buf), 0);

						tmp_zone = ZONE->head->F_link;
						while (tmp_zone->zone_name != "출발") {
							if (input_zone == tmp_zone->zone_num) {
								if (tmp_zone->owner == TURN) {
									STATE = SELL_ZONE;
									break;
								}
								else
								{
										printf("당신의 땅이 아닙니다.");
										gotoxy(48, 30);
										printf("ENTER를 입력하세요.");
										while (_getch() != ENTER);
										MENU_CLR();
										STATE = PRE_STATE;		
									break;
								}
							}
							else
								tmp_zone = tmp_zone->F_link;
						}
						if (tmp_zone->zone_name == "출발")
						{
							if (TURN == P1_TURN) {
								STATE = PRE_STATE;
								MENU_CLR();
							}
							else {
								printf("정확한 번호를 입력하세요.");
								printf("ENTER를 입력해주세요.");
								while (_getch() != ENTER);
								MENU_CLR();
								STATE = PRE_STATE;
							}
						}
					}	
				}
				break;
			}
			case SELL_ZONE:
			{
				MENU_CLR();
				SELL_MONEY = 0;
				tmp_zone = ZONE->head;

				while (tmp_zone->zone_num != input_zone)
					tmp_zone = tmp_zone->F_link;

				SELL_MONEY += tmp_zone->zone_cost;
				if (tmp_zone->hotel == EXIST)
				{
					SELL_MONEY += tmp_zone->hotel_cost;
					tmp_zone->hotel = NON_EXIST;
				}
				if (tmp_zone->building == EXIST)
				{
					SELL_MONEY += tmp_zone->building_cost;
					tmp_zone->building = NON_EXIST;
				}
				if (tmp_zone->villa == EXIST)
				{
					SELL_MONEY += tmp_zone->villa_cost;
					tmp_zone->villa = NON_EXIST;
				}

				tmp_zone->owner = NULL;
				stat->money += SELL_MONEY;

				gotoxy(tmp_zone->zone_X + 2, tmp_zone->zone_Y - 1);

				printf("%s", tmp_zone->zone_name);
				//건물 초기화
				if (strlen(tmp_zone->zone_name) == 4) //두 글자
					gotoxy(tmp_zone->zone_X - 4, tmp_zone->zone_Y + 2);
				else if (strlen(tmp_zone->zone_name) == 6) //세 글자
					gotoxy(tmp_zone->zone_X - 3, tmp_zone->zone_Y + 2);
				else
					gotoxy(tmp_zone->zone_X - 2, tmp_zone->zone_Y + 2);
				printf("              ");

				MONEY_SHOW(user, user_set);
				gotoxy(48, 24);
				printf("%s지역을 매각하였습니다.", tmp_zone->zone_name);
				gotoxy(48, 25);
				printf("다음과 같은 금액을 받았습니다 : %d 만원", SELL_MONEY);
				if (TURN == P2_TURN) {
					gotoxy(48, 26);
					printf("ENTER를 입력하세요.");
					pas = _getch();
					while (pas != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}
				MENU_CLR();


				if (key_flag == EXIST) 
					STATE = KEY_STATE;	//판매 황금키일때
				else
					STATE = BEH_NOTMINE; //일반적일때
				break;
			}
			case BEH_MINE:
			{
				PRE_STATE = BEH_MINE;
				if (TURN == P2_TURN) {
					gotoxy(48, 24); printf("당신의 땅입니다.");
					gotoxy(48, 25); printf("행동을 선택하셔야 합니다. ");
					gotoxy(48, 26); printf("1. 땅을 구매한다. ( %d만원 )", stat->location->zone_cost);
					gotoxy(48, 27); printf("2. 호텔을 짓는다. ( %d만원 )", stat->location->hotel_cost);
					gotoxy(48, 28); printf("3. 빌딩을 짓는다. ( %d만원 )", stat->location->building_cost);
					gotoxy(48, 29); printf("4. 별장을 짓는다. ( %d만원 )", stat->location->villa_cost);
					gotoxy(48, 30); printf("5. 그냥 지나간다.");
					gotoxy(48, 31); printf("행동의 번호를 입력해주세요 : ");
					gotoxy(80, 31);
					while ((SEL_BEH = _getch()) == ENTER); // SEL_BEH 선택받기

					_itoa(SEL_BEH, sel_buf, 10);
					send(cs, sel_buf, strlen(sel_buf), 0);			//10진수 문자열로된 sel_buf값을 전달 한다.
				}
				else {
					nRcv = recv(cs, sel_buf, sizeof(sel_buf) - 1, 0);
					//gotoxy(65, 65); printf("　　　　　　　　　");
					//gotoxy(65, 65); printf("nRcv값: %d", nRcv);

					if (nRcv == -1) {
						gotoxy(50, 50); printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					sel_buf[nRcv] = '\0';
					SEL_BEH = atoi(sel_buf);
				}
				//X0_CLR();
				STATE = BEH;
				break;
			}
			case NEXT_TURN:
			{
				gotoxy(23, 38); printf(" 　　　　　　　　　　　　　　　　　　　　　　　　　");
				g_cnt = 0; //홀짝 게임 횟수 초기화
				gotoxy(56, 26);	printf("                    "); //출발지 ENTER
				gotoxy(45, 18); printf("                                                "); //출발지 도착 문구 초기화
				gotoxy(48, 24); printf("                                   "); //플레이어 지역 구매 문구 초기화
				island_CLR();
				gotoxy(40, 35); printf("                                                    "); //더블 초기화
	
				MENU_CLR();

				MONEY_SHOW(user, user_set);

				if (gameover_cnt == 1)
					STATE = GAME_OVER;
				else {

					if (((dice1 != dice2) || (stat->gameover == GAMEOVER))) {
						while (1) {
							if ((TURN + 1) > user_set)
								TURN = P1_TURN;
							else
								++TURN;

							if ((user + TURN - 1)->gameover != GAMEOVER)
								break;
						}
					}
					

					if (TURN == P1_TURN)
						Red1;
					else
						Gold1;

					gotoxy(48, 22); printf("                                                 "); //도착하였습니다 초기화
					gotoxy(55, 20); printf("                                  "); //소지금 출력 초기화

					gotoxy(23, 37); printf("                                                   ");
					gotoxy(23, 37); printf("플레이어%d이(가) 주사위를 굴릴 차례입니다.", TURN);
					gotoxy(23, 38); printf("                                                   ");
					White1;
					if (TURN == P2_TURN) {
						gotoxy(23, 38); printf("ENTER를 입력해주세요.");

						while ((pas = _getch()) != ENTER);
						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);
						STATE = P_TURN;
					}
					else {
						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);
						STATE = P_TURN;

					}
					gotoxy(54, 18); printf("                                  "); //트리플 독점 조심!!
				}
				break;
			}
			case ISLAND:
			{
				gotoxy(48, 17); printf("　　　　　　　　　　　　　　　　　　　　");
				Green1;
				gotoxy(48, 24);
				FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &channel[1]); // 무인도
				printf("무인도에 표류하였습니다.");
				White1;
				if (dice1 == dice2) {
					dice1 = -1;
					gotoxy(48, 26);	printf("더블이 나왔으므로 다음 턴에 바로 탈출합니다.");
					if (TURN == P2_TURN) {
						gotoxy(48, 27);	printf("ENTER를 입력하세요.");
					}
				}
				else if (stat->escape == EXIST) {
					gotoxy(48, 26);	printf("무인도 탈출권을 사용하여 바로 탈출합니다.");
					stat->escape = NON_EXIST;
					if (TURN == P2_TURN) {
						gotoxy(48, 27);	printf("ENTER를 입력하세요.");
					}
				}
				else {
					gotoxy(48, 26);	printf("앞으로 3턴 동안 갇혀 있게 됩니다.");
					gotoxy(48, 27);	printf("단, 더블이 나오면 바로 탈출을 할 수 있습니다.");
					if (TURN == P2_TURN) {
						gotoxy(48, 28);	printf("ENTER를 입력하세요.");
					}
					stat->island_index = 3;
				}

				if (TURN == P2_TURN) {
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}

				MENU_CLR();
				STATE = NEXT_TURN;
				break;
			}
			case IN_ISLAND:
			{
				gotoxy(57, 20);	printf("                    ");
				gotoxy(48, 17); printf("                                     ");
				if (stat->island_index == 0) {

					gotoxy(57, 19);	printf("무인도에서 탈출합니다.");
					move_player(user, stat, TURN, user_set,bal);
					island_CLR();
					DICE_CLR();
				
					STATE = re_map;
				}
				else {
					--(stat->island_index);
					if (dice1 != dice2) {
						gotoxy(48, 20);	printf("이번 턴에는 탈출하실 수가 없네요...");
						if (TURN == P2_TURN) {
							gotoxy(48, 21);	printf("ENTER를 입력하세요.");
							pas = _getch();
							while (pas != ENTER);
							_itoa(pas, ENTER_buf, 10);
							send(cs, ENTER_buf, strlen(ENTER_buf), 0);
						}
						else {
							nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
							if (nRcv == -1) {
								printf("값을 받지 못하였습니다.");
								_getch();
								system("cls");
								return;
							}
							ENTER_buf[nRcv] = '\0';
							pas = atoi(ENTER_buf);
							while (pas != ENTER);
						}
						island_CLR();
						DICE_CLR();
						STATE = NEXT_TURN;
					}
					else if (dice1 == dice2) {
						gotoxy(48, 20);	printf("더블입니다!!");
						gotoxy(48, 21);	printf("무인도에서 탈출 합니다!!");
						stat->island_index = 0;
						move_player(user, stat, TURN, user_set,bal);
						island_CLR();
						DICE_CLR();
						STATE = re_map;
					}
				}
				break;
			}
			case SPACESHIP:
			{
				DICE_CLR();
				ZONE_LIST_SHOW(ZONE);
				PRE_STATE = SPACESHIP;
				dice1--;

				stat->spaceship = NON_EXIST;
				White1;
				if (TURN == P2_TURN) {
					gotoxy(48, 24);	printf("이동하기를 원하는 지역의 번호를 입력하세요: ");
					for (i = 0; i < 3; i++)
						Zone_NUM[i] = NULL;
					for (i = 0; i < 3; i++)
					{
						Zone_NUM[i] = _getch();
						if ((Zone_NUM[0] < 48) || (Zone_NUM[0] > 57)) //0보다 작거나 9보다 크면
						{
							i--;
							gotoxy(90, 24);
							printf("    ");
							gotoxy(90, 24);
						}
						else if (Zone_NUM[1] == ENTER)
							break;
						else if ((Zone_NUM[i] < 48) || (Zone_NUM[i] > 57)) {
							if (i == 1)
								strcpy(Zone_NUM, ERR); //Zone_NUM에 ERR를 복사
							break;
						}
						else
							printf(" %c", Zone_NUM[i]); //입력값 표시
					}
					input_zone = atoi(Zone_NUM); //입력받은 문자열 숫자를 int로 변경
					MENU_CLR();

					if ((input_zone < 0) || (input_zone > 27) || (Zone_NUM == ERR))
					{
						gotoxy(48, 24);	printf("정확한 번호를 입력하여 주세요.");
						STATE = PRE_STATE;
						gotoxy(48, 25);	printf("ENTER를 입력하세요.");
						while (_getch() != ENTER);
						MENU_CLR();
						break;
					}
					_itoa(input_zone, zone_buf, 10);
					send(cs, zone_buf, strlen(zone_buf), 0);
				}
				else {
					nRcv = recv(cs, zone_buf, sizeof(zone_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					zone_buf[nRcv] = '\0';
					input_zone = atoi(zone_buf);
					//gotoxy(50, 50); printf("                ");
					//gotoxy(50, 50); printf("%d", input_zone);
				}

				gotoxy(138 + (2 * (TURN - 1)), 3); printf("  "); //우주선 내의 플레이어 CLR

				while (stat->location->zone_num != input_zone) {
					if (stat->location->zone_name == "출발")
					{
						gotoxy(44, 19);
						stat->money += bal / 10;
						Violet1;
						FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &channel[1]); // 반환점
						printf("한 바퀴를 돌았습니다. 월급 %d만원을 지급합니다.", bal / 10);
						White1;
						MONEY_SHOW(user, user_set);
					}
					stat->location = stat->location->F_link;
				}

				gotoxy(stat->location->zone_X + (3 * TURN) - 4, stat->location->zone_Y);
				if (TURN == P1_TURN) {
					Red1; printf("①");
				}
				else if (TURN == P2_TURN)
				{
					Gold1; printf("②");
				}
				else if (TURN == P3_TURN)
				{
					Sky1; printf("③");
				}
				else if (TURN == P4_TURN)
				{
					Green1;	printf("④");
				}
				White1;
				STATE = re_map;
				FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &channel[1]); // 우주선
				gotoxy(48, 24);	printf("이동을 완료하였습니다.");
				if (TURN == P2_TURN) {
					gotoxy(48, 25);	printf("ENTER를 입력해주세요.");
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}
				gotoxy(44, 19); printf("                                               ");
				break;
			}
			case GOLDEN_KEY:
			{
				FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[7], 0, &channel[1]); // 카드소리

				if (TURN == P2_TURN) {
					//pick = 23;				//우주여행 테스트할려고 사용
					pick = rand() % 24;

					_itoa(pick, key_buf, 10);
					send(cs, key_buf, strlen(key_buf), 0);


					take_golden_key(G_KEY, pick);

				}
				else {

					
					nRcv = recv(cs, key_buf, sizeof(key_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					key_buf[nRcv] = '\0';
					pick = atoi(key_buf);
					

					take_golden_key(G_KEY, pick);
				}
				show_golden_key(G_KEY->front);
				if (TURN == P2_TURN) {
					White1;
					while ((pas = _getch()) != ENTER);

					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);

				}
				else {
					White1;
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}


				gk_CLR();

				switch (G_KEY->front->key_num + 1)
				{
				case 1:
				{
					STATE = KEY1;
					break;
				}
				case 2:
				{
					STATE = KEY2;
					break;
				}
				case 3:
				{
					STATE = KEY3;
					break;
				}
				case 4:
				{
					STATE = KEY4;
					break;
				}
				case 5:
				{
					STATE = KEY5;
					break;
				}
				case 6:
				{
					STATE = KEY6;
					break;
				}
				case 7:
				{
					STATE = KEY7;
					break;
				}
				case 8:
				{
					STATE = KEY8;
					break;
				}
				case 9:
				{
					STATE = KEY9;
					break;
				}
				case 10:
				{
					STATE = KEY10;
					break;
				}
				case 11:
				{
					STATE = KEY11;
					break;
				}
				case 12:
				{
					STATE = KEY12;
					break;
				}
				case 13:
				{
					STATE = KEY13;
					break;
				}
				case 14:
				{
					STATE = KEY14;
					break;
				}
				case 15:
				{
					STATE = KEY15;
					break;
				}
				case 16:
				{
					STATE = KEY16;
					break;
				}
				case 17:
				{
					STATE = KEY17;
					break;
				}
				case 18:
				{
					STATE = KEY18;
					break;
				}
				case 19:
				{
					STATE = KEY19;
					break;
				}
				case 20:
				{
					STATE = KEY20;
					break;
				}
				case 21:
				{
					STATE = KEY21;
					break;
				}
				case 22:
				{
					STATE = KEY22;
					break;
				}
				case 23:
				{
					STATE = KEY23;
					break;
				}
				case 24:
				{
					STATE = KEY24;
					break;
				}
				default:
					break;
				}
				break;
			}
			case KEY1:
			{
				gotoxy(55, 24);
				if (stat->money < bal/10)
				{
					printf("병원비가 모자랍니다");
					KEY_STATE = KEY1;
					key_flag = EXIST;
					STATE = NOT_ENOUGH_MONEY;
				}
				else
				{
					stat->money -= bal/10;
					printf("병원비로 %d만원을 지불하였습니다.",bal/10);
					key_flag = NULL;
					MONEY_SHOW(user, user_set);
					STATE = NEXT_TURN;
				}
			
				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}
				gk_CLR();
				break;
			}
			case KEY2:
			{
				stat->money += bal/2;
				gotoxy(55, 24);	printf("당첨금으로 %d만원을 받았습니다.",bal/2);
				MONEY_SHOW(user, user_set);
				STATE = NEXT_TURN;

				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}

				gk_CLR();
				break;
			}
			case KEY3:
			{
				stat->escape = EXIST;
				gotoxy(55, 24);	printf("무인도탈출권을 받았습니다.");
				STATE = NEXT_TURN;

				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}

				gk_CLR();
				break;
			}
			case KEY4:
			{
				stat->pre_X = stat->location->zone_X;
				stat->pre_Y = stat->location->zone_Y;

				while (stat->location->zone_name != "무인도")
					stat->location = stat->location->F_link;
				MOVING_init(stat, TURN);
				STATE = ISLAND;
				break;
			}
			case KEY5:
			{
				stat->OE = EXIST;
				gotoxy(55, 24);	printf("주사위 홀짝권을 발급받았습니다.");
				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}

				STATE = NEXT_TURN;
				break;
			}
			case KEY6:
			{
				gotoxy(55, 24);
				if (stat->money < bal/10)
				{
					printf("벌금 %d만원에 대한 보유금액이모자랍니다.",bal/10);
					KEY_STATE = KEY1;
					key_flag = EXIST;
					STATE = NOT_ENOUGH_MONEY;
				}
				else
				{
					stat->money -= bal/10;
					printf("벌금으로 %d만원을 지불하였습니다.",bal/10);
					key_flag = NULL;
					MONEY_SHOW(user, user_set);
					STATE = NEXT_TURN;
				}
				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}

				gk_CLR();
				break;
			}
			case KEY7:
			{
				gotoxy(55, 24);
				if (stat->money < bal/10)
				{
					printf("등록금을 내기에 보유금액이 모자랍니다.");
					KEY_STATE = KEY1;
					key_flag = EXIST;
					STATE = NOT_ENOUGH_MONEY;
				}
				else
				{
					stat->money -= bal/10;
					printf("등록금으로 %d만원을 지불하였습니다.",bal/10);
					key_flag = NULL;
					MONEY_SHOW(user, user_set);
					STATE = NEXT_TURN;
				}
				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}
				gk_CLR();
				break;
			}
			case KEY8:
			{
				stat->money += bal/5;
				gotoxy(55, 24);	printf("노후연금으로 %d만원을 받았습니다.",bal/5);
				MONEY_SHOW(user, user_set);
				STATE = NEXT_TURN;
				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}
				gk_CLR();
				break;
			}
			case KEY9:
			{
				stat->pre_X = stat->location->zone_X;
				stat->pre_Y = stat->location->zone_Y;
				for (i = 0; i < 3; i++)
					stat->location = stat->location->B_link;
				MOVING_init(stat, TURN);
				STATE = re_map;
				break;
			}
			case KEY10:
			{
				stat->pre_X = stat->location->zone_X;
				stat->pre_Y = stat->location->zone_Y;
				for (i = 0; i < 2; i++)
					stat->location = stat->location->B_link;
				MOVING_init(stat, TURN);
				STATE = re_map;
				break;
			}
			case KEY11:
			{
				stat->pre_X = stat->location->zone_X;
				stat->pre_Y = stat->location->zone_Y;
				while (stat->location->zone_name != "출발")
					stat->location = stat->location->F_link;
				MOVING_init(stat, TURN);
				STATE = re_map;
				gotoxy(44, 19);
				stat->money += bal/5; //출발지에 딱 도착 시 월급 2배
				Violet1;
				FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &channel[1]); // 반환점
				printf("한 바퀴를 돌았습니다. 월급 %d만원을 지급합니다.",bal/5);
				White1;
				if (TURN == P2_TURN) {
					gotoxy(55, 33);	printf("ENTER를 입력하세요.");
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}
				gotoxy(55, 33);	printf("                      ");
				gotoxy(44, 19); printf("                                                ");
				break;
			}
			case KEY12:
			{
				stat->money += bal/10;
				gotoxy(55, 24);	printf("우승상금으로 %d만원을 받았습니다.",bal/10);
				MONEY_SHOW(user, user_set);
				STATE = NEXT_TURN;
				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}
				gk_CLR();
				break;
			}
			case KEY13:
			{
				stat->passcard = EXIST;
				gotoxy(55, 24);	printf("우대권을 발급받았습니다.");

				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					while ((pas = _getch()) != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}
				STATE = NEXT_TURN;
				break;
			}
			case KEY14:
			{
				stat->pre_X = stat->location->zone_X;
				stat->pre_Y = stat->location->zone_Y;
				while (stat->location->zone_name != "부산")
					stat->location = stat->location->F_link;
				MOVING_init(stat, TURN);
				STATE = re_map;
				break;
			}
			case KEY15:
			{
				tmp_zone = ZONE->head->F_link;

				while (tmp_zone->zone_name != "출발"){
					if (tmp_zone->owner == TURN){
						if (tmp_zone->hotel == EXIST)
							fine += 5;
						if (tmp_zone->building == EXIST)
							fine += 3;
						if (tmp_zone->villa == EXIST)
							fine += 1;
					}
					tmp_zone = tmp_zone->F_link;
				}

				if (fine > stat->money)
				{
					gotoxy(55, 24);	printf("방범비 %d만원이 부족합니다.", fine);
					STATE = NOT_ENOUGH_MONEY;
					fine = 0;
					key_flag = EXIST;
					KEY_STATE = KEY18;
					break;
				}
				else
				{
					stat->money -= fine;
					MONEY_SHOW(user, user_set);
					gotoxy(55, 24);	printf("방범비로 %d만원을 지불하였습니다.", fine);
					fine = 0;
					if (TURN == P2_TURN) {
						gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
						pas = _getch();
						while (pas != ENTER);
						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);
					}
					else {
						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);
					}
					STATE = NEXT_TURN;
					key_flag = NULL;
					break;
				};
			}
			case KEY16:
			{
				stat->money += bal/5;
				gotoxy(55, 24);	printf("장학금으로 %d만원을 받았습니다.",bal/5);
				MONEY_SHOW(user, user_set);
				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					pas = _getch();
					while (pas != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}
				STATE = NEXT_TURN;
				gk_CLR();
				break;
			}
			case KEY17:
			{
				gotoxy(55, 24);	printf("%d 만원을 받았습니다.", bal/5);
				stat->money += bal/5;
				MONEY_SHOW(user, user_set);
				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					pas = _getch();
					while (pas != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}
				STATE = NEXT_TURN;
				gk_CLR();
				break;
			}
			case KEY18:
			{
				tmp_zone = ZONE->head->F_link;

				while (tmp_zone->zone_name != "출발"){
					if (tmp_zone->owner == TURN){
						if (tmp_zone->hotel == EXIST)
							fine += 10;
						if (tmp_zone->building == EXIST)
							fine += 6;
						if (tmp_zone->villa == EXIST)
							fine += 3;
					}
					tmp_zone = tmp_zone->F_link;
				}

				if (fine > stat->money){
					gotoxy(55, 24);	printf("수리비 %d만원이 부족합니다.", fine);
					STATE = NOT_ENOUGH_MONEY;
					fine = 0;
					key_flag = EXIST;
					KEY_STATE = KEY18;
					break;
				}
				else
				{
					stat->money -= fine;
					MONEY_SHOW(user, user_set);
					gotoxy(55, 24);	printf("건물수리비로 %d만원을 지불하였습니다.", fine);
					fine = 0;
					if (TURN == P2_TURN) {
						gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
						pas = _getch();
						while (pas != ENTER);
						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);
					}
					else {
						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);
					}
					STATE = NEXT_TURN;
					key_flag = NULL;
					break;
				};
			}
			case KEY19:
			{
				stat->money += bal/10;
				gotoxy(55, 24);	printf("상금 %d만원을 받았습니다.",bal/10);
				MONEY_SHOW(user, user_set);
				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					pas = _getch();
					while (pas != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}
				STATE = NEXT_TURN;
				gk_CLR();
				break;
			}
			case KEY20:
			{
				sum = 0;
				tmp_zone = ZONE->head->F_link;
				max_zone = ZONE->head->F_link;

				while (tmp_zone->zone_name != "출발") {
					if (tmp_zone->owner == TURN) {
						sum += tmp_zone->zone_cost;
						if (tmp_zone->hotel == EXIST)
							sum += tmp_zone->hotel_cost;
						if (tmp_zone->building == EXIST)
							sum += tmp_zone->building_cost;
						if (tmp_zone->villa == EXIST)
							sum += tmp_zone->villa_cost;

						if (sum > max) {
							max = sum;
							max_zone = tmp_zone;
						}
						sum = 0;
					}
					tmp_zone = tmp_zone->F_link;
				}
				if (max == 0)
				{
					gotoxy(55, 24);	printf("보유한 땅이 없습니다.");
					if (TURN == P2_TURN) {
						gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
						pas = _getch();
						while (pas != ENTER);
						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);
					}
					else {
						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);
					}
					STATE = NEXT_TURN;
					max = 0;
					sum = 0;
					break;
				}
				else
				{
					max_zone->owner = NULL;
					max_zone->hotel = NULL;
					max_zone->building = NULL;
					max_zone->villa = NULL;
					stat->money += (max / 2);

					//지역 이름 초기화
					gotoxy(max_zone->zone_X + 2, max_zone->zone_Y - 1);
					printf("%s", max_zone->zone_name);
					//지역 건물 초기화
					if (strlen(max_zone->zone_name) == 4) //두 글자
						gotoxy(max_zone->zone_X - 4, max_zone->zone_Y + 2);
					else if (strlen(max_zone->zone_name) == 6) //세 글자
						gotoxy(max_zone->zone_X - 3, max_zone->zone_Y + 2);
					else
						gotoxy(max_zone->zone_X - 2, max_zone->zone_Y + 2);
					printf("              ");

					MONEY_SHOW(user, user_set);
					gotoxy(55, 24);
					printf("%s지역을 매각하였습니다.", max_zone->zone_name);
					if (TURN == P2_TURN) {
						gotoxy(55, 25);
						printf("실제책정값 : %d만원, 반액매각금액 : %d만원", max, max/2);
						gotoxy(55, 26);
						printf("다음과 같은 금액을 받았습니다 : %d 만원", max/2);
					}
					gotoxy(55, 27);
					if (TURN == P2_TURN) {
						gotoxy(55, 27);	printf("ENTER를 입력해주세요.");
						pas = _getch();
						while (pas != ENTER);
						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);
					}
					else {
						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);
					}
					STATE = NEXT_TURN;
					max = 0;
					sum = 0;
					break;
				}
			}
			case KEY21:
			{
				stat->pre_X = stat->location->zone_X;
				stat->pre_Y = stat->location->zone_Y;
				while (stat->location->zone_name != "서울")
					stat->location = stat->location->F_link;
				MOVING_init(stat, TURN);
				STATE = re_map;
				break;
			}
			case KEY22:
			{
				tmp_zone = ZONE->head->F_link;

				while (tmp_zone->zone_name != "출발"){
					if (tmp_zone->owner == TURN){
						if (tmp_zone->hotel == EXIST)
							fine += 15;
						if (tmp_zone->building == EXIST)
							fine += 10;
						if (tmp_zone->villa == EXIST)
							fine += 3;
					}
					tmp_zone = tmp_zone->F_link;
				}

				if (fine > stat->money)
				{
					gotoxy(55, 24);	printf("소득세 %d만원 부족합니다.", fine);
					STATE = NOT_ENOUGH_MONEY;
					fine = 0;
					key_flag = EXIST;
					KEY_STATE = KEY18;
					break;
				}
				else
				{
					stat->money -= fine;
					MONEY_SHOW(user, user_set);
					gotoxy(55, 24);	printf("소득세로 %d만원을 지불하였습니다.", fine);
					fine = 0;
					if (TURN == P2_TURN) {
						gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
						pas = _getch();
						while (pas != ENTER);
						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);
					}
					else {
						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);
					}
					STATE = NEXT_TURN;
					key_flag = NULL;
					break;
				};
			}
			case KEY23:
			{
				stat->spaceship = EXIST;
				dice1 = -1;
				gotoxy(stat->location->zone_X + (3 * TURN) - 4, stat->location->zone_Y);
				printf("  ");
				if (TURN == P1_TURN)
				{
					gotoxy(138, 3); Red1; printf("①");
					White1;
				}
				else if (TURN == P2_TURN)
				{
					gotoxy(140, 3); Gold1; printf("②");
					White1;
				}
				else if (TURN == P3_TURN)
				{
					gotoxy(142, 3); Sky1; printf("③");
					White1;
				}
				else if (TURN == P4_TURN)
				{
					gotoxy(144, 3); Green1; printf("④");
					White1;
				}

				while (stat->location->zone_name != "우주여행")
					stat->location = stat->location->F_link;
				STATE = NEXT_TURN;
				break;
			}
			case KEY24:
			{
				int sel_p;

				if (TURN == P2_TURN) {
					gotoxy(55, 24);
					printf("공격할 플레이어를 입력하세요: ");
					sel_p = _getch();

					_itoa(sel_p, sel_p_buf, 10);
					send(cs, sel_p_buf, strlen(sel_p_buf), 0);

					if (sel_p < 49 || sel_p>48 + gameover_cnt) {
						gotoxy(55, 24);
						printf("                              ");
						gotoxy(55, 24);
						printf("올바른 플레이어를 입력하세요");
						STATE = KEY24;
						break;
					}
				}
				else {
					nRcv = recv(cs, sel_p_buf, sizeof(sel_p_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					sel_p_buf[nRcv] = '\0';
					sel_p = atoi(sel_p_buf);
				}

				if (TURN == P2_TURN) {
					gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
					pas = _getch();
					while (pas != ENTER);
					_itoa(pas, ENTER_buf, 10);
					send(cs, ENTER_buf, strlen(ENTER_buf), 0);
				}
				else {
					nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
					if (nRcv == -1) {
						printf("값을 받지 못하였습니다.");
						_getch();
						system("cls");
						return;
					}
					ENTER_buf[nRcv] = '\0';
					pas = atoi(ENTER_buf);
					while (pas != ENTER);
				}

				MENU_CLR();
				sum = 0;
				tmp_zone = ZONE->head->F_link;
				max_zone = ZONE->head->F_link;

				while (tmp_zone->zone_name != "출발"){
					if (tmp_zone->owner == sel_p-48){
						sum += tmp_zone->zone_cost;
						if (tmp_zone->hotel == EXIST)
							sum += tmp_zone->hotel_cost;
						if (tmp_zone->building == EXIST)
							sum += tmp_zone->building_cost;
						if (tmp_zone->villa == EXIST)
							sum += tmp_zone->villa_cost;

						if (sum > max){
							max = sum;
							max_zone = tmp_zone;
						}
						sum = 0;
					}
					tmp_zone = tmp_zone->F_link;
				}
				if (max == 0){
					gotoxy(55, 24);	printf("보유한 땅이 없습니다.");
					if (TURN == P2_TURN) {
						gotoxy(55, 25);	printf("ENTER를 입력해주세요.");
						pas = _getch();
						while (pas != ENTER);
						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);
					}
					else {
						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);
					}
					STATE = NEXT_TURN;
					max = 0;
					sum = 0;
					break;
				}
				else
				{
					max_zone->owner = NULL;
					max_zone->hotel = NULL;
					max_zone->building = NULL;
					max_zone->villa = NULL;
					stat->money += (max / 2);

					if (max_zone->zone_name == sizeof(4)) {
						gotoxy(max_zone->zone_X + 4, max_zone->zone_Y - 1);
						printf("%s", max_zone->zone_name);
						gotoxy(max_zone->zone_X + 4, max_zone->zone_Y + 1);
						printf("       ");
						gotoxy(max_zone->zone_X + 4, max_zone->zone_Y + 2);
						printf("       ");
					}
					else if (max_zone->zone_name == sizeof(6)) {
						gotoxy(max_zone->zone_X + 3, max_zone->zone_Y - 1);
							printf("%s", max_zone->zone_name);
							gotoxy(max_zone->zone_X + 3, max_zone->zone_Y + 1);
							printf("       ");
							gotoxy(max_zone->zone_X + 3, max_zone->zone_Y + 2);
							printf("       ");
					}
					else {
						gotoxy(max_zone->zone_X + 2, max_zone->zone_Y - 1);
						printf("%s", max_zone->zone_name);
						gotoxy(max_zone->zone_X + 2, max_zone->zone_Y + 1);
						printf("       ");
						gotoxy(max_zone->zone_X + 2, max_zone->zone_Y + 2);
						printf("       ");
					}
		
					MONEY_SHOW(user, user_set);
					gotoxy(55, 24);
					printf("%s지역을 매각하였습니다.", max_zone->zone_name);
					
					if (TURN == P1_TURN) {
						gotoxy(55, 25);
						printf("실제책정값 : %d만원, 반액매각금액 : %d만원", max, max/2);
						gotoxy(55, 26);
						printf("다음과 같은 금액을 받았습니다 : %d 만원", max/2);
					}

					gotoxy(55, 27);
					if (TURN == P2_TURN) {
						gotoxy(55, 27);	printf("ENTER를 입력해주세요.");
						pas = _getch();
						while (pas != ENTER);
						_itoa(pas, ENTER_buf, 10);
						send(cs, ENTER_buf, strlen(ENTER_buf), 0);
					}
					else {
						nRcv = recv(cs, ENTER_buf, sizeof(ENTER_buf) - 1, 0);
						if (nRcv == -1) {
							printf("값을 받지 못하였습니다.");
							_getch();
							system("cls");
							return;
						}
						ENTER_buf[nRcv] = '\0';
						pas = atoi(ENTER_buf);
						while (pas != ENTER);
					}
					STATE = NEXT_TURN;
					max = 0;
					sum = 0;
					break;
				}
			}
		case GAME_OVER:
		{
			system("cls");
			FMOD_Channel_Stop(channel[0]);
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[9], 0, &channel[0]); // 게임오버

			system("mode con cols=100 lines=30 | title 부르마블 Client");

			if (COLOR_WIN != NULL) { //컬러독점 승리
				if (TURN == PLAYER1)
				{
					White1;
					gotoxy(31, 10);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(31, 11);	printf("┃ 　　 　 ★ 컬러 독점 게임 종료 ★ 　 　　┃\n");
					gotoxy(31, 12);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
					Red1;
					gotoxy(26, 13);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(26, 14);	printf("┃ 　　　　　　Player 1가 승리하였습니다.　 　　　　┃\n");
					gotoxy(26, 15);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
				}
				else if (TURN == PLAYER2)
				{
					White1;
					gotoxy(31, 10);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(31, 11);	printf("┃ 　　 　 ★ 컬러 독점 게임 종료 ★ 　 　　┃\n");
					gotoxy(31, 12);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
					Gold1;
					gotoxy(26, 13);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(26, 14);	printf("┃ 　　　　　　Player 2가 승리하였습니다.　 　　　　┃\n");
					gotoxy(26, 15);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
				}
				Green1;
				gotoxy(38, 22);	printf("ENTER 입력시 종료됩니다..");
				while (_getch() != ENTER) {
					STATE = GAMEOVER;
				}
			}
			else if (LINE_WIN != NULL) { //라인독점 승리
				if (TURN == PLAYER1)
				{
					White1;
					gotoxy(31, 10);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(31, 11);	printf("┃ 　　　  ★ 라인 독점 게임 종료 ★  　　　┃\n");
					gotoxy(31, 12);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
					Red1;
					gotoxy(26, 13);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(26, 14);	printf("┃ 　　　　　　Player 1가 승리하였습니다.　 　　　　┃\n");
					gotoxy(26, 15);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
				}
				else if (TURN == PLAYER2)
				{
					White1;
					gotoxy(31, 10);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(31, 11);	printf("┃ 　　　  ★ 라인 독점 게임 종료 ★  　　　┃\n");
					gotoxy(31, 12);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
					Gold1;
					gotoxy(26, 13);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(26, 14);	printf("┃ 　　　　　　Player 2가 승리하였습니다.　 　　　　┃\n");
					gotoxy(26, 15);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
				}
				Green1;
				gotoxy(38, 22);	printf("ENTER 입력시 종료됩니다..");
				while (_getch() != ENTER) {
					STATE = GAMEOVER;
				}
			}
			else {
				for (TURN = 1; TURN <= user_set; TURN++) {
					if ((user + TURN - 1)->gameover != GAMEOVER)
						break;
				}

				if (TURN == PLAYER1)
				{
					White1;
					gotoxy(31, 10);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(31, 11);	printf("┃ 　　　      ★  게임 종료 ★       　　　┃\n");
					gotoxy(31, 12);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
					Red1;
					gotoxy(26, 13);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(26, 14);	printf("┃ 　　　　　　Player 1가 승리하였습니다.　 　　　　┃\n");
					gotoxy(26, 15);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
				}
				else if (TURN == PLAYER2)
				{
					White1;
					gotoxy(31, 10);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(31, 11);	printf("┃ 　　　      ★  게임 종료 ★       　　　┃\n");
					gotoxy(31, 12);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
					Gold1;
					gotoxy(26, 13);	printf("┏〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┓\n");
					gotoxy(26, 14);	printf("┃ 　　　　　　Player 2가 승리하였습니다.　 　　　　┃\n");
					gotoxy(26, 15);	printf("┗〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┛\n");
				}

				Green1;
				gotoxy(38, 22);	printf("ENTER 입력시 종료됩니다..");

				while (_getch() != ENTER) {
					STATE = GAMEOVER;
				}
			}
			STATE = GAMEOVER;
			break;
		}

		case GAMEOVER:
		{
			system("cls");
			return 0;
			break;
		}

			default:
				break;	
		}
	}
}