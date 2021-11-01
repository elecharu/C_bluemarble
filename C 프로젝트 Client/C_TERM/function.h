//#pragma once
#include "def.h"

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

//////////////	¸Ê »çÀÌÁî	//////////////
void game_size() {
	system("mode con cols=198 lines=53 | title ºÎ¸£¸¶ºí Client");
}
void info_size() {
	system("mode con cols=100 lines=33 | title ºÎ¸£¸¶ºí Client");
}
void intro_size() {
	system("mode con cols=161 lines=53 | title ºÎ¸£¸¶ºí Client");
}

//////////////	±×¸®±â	////////////////
void draw_map();
void setMapcolor(int i);
int draw_intro(int state);
int infor();
///ÀÎÆ®·Î

char* intro[23] = {
		{"                ¡á¡á        ¡á¡á                                                                           ¡á¡á                 ¡á¡á        ¡á¡á      "},
		{"                ¡á¡á        ¡á¡á                                                                           ¡á¡á                 ¡á¡á        ¡á¡á       "},
		{"                ¡á¡á¡á¡á¡á¡á¡á¡á                     ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á                                  ¡á¡á                 ¡á¡á¡á¡á¡á¡á¡á¡á       "},
		{"                ¡á¡á¡á¡á¡á¡á¡á¡á                     ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á            ¡á¡á¡á¡á¡á¡á¡á¡á      ¡á¡á                 ¡á¡á¡á¡á¡á¡á¡á¡á       "},
		{"                ¡á¡á        ¡á¡á                                     ¡á¡á            ¡á¡á¡á¡á¡á¡á¡á¡á      ¡á¡á                 ¡á¡á        ¡á¡á       "},
		{"                ¡á¡á        ¡á¡á                                     ¡á¡á            ¡á¡á        ¡á¡á      ¡á¡á                 ¡á¡á        ¡á¡á       "},
		{"                ¡á¡á¡á¡á¡á¡á¡á¡á                     ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á            ¡á¡á        ¡á¡á      ¡á¡á¡á¡á¡á¡á         ¡á¡á¡á¡á¡á¡á¡á¡á       "},
		{"                ¡á¡á¡á¡á¡á¡á¡á¡á                     ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á            ¡á¡á        ¡á¡á      ¡á¡á¡á¡á¡á¡á         ¡á¡á¡á¡á¡á¡á¡á¡á       "},
		{"                                                     ¡á¡á                            ¡á¡á        ¡á¡á      ¡á¡á                                          "},
		{"                                                     ¡á¡á                            ¡á¡á¡á¡á¡á¡á¡á¡á      ¡á¡á                                          "},
		{"      ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á           ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á            ¡á¡á¡á¡á¡á¡á¡á¡á      ¡á¡á      ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á"},
		{"      ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á           ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á                                  ¡á¡á      ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á"},
		{"                      ¡á¡á                                                                                 ¡á¡á                                        "},
		{"                      ¡á¡á                                                                                 ¡á¡á               ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á         "},
		{"                      ¡á¡á                                                                                                    ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á         "},
		{"                      ¡á¡á                   ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á                                                             ¡á¡á         "},
		{"                      ¡á¡á                   ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á                                                             ¡á¡á         "},
		{"                      ¡á¡á                                                                                                    ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á         "},
		{"                                                                                                                              ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á         "},
		{"                                                                                                                              ¡á¡á                         "},
		{"                                                                                                                              ¡á¡á                         "},
		{"                                                                                                                              ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á         "},
		{"                                                                                                                              ¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á         "},
};
/// Áöµµ
/* ¦¢ Ãß°¡¹öÀü */ //56ÁÙ
/*
char* zone[49] = {
		{"¦£¦¡¦¡¦¡¦¡¦¡  07 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  08 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  09 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  10 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  11 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  12 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  13 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  14 ¦¡¦¡¦¡¦¡¦¡¦¤¦¢"},
		{"¦¢     ¹«ÀÎµµ    ¦¢     ¿À»çÄ«    ¦¢     ½Ãµå´Ï    ¦¢      È«Äá     ¦¢    È²±Ý¿­¼è   ¦¢     ½ÃÄ«°í    ¦¢      ºÎ»ê     ¦¢    ¿ìÁÖ¿©Çà   ¦¢¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  06 ¦¡¦¡¦¡¦¡¦¡¦©¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦«¦¡¦¡¦¡¦¡¦¡  15 ¦¡¦¡¦¡¦¡¦¡¦©¦¢"},
		{"¦¢     Ä«ÀÌ·Î    ¦¢                                                                                               ¦¢    ¸ð½ºÅ©¹Ù   ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  05 ¦¡¦¡¦¡¦¡¦¡¦©                                                                                               ¦§¦¡¦¡¦¡¦¡¦¡  16 ¦¡¦¡¦¡¦¡¦¡¦©¦¢"},
		{"¦¢     µÎ¹ÙÀÌ    ¦¢                                                                                               ¦¢     Åä·ÐÅä    ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  04 ¦¡¦¡¦¡¦¡¦¡¦©                                                                                               ¦§¦¡¦¡¦¡¦¡¦¡  17 ¦¡¦¡¦¡¦¡¦¡¦©¦¢"},
		{"¦¢    Å¸ÀÌº£ÀÌ   ¦¢                                                                                               ¦¢    È²±Ý¿­¼è   ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  03 ¦¡¦¡¦¡¦¡¦¡¦©                                                                                               ¦§¦¡¦¡¦¡¦¡¦¡  18 ¦¡¦¡¦¡¦¡¦¡¦©¦¢"},
		{"¦¢    È²±Ý¿­¼è   ¦¢                                                                                               ¦¢     ¸®½ºº»    ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  02 ¦¡¦¡¦¡¦¡¦¡¦©                                                                                               ¦§¦¡¦¡¦¡¦¡¦¡  19 ¦¡¦¡¦¡¦¡¦¡¦©¦¢"},
		{"¦¢     º£ÀÌÂ¡    ¦¢                                                                                               ¦¢    ¸¶µå¸®µå   ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  01 ¦¡¦¡¦¡¦¡¦¡¦©                                                                                               ¦§¦¡¦¡¦¡¦¡¦¡  20 ¦¡¦¡¦¡¦¡¦¡¦©¦¢"},
		{"¦¢      ¹æÄÛ     ¦¢                                                                                               ¦¢      ·Î¸¶     ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  00 ¦¡¦¡¦¡¦¡¦¡¦«¦¡¦¡¦¡¦¡¦¡  27 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  26 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  25 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  24 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  23 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  22 ¦¡¦¡¦¡¦¡¦¡¦«¦¡¦¡¦¡¦¡¦¡  21 ¦¡¦¡¦¡¦¡¦¡¦©¦¢"},
		{"¦¢     START     ¦¢      ¼­¿ï     ¦¢      ´º¿å     ¦¢    È²±Ý¿­¼è   ¦¢      ·±´ø     ¦¢      ÆÄ¸®     ¦¢     º£¸¦¸°    ¦¢    È¦Â¦°ÔÀÓ   ¦¢¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢¦¢"},
		{"¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥¦¢"},

};*/
/* ¦¢»èÁ¦¹öÀü */ //56ÁÙ
char* zone[49] = {
		{"¦£¦¡¦¡¦¡¦¡¦¡  07 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  08 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  09 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  10 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  11 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  12 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  13 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  14 ¦¡¦¡¦¡¦¡¦¡¦¤"},
		{"¦¢     ¹«ÀÎµµ    ¦¢     ¿À»çÄ«    ¦¢     ½Ãµå´Ï    ¦¢      È«Äá     ¦¢    È²±Ý¿­¼è   ¦¢     ½ÃÄ«°í    ¦¢      ºÎ»ê     ¦¢    ¿ìÁÖ¿©Çà   ¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  06 ¦¡¦¡¦¡¦¡¦¡¦©¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦«¦¡¦¡¦¡¦¡¦¡  15 ¦¡¦¡¦¡¦¡¦¡¦©"},
		{"¦¢     Ä«ÀÌ·Î    ¦¢                                                                                               ¦¢    ¸ð½ºÅ©¹Ù   ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  05 ¦¡¦¡¦¡¦¡¦¡¦©                                                                                               ¦§¦¡¦¡¦¡¦¡¦¡  16 ¦¡¦¡¦¡¦¡¦¡¦©"},
		{"¦¢     µÎ¹ÙÀÌ    ¦¢                                                                                               ¦¢     Åä·ÐÅä    ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  04 ¦¡¦¡¦¡¦¡¦¡¦©                                                                                               ¦§¦¡¦¡¦¡¦¡¦¡  17 ¦¡¦¡¦¡¦¡¦¡¦©"},
		{"¦¢    Å¸ÀÌº£ÀÌ   ¦¢                                                                                               ¦¢    È²±Ý¿­¼è   ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  03 ¦¡¦¡¦¡¦¡¦¡¦©                                                                                               ¦§¦¡¦¡¦¡¦¡¦¡  18 ¦¡¦¡¦¡¦¡¦¡¦©"},
		{"¦¢    È²±Ý¿­¼è   ¦¢                                                                                               ¦¢     ¸®½ºº»    ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  02 ¦¡¦¡¦¡¦¡¦¡¦©                                                                                               ¦§¦¡¦¡¦¡¦¡¦¡  19 ¦¡¦¡¦¡¦¡¦¡¦©"},
		{"¦¢     º£ÀÌÂ¡    ¦¢                                                                                               ¦¢    ¸¶µå¸®µå   ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  01 ¦¡¦¡¦¡¦¡¦¡¦©                                                                                               ¦§¦¡¦¡¦¡¦¡¦¡  20 ¦¡¦¡¦¡¦¡¦¡¦©"},
		{"¦¢      ¹æÄÛ     ¦¢                                                                                               ¦¢      ·Î¸¶     ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦¢               ¦¢                                                                                               ¦¢               ¦¢"},
		{"¦§¦¡¦¡¦¡¦¡¦¡  00 ¦¡¦¡¦¡¦¡¦¡¦«¦¡¦¡¦¡¦¡¦¡  27 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  26 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  25 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  24 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  23 ¦¡¦¡¦¡¦¡¦¡¦¨¦¡¦¡¦¡¦¡¦¡  22 ¦¡¦¡¦¡¦¡¦¡¦«¦¡¦¡¦¡¦¡¦¡  21 ¦¡¦¡¦¡¦¡¦¡¦©"},
		{"¦¢      Ãâ¹ß     ¦¢      ¼­¿ï     ¦¢      ´º¿å     ¦¢    È²±Ý¿­¼è   ¦¢      ·±´ø     ¦¢      ÆÄ¸®     ¦¢     º£¸¦¸°    ¦¢    È¦Â¦°ÔÀÓ   ¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢"},
		{"¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢               ¦¢"},
		{"¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦ª¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥"},

};
int draw_intro(int state) {
	system("cls");
	int x = 77;		//xÀÇ ½ÃÀÛÀ§Ä¡
	int y = 38;		//yÀÇ ½ÃÀÛÀ§Ä¡
	int loc_y = y;  //yÀÇ ¿ø·¡À§Ä¡
	char select = 0;
	int start_flag = START;
	CLR;
	gotoxy(77, 38);	printf("°Ô ÀÓ ½Ã ÀÛ");
	//gotoxy(77, 41);	printf("°Ô ÀÓ Á¾ ·á");
	gotoxy(77, 44);	printf("°Ô ÀÓ Á¤ º¸");
	gotoxy(74, 38);	printf("¢º");
	gotoxy(180, 60);
	// Ä­À» 3°³ ¸¸µé°í ½ÍÀ¸¸é x, y ÀÇ °ªÀÌ 3¾¿ Â÷ÀÌ³­ ¤ÓÂü°í

	while (1) {
		if (_kbhit())
			select = _getch();
		switch (select) {
		case UP:
			CLR;
			if (y == loc_y) {
				gotoxy(x - 3, y);
				printf("  ");
				y += 3;					//Ä­À» 3Ä­ ¸¸µé°í ½ÍÀ¸¸é ¿©±â´Ù°¡ 6
				gotoxy(x - 3, y);
				printf("¢º");
			}
			else {
				gotoxy(x - 3, y);
				printf("  ");
				y -= 3;
				gotoxy(x - 3, y);
				printf("¢º");
			}
			select = 0;
			break;
		case DOWN:
			CLR;
			if (y == loc_y + 6) {
				gotoxy(x - 3, y);
				printf("  ");
				y -= 3;					//Ä­À» 3Ä­ ¸¸µé°í ½ÍÀ¸¸é ¿©±â´Ù°¡ 6
				gotoxy(x - 3, y);
				printf("¢º");
			}
			else {
				gotoxy(x - 3, y);
				printf("  ");
				y += 3;
				gotoxy(x - 3, y);
				printf("¢º");
			}
			select = 0;
			break;
		case ENTER:
			if (y == loc_y)
				start_flag = START;
			else if (y == loc_y + 3)
				start_flag = EXIT;
			else
				start_flag = DATA;
			return start_flag;
			break;
		default:
			for (int i = 0; i < 23; i++) {
				if (i % 4 == 0) {
					switch (state) {
					case 0:
						state = 1;
						Red1;
						break;
					case 1:
						state = 2;
						Gold1;
						break;
					case 2:
						state = 3;
						Red1;
						break;
					case 3:
						state = 4;
						Green1;
						break;
					default:
						state = 1;
						Violet1;
						break;
					}
				}
				gotoxy(0, i + 5);
				printf("%s", intro[i]); //¸Ê Ãâ·Â
			}
		}
		Sleep(150);
	}
}


void draw_map() {
	CLR;
	for (int i = 0; i < 49; i++) {
		gotoxy(1, i);
		printf("%s", zone[i]); //¸Ê Ãâ·Â
		setMapcolor(i);
	}
	Green1;
	for (int i = SELL_Y; i <= 31; i++) {
		gotoxy(SELL_X, i);
		if (i == SELL_Y)
			printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		else if (i == 31)
			printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
		else
			printf("¦­                        ¦­");
	}

	Green1;
	gotoxy(141, 0);	printf("¡ã");
	gotoxy(137, 1);	printf("¢¸¡á¡á¡á¢º");
	gotoxy(135, 2);	printf("¢¸¡á¡á¡á¡á¡á¢º");
	gotoxy(132, 3);	printf("¢¸¡á¡á        ¡á¡á¢º");
	gotoxy(135, 4); printf("¢¸¡á¡á¡á¡á¡á¢º");
	gotoxy(137, 5); printf("¢¸¡á¡á¡á¢º");
	gotoxy(141, 6); printf("¡å");
	White1;
}

void setMapcolor(int i) {
	if (i == 5) {
		Sky;
		gotoxy(19, i); //¿À»çÄ«
		printf("              ");
		gotoxy(35, i); //½Ãµå´Ï
		printf("              ");
		gotoxy(51, i); //È«Äá
		printf("              ");
		Blue2;
		gotoxy(83, i); //½ÃÄ«°í
		printf("              ");
		gotoxy(99, i); //ºÎ»ê
		printf("              ");
		CLR;
	}
	if (i == 11 || i == 17 || i == 23) { //Ä«ÀÌ·Î , µÎ¹ÙÀÌ, Å¸ÀÌº£ÀÌ
		White;
		gotoxy(3, i);
		printf("              ");
		if (i == 11 || i == 17) { // ¸ð½ºÅ©¹Ù, Åä·ÐÅä
			Violet;
			gotoxy(115, i);
			printf("              ");
		}
		CLR;
	}
	if (i == 29 || i == 35 || i == 41) { //¸®½ºº», ¸¶µå¸®µå, ·Î¸¶
		Purple;
		gotoxy(115, i);
		printf("              ");
		if (i == 35 || i == 41) { // º£ÀÌÂ¡, ¹æÄÛ
			Gray;
			gotoxy(3, i);
			printf("              ");
		}
		CLR;
	}
	if (i == 47) {
		Red2;
		gotoxy(19, i); //¼­¿ï
		printf("              ");
		gotoxy(35, i); //´º¿å
		printf("              ");
		LRed;
		gotoxy(67, i); //·±´ø
		printf("              ");
		gotoxy(83, i); //ÆÄ¸®
		printf("              ");
		gotoxy(99, i); //º£¸¦¸°
		printf("              ");
		CLR;
	}
}
int infor() {
	system("cls");
	CLR;
	system("mode con cols=110 lines=20 | title ºÎ¸£¸¶ºí Client");
	printf("\n\n\n");
	printf("¡¡¡¡¡¡    ¶¥À» ±¸ÀÔÇÏ°í °Ç¹°À» °Ç¼³ÇÏ¿© »ó´ë¸¦ ÆÄ»ê½ÃÅ°°Å³ª ÄÃ·¯µ¶Á¡, ¶óÀÎµ¶Á¡À¸·Î ½Â¸®¸¦ ÀïÃëÇÏ¼¼¿ä!\n\n");
	printf("¡¡¡¡¡¡¼­¹ö ÇÁ·Î±×·¥Àº ÇÃ·¹ÀÌ¾î 1, Å¬¶óÀÌ¾ðÆ® ÇÁ·Î±×·¥Àº ÇÃ·¹ÀÌ¾î 2¸¦ ÁöÁ¤¹ÞÀ¸¸ç ÀÌ´Â º¯°æÇÒ ¼ö ¾ø½À´Ï´Ù.\n\n");
	printf("¡¡¡¡¡¡    °Ç¹°Àº ÃÖ´ë 1ÅÏ¿¡ 1°³¾¿¸¸ °Ç¼³ÇÒ ¼ö ÀÖÀ¸¸ç °Ç¹°À» Áþ±â À§ÇØ¼­´Â ¶¥À» ¸ÕÀú ±¸ÀÔÇØ¾ßÇÕ´Ï´Ù.\n\n");
	printf("¡¡¡¡¡¡      È²±ÝÅ°¿¡´Â 24°¡ÁöÀÇ ±â´ÉµéÀÌ µé¾î°¡ÀÖÀ¸¸ç ÀÌ °ÔÀÓÀº ÁÖ»çÀ§ ´õºíÀÇ È½¼ö Á¦ÇÑÀÌ ¾ø½À´Ï´Ù.\n\n\n\n");
	printf("\n");
	printf("¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¿µÁøÀü¹®´ëÇÐ ÄÄÇ»ÅÍ Á¤º¸°è¿­ 2021_1ÇÐ±â_CÇÁ·Î±×·¡¹Ö ÅÒÇÁ·ÎÁ§Æ® 1Á¶\n");
	printf("¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡  Á¦ÀÛÀÚ: ÇÑ¼º¼ö, Àü¹ü¼ö, ±è¿µ¹Î, ÃÖ¼±È£, ÆÇÈË³ê\n\n\n");
	printf("¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¸ÞÀÎÈ­¸éÀ¸·Î µ¹¾Æ°¡±â À§ÇØ¼­´Â ESCÅ°¸¦ ÀÌ¿ëÇÏ¿© ÀÌµ¿ÇÒ ¼ö ÀÖ½À´Ï´Ù.\n");
	char temp = _getch();
	if (temp == ESC)
		return temp;
	else
		return 0;
}

/*ÁÖ»çÀ§ ºÎºÐ*/
int dice_rand() {
	int dice_tmp = 0;
	while (1) {
		dice_tmp = rand() % 6 + 1;
		if (dice_tmp != 0) {
			return dice_tmp;
		}
	}
}

//ÁÖ»çÀ§ ´« Ãâ·Â
void print_dice_num(int x, int y, int dice_num) {

	gotoxy(x, y++);
	White1;
	switch (dice_num) {
	case 1:
		printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¢     ¡Ü    ¦¢"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
		break;
	case 2:
		printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¢   ¡Ü  ¡Ü  ¦¢"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
		break;
	case 3:
		printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¢     ¡Ü    ¦¢"); gotoxy(x, y++);
		printf("¦¢     ¡Ü    ¦¢"); gotoxy(x, y++);
		printf("¦¢     ¡Ü    ¦¢"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
		break;
	case 4:
		printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¢   ¡Ü  ¡Ü  ¦¢"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¢   ¡Ü  ¡Ü  ¦¢"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
		break;
	case 5:
		printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¢   ¡Ü  ¡Ü  ¦¢"); gotoxy(x, y++);
		printf("¦¢     ¡Ü    ¦¢"); gotoxy(x, y++);
		printf("¦¢   ¡Ü  ¡Ü  ¦¢"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
		break;
	case 6:
		printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¢   ¡Ü  ¡Ü  ¦¢"); gotoxy(x, y++);
		printf("¦¢   ¡Ü  ¡Ü  ¦¢"); gotoxy(x, y++);
		printf("¦¢   ¡Ü  ¡Ü  ¦¢"); gotoxy(x, y++);
		printf("¦¢           ¦¢"); gotoxy(x, y++);
		printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
		break;
	default:
		break;
	}
	gotoxy(x, y++);
	printf("                              ");
	White1;
}
void print_dice(int dice1, int dice2) {
	print_dice_num(51, 23, dice1);
	print_dice_num(68, 23, dice2);
}

void dice_init(int* dice1, int* dice2) {
	*dice1 = *dice2 = 0;
}

void casting_dice(int* dice1, int* dice2, int* dice_sum, int* OE_KEY, int* OE, int use) {
	if (*OE == EXIST && use == 1) {
		if (*OE_KEY % 2 == ODD) {
			do {
				*dice1 = rand() % 6 + 1;
				*dice2 = rand() % 6 + 1;
				*dice_sum = *dice1 + *dice2;
			} while ((*dice_sum % 2) != 1);
			*OE = NON_EXIST;
		}
		else {
			do {
				*dice1 = rand() % 6 + 1;
				*dice2 = rand() % 6 + 1;
				*dice_sum = *dice1 + *dice2;
			} while ((*dice_sum % 2) != 0);
			*OE = NON_EXIST;
		}
	}
	else {
		dice_init(dice1, dice2);

		*dice1 = rand() % 6 + 1;
		*dice2 = rand() % 6 + 1;
		*dice_sum = *dice1 + *dice2;
	}
	print_dice(*dice1, *dice2);

	if (*dice1 == *dice2) {
		gotoxy(40, 35);
		printf("´õºíÀÔ´Ï´Ù! ÁÖ»çÀ§¸¦ ±¼¸± ±âÈ¸°¡ ÇÑ¹ø ´õ ÁÖ¾îÁý´Ï´Ù.");
	}
}
/* ¹Ì´Ï°ÔÀÓ ÁÖ»çÀ§ */
int mini() {
	print_dice(dice_rand(), dice_rand());
	int dice1 = rand() % 6 + 1;
	int dice2 = rand() % 6 + 1;
	int dice_sum = dice1 + dice2;
	print_dice(dice1, dice2);
	return dice_sum;
}
/* ¸» ÀÌµ¿ ÇÔ¼ö °ü·Ã*/
void MOVING_init(player* player, int turn) {

	gotoxy(player->pre_X + (3 * turn) - 4, player->pre_Y); printf("   ");
	gotoxy(player->location->zone_X + (3 * turn) - 4, player->location->zone_Y);

	if (turn == 1) {
		Red1;
		printf("¨ç");
	}
	else if (turn == 2) {
		Gold1;
		printf("¨è");
	}
	else if (turn == 3) {
		Sky1;
		printf("¨é");
	}
	else if (turn == 4) {
		Green1;
		printf("¨ê");
	}
	White1;
}

/* º¸À¯ ¾ÆÀÌÅÛ */

void MONEY_SHOW(player* player, int user_set) {
	gotoxy(138, 12); Violet1;
	printf("°¢ ÇÃ·¹ÀÌ¾îÀÇ º¸À¯ ¾ÆÀÌÅÛ");
	gotoxy(138, 44);
	printf("                     ");
	gotoxy(138, 43);
	printf("°¢ ÇÃ·¹ÀÌ¾îÀÇ ¼ÒÁö±Ý");
	for (int i = 0; i < user_set; i++) {
		switch (i)
		{
		case 0:
			Red1;
			break;
		case 1:
			Gold1;
			break;
		case 2:
			Sky1;
			break;
		case 3:
			Green1;
			break;
		default:
			break;
		}
		gotoxy(138, 44 + i);
		printf("                      ");
		gotoxy(138, 44 + i);
		if ((player + i)->gameover == GAMEOVER) {
			printf("ÇÃ·¹ÀÌ¾î%d : ÆÄ  »ê", i + 1);
			gotoxy(138, 13 + i);
			printf("                              ");
		}
		else {
			printf("ÇÃ·¹ÀÌ¾î%d : %d ¸¸¿ø", i + 1, (player + i)->money);
			gotoxy(138, 13 + i);
			printf("                              ");
			gotoxy(138, 13 + i);
			printf("ÇÃ·¹ÀÌ¾î%d : ", i + 1);
			if ((player + i)->passcard == EXIST)
				printf("¿ì´ë±Ç ");
			else if ((player + i)->escape == EXIST)
				printf("¹«ÀÎµµ Å»Ãâ±Ç");
			else if ((player + i)->OE == EXIST)
				printf("ÁÖ»çÀ§ È¦Â¦±Ç");
		}
	}
	White1;
}
/* ¸ðµç ¶¥ Ãâ·Â */

void ZONE_LIST_SHOW(zone_head* ZONE) {
	int x = SELL_X + 3, y = SELL_Y;
	zone_list* tmp = ZONE->head;

	gotoxy(x += 2, ++y);
	White1;
	printf(" * Áö¿ª ¸®½ºÆ® *");
	gotoxy(x += 2, ++y);

	do {
		if (tmp->owner == PLAYER1)
			Red1;
		else if (tmp->owner == PLAYER2)
			Gold1;
		else if (tmp->owner == PLAYER3)
			Sky1;
		else if (tmp->owner == PLAYER4)
			Green1;
		else if ((tmp->zone_name == "È²±Ý¿­¼è") | (tmp->zone_name == "Ãâ¹ß") | (tmp->zone_name == "È¦Â¦°ÔÀÓ") | (tmp->zone_name == "¹«ÀÎµµ") | (tmp->zone_name == "¿ìÁÖ¿©Çà"))
			SK1;
		else
			White1;
		printf("%2d.%s", tmp->zone_num, tmp->zone_name);
		gotoxy(x, ++y);

		tmp = tmp->F_link;
	} while (tmp->zone_name != "Ãâ¹ß");

}

int check_(zone_list* tmp, int TURN) {
	int cnt = 0;
	int gray_num = 0;
	int white_num = 0;
	int sky_num = 0;
	int blue_num = 0;
	int violet_num = 0;
	int purple_num = 0;
	int lred_num = 0;
	int red_num = 0;

	while (tmp->zone_name != "Ãâ¹ß") {
		if (tmp->owner == TURN) {
			if (tmp->zone_color == "gray")
				gray_num++;
			if (tmp->zone_color == "white")
				white_num++;
			if (tmp->zone_color == "sky")
				sky_num++;
			if (tmp->zone_color == "blue")
				blue_num++;
			if (tmp->zone_color == "violet")
				violet_num++;
			if (tmp->zone_color == "purple")
				purple_num++;
			if (tmp->zone_color == "lred")
				lred_num++;
			if (tmp->zone_color == "red")
				red_num++;
		}
		tmp = tmp->F_link;
	}
	if (gray_num == 2)
		cnt++;
	if (white_num == 3)
		cnt++;
	if (sky_num == 3)
		cnt++;
	if (blue_num == 2)
		cnt++;
	if (violet_num == 2)
		cnt++;
	if (purple_num == 3)
		cnt++;
	if (lred_num == 3)
		cnt++;
	if (red_num == 2)
		cnt++;

	if (gray_num == 2 && white_num == 3)
		return LINE1;
	else if (blue_num == 2 && sky_num == 3)
		return LINE2;
	else if (violet_num == 2 && purple_num == 3)
		return LINE3;
	else if (red_num == 2 && lred_num == 3)
		return LINE4;

	return cnt;
}
/* °Ç¹° */

void STRUCTURE_DRAW(zone_list* Z, int S, int turn) {
	int x = Z->zone_X, y = Z->zone_Y;

	if (strlen(Z->zone_name) == 8)
		x += 2;
	if (strlen(Z->zone_name) == 6)
		x++;

	gotoxy(x, y += 2);
	if (turn == P1_TURN)
		Red1;
	else if (turn == P2_TURN)
		Gold1;
	else if (turn == P3_TURN)
		Sky1;
	else if (turn == P4_TURN)
		Green1;


	switch (S) {
	case 1:
		gotoxy(x, y);
		printf("¢Â");
		break;
	case 2:
		gotoxy(x + 3, y);
		printf("¢Á");
		break;
	case 3:
		gotoxy(x + 6, y);
		printf("¡â");
		break;
	}
	White1;
}

/* ¶¥ ±¸ÀÔ */
void BUY_ZONE(zone_list* Z, int turn) {

	gotoxy(Z->zone_X + 2, Z->zone_Y - 1);
	printf("      ");
	if (Z->hotel == EXIST) {
		STRUCTURE_DRAW(Z, 1, turn);
	}
	if (Z->building == EXIST) {
		STRUCTURE_DRAW(Z, 2, turn);
	}
	if (Z->villa == EXIST) {
		STRUCTURE_DRAW(Z, 3, turn);
	}

	if (turn == P1_TURN)
		Red1;
	else if (turn == P2_TURN)
		Gold1;
	else if (turn == P3_TURN)
		Sky1;
	else if (turn == P4_TURN)
		Green1;
	else
		White1;

	gotoxy(Z->zone_X + 2, Z->zone_Y - 1);
	printf("%s", Z->zone_name);
	White1;
}

/* ¶¥ ÆÇ¸Å */

int SELL_LIST(int PLAYER, zone_head* ZONE) {

	zone_list* tmp = ZONE->head->F_link;
	int x = SELL_X, y = SELL_Y;
	int gameover = 0;

	gotoxy(x += 2, ++y);
	printf("º¸À¯ ÁßÀÎ ¶¥&°Ç¹° °¡°Ý");
	x += 2;
	gotoxy(x, ++y);
	gameover = GAMEOVER;
	while (tmp->zone_name != "Ãâ¹ß")
	{
		if (tmp->owner == PLAYER)
		{
			gameover = 0;
			printf("%2d.", tmp->zone_num);
			printf("%s : %d¸¸¿ø", tmp->zone_name, tmp->zone_cost);
			++x;
			if (tmp->hotel == EXIST)
			{
				gotoxy(x, ++y);
				printf("  È£ÅÚ : %d¸¸¿ø", tmp->hotel_cost);
			}
			if (tmp->building == EXIST)
			{
				gotoxy(x, ++y);
				printf("  ºôµù : %d¸¸¿ø", tmp->building_cost);
			}
			if (tmp->villa == EXIST)
			{
				gotoxy(x, ++y);
				printf("  º°Àå : %d¸¸¿ø", tmp->villa_cost);
			}
			gotoxy(--x, ++y);
		}
		tmp = tmp->F_link;
	}
	return gameover;
}

/* È²±Ý¿­¼è */
void show_golden_key(golden_key* G)
{
	Gold1;
	gotoxy(21, 8);	printf("  ¡Ù¡Ù È²±Ý¿­¼è ¡Ù¡Ù");
	gotoxy(23, 9);	printf("%s", G->key_name);
	gotoxy(23, 10);	printf("%s", G->key_content);
	/*
	White1;;
	gotoxy(23, 12);	printf("ENTER¸¦ ÀÔ·ÂÇÏ¼¼¿ä.");
	while (_getch() != ENTER);
	*/
}

/* È­¸é Å¬¸®¾î */

void DICE_CLR(void) {
	for (int i = 22; i <= 31; i++) {
		gotoxy(29, i);
		printf("                                                      ");
	}
}

void MENU_CLR(void) {
	for (int i = 24; i <= 31; i++) {
		gotoxy(48, i);
		printf("                                                      ");
	}
}
void zone_NAME_CLR(zone_list* Z) {
	gotoxy(Z->zone_X, Z->zone_Y - 1);
	printf("     ");
}
void SELL_LIST_CLR(void) {
	int x = SELL_X + 1, y = SELL_Y;
	gotoxy(x, ++y);
	while (y < 31) {
		printf("                        ");
		gotoxy(x, ++y);
	}
}
void ZONE_LIST_SHOW_CLR(void) {
	int x = SELL_X + 3, y = SELL_Y;
	gotoxy(x, ++y);
	while (y < 31) {
		printf("              ");
		gotoxy(x, ++y);
	}
}
void gk_CLR(void) {

	for (int i = 8; i <= 12; i++) {
		if (i == 8) {
			gotoxy(21, i);
			printf("                                                                                          ");
		}
		else {
			gotoxy(23, i);
			printf("                                                                                          ");
		}
	}
}

void island_CLR() {
	for (int i = 18; i <= 21; i++) {
		gotoxy(48, i);
		printf("                                     ");
	}
}