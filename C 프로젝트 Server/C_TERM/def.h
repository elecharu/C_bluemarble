#pragma once
#define COLOR GetStdHandle(STD_OUTPUT_HANDLE)

#define Blue2 SetConsoleTextAttribute(COLOR,0x0010) //파란색 //RGB는 정의되있지만 배경색과 통일하려고
#define Green2 SetConsoleTextAttribute(COLOR,0x0020) //초록색 
#define Sky SetConsoleTextAttribute(COLOR,0x0030) //하늘색
#define Red2 SetConsoleTextAttribute(COLOR,0x0040) //빨간색
#define Purple SetConsoleTextAttribute(COLOR,0x0050) //보라색
#define Gold SetConsoleTextAttribute(COLOR,0x0060) //노란색
#define Gray SetConsoleTextAttribute(COLOR,0x0080) //회색
#define SK SetConsoleTextAttribute(COLOR,0x00E0) //살색
#define Violet SetConsoleTextAttribute(COLOR,0x00D0) //보라색
#define LRed SetConsoleTextAttribute(COLOR,0x00C0) //주홍색
#define White SetConsoleTextAttribute(COLOR,0x00F0) //하얀색
#define CLR SetConsoleTextAttribute(COLOR,0x000F) //검은배경, 흰폰트

#define Blue1 SetConsoleTextAttribute(COLOR,0x0001) //파란색
#define Green1 SetConsoleTextAttribute(COLOR,0x0002) //초록색
#define Sky1 SetConsoleTextAttribute(COLOR,0x0003) //하늘색
#define Red1 SetConsoleTextAttribute(COLOR,0x0004) //빨간색
#define Purple1 SetConsoleTextAttribute(COLOR,0x0005) //보라색
#define Gold1 SetConsoleTextAttribute(COLOR,0x0006) //노란색
#define Gray1 SetConsoleTextAttribute(COLOR,0x0008) //회색
#define SK1 SetConsoleTextAttribute(COLOR,0x000E) //살색
#define Violet1 SetConsoleTextAttribute(COLOR,0x000D) //보라색
#define LRed1 SetConsoleTextAttribute(COLOR,0x000C) //주홍색
#define White1 SetConsoleTextAttribute(COLOR,0x000F) //하얀색

#define UP 72
#define DOWN 80 
#define LEFT 75 
#define RIGHT 77
#define ENTER 13
#define ESC 27
#define ERR "99"

#define P1_TURN 1
#define P2_TURN 2
#define P3_TURN 3
#define P4_TURN 4

#define PLAYER1 1
#define PLAYER2 2
#define PLAYER3 3
#define PLAYER4 4

#define LINE1 77
#define LINE2 78
#define LINE3 79
#define LINE4 80
#define LINE_WARN 81


#define START 998
#define EXIT 999
#define DATA 1000

#define EXIST 10
#define NON_EXIST 20
#define SELL_X 169
#define SELL_Y 0
#define GAMEOVER -1

#define ODD 1
#define EVEN 2

//0010 blue
// 0020 green
// 0030 sky
// 0040 red
// 0x0050 purple
//0060 gold
// 0070 white_gray
//00A0 LIGHT_GREEN
// 00C0 다홍색
// 00D0 바이올렛?
//00E0 살색
//00F0 흰색