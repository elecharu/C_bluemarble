#include "struct.h"
#include "def.h"
#include <stdio.h>
#include <windows.h>



//////////////////////////////  지역 ////////////////////////////////////////

zone_list* GetZone(void){
	return (zone_list*)malloc(sizeof(zone_list));
}

zone_head* createZoneList(void){
	zone_head* A;
	A = (zone_head*)malloc(sizeof(zone_head));
	A->head = NULL;
	return A;
}

void insertZone(zone_head* Z, char* name, int num, int X, int Y, int Z_cost, int H_cost, int B_cost, int V_cost, int Z_toll, int H_toll, int B_toll, int V_toll,char* color){
	zone_list* insert = GetZone();
	zone_list* p = Z->head;

	insert->zone_name = name;
	insert->zone_num = num;
	insert->zone_X = X;
	insert->zone_Y = Y;
	insert->owner = NULL;
	insert->hotel = NON_EXIST;
	insert->building = NON_EXIST;
	insert->villa = NON_EXIST;
	insert->zone_cost = Z_cost;
	insert->hotel_cost = H_cost;
	insert->building_cost = B_cost;
	insert->villa_cost = V_cost;
	insert->zone_toll = Z_toll;
	insert->hotel_toll = H_toll;
	insert->building_toll = B_toll;
	insert->villa_toll = V_toll;
	insert->zone_color = color;

	if (Z->head == NULL){ //head가 NULL일때 
		Z->head = insert;
		insert->B_link = NULL;
		insert->F_link = Z->head;
	}
	else{
		while (p->F_link != Z->head){
			p = p->F_link;
		}
		p->F_link = insert;
		insert->B_link = p;
		insert->F_link = Z->head;
		Z->head->B_link = insert;
	}
}
/*
void Zone_init(zone_head* ZONE)
{							    //x,y
	insertZone(ZONE, "출발", 0, 4, 44, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "방콕", 1, 4, 38, 5, 25, 15, 5, 1, 25, 9, 3);
	insertZone(ZONE, "베이징", 2, 4, 32, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "황금열쇠", 3, 4, 26, 5, 25, 15, 5, 1, 25, 9, 3);
	insertZone(ZONE, "타이베이", 4, 4, 20, 5, 25, 15, 5, 1, 25, 9, 3);
	insertZone(ZONE, "두바이", 5, 4, 14, 20, 0, 0, 0, 30, 0, 0, 0);
	insertZone(ZONE, "카이로", 6, 4, 8, 10, 25, 15, 5, 1, 55, 27, 9);
	insertZone(ZONE, "무인도", 7, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "오사카", 8, 20, 2, 10, 25, 15, 5, 1, 55, 27, 9);
	insertZone(ZONE, "시드니", 9, 36, 2, 12, 25, 15, 5, 1, 60, 30, 10);
	insertZone(ZONE, "홍콩", 10, 52, 2, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "황금열쇠", 11, 68, 2, 14, 50, 30, 10, 2, 75, 45, 15);
	insertZone(ZONE, "시카고", 12, 84, 2, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "부산", 13, 100, 2, 16, 50, 30, 10, 2, 90, 50, 18);
	insertZone(ZONE, "우주여행", 14, 116, 2, 16, 50, 30, 10, 2, 90, 50, 18);
	insertZone(ZONE, "모스크바", 15, 116, 8, 20, 0, 0, 0, 30, 0, 0, 0);
	insertZone(ZONE, "토론토", 16, 116, 14, 18, 50, 30, 10, 2, 99, 55, 20);
	insertZone(ZONE, "황금열쇠", 17, 116, 20, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "리스본", 18, 116, 26, 18, 50, 30, 10, 2, 99, 55, 20);
	insertZone(ZONE, "마드리드", 19, 116, 32, 20, 50, 30, 10, 2, 100, 60, 22);
	insertZone(ZONE, "로마", 20, 116, 38, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "홀짝게임", 21, 116, 44, 22, 75, 45, 15, 3, 105, 70, 25);
	insertZone(ZONE, "베를린", 22, 100, 44, 44, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "파리", 23, 84, 44, 44, 75, 45, 15, 3, 110, 75, 30);
	insertZone(ZONE, "런던", 24, 68, 44, 44, 75, 45, 15, 3, 110, 75, 30);
	insertZone(ZONE, "황금열쇠", 25, 52, 44, 50, 0, 0, 0, 60, 0, 0, 0);
	insertZone(ZONE, "뉴욕", 26, 36, 44, 26, 75, 45, 15, 3, 115, 80, 33);
	insertZone(ZONE, "서울", 27, 20, 44, 26, 75, 45, 15, 3, 115, 80, 33);
}
*/
//(zone_head* Z, char* name, int num, int X, int Y, int Z_cost, int H_cost, int B_cost, int V_cost, int Z_toll, int H_toll, int B_toll, int V_toll,char color)
//4번째부터 땅 가격, 호텔 가격, 빌딩가격, 빌라가격 , 땅 통행료, 호텔 통행료, 빌딩 통행료, 빌라 통행료
void Zone_init(zone_head* ZONE,int bal){							   
	insertZone(ZONE, "출발", 0, 5, 44, 0, 0, 0, 0, 0, 0, 0, 0,"none");
	insertZone(ZONE, "방콕", 1, 6, 38, (bal / 40) , (bal / 20), (bal / 40), (bal / 80), (bal / 40), ((bal / 40) + (bal / 20)), ((bal / 40)* 2), ((bal / 40) + (bal / 80)), "gray");
	insertZone(ZONE, "베이징", 2, 5, 32, (bal / 40) , (bal / 20), (bal / 40), (bal / 80), (bal / 40), ((bal / 40) + (bal / 20)), ((bal / 40) * 2), ((bal / 40) + (bal / 80)), "gray");
	insertZone(ZONE, "황금열쇠", 3, 4, 26, 0, 0, 0, 0, 0, 0, 0, 0, "none");
	insertZone(ZONE, "타이베이", 4, 4, 20, (bal / 35), (bal / 35) * 2, (bal / 35), (bal / 70), (bal / 35), ((bal / 35) + ((bal / 35)*2)), ((bal / 35) * 2), ((bal / 35) + (bal / 70)), "white");
	insertZone(ZONE, "두바이", 5, 5, 14, (bal / 35), (bal / 35) * 2, (bal / 35), (bal / 70), (bal / 35), ((bal / 35) + ((bal / 35) * 2)), ((bal / 35) * 2), ((bal / 35) + (bal / 70)), "white");
	insertZone(ZONE, "카이로", 6, 5, 8, (bal / 35), (bal / 35) * 2, (bal / 35), (bal / 70), (bal / 35), ((bal / 35) + ((bal / 35) * 2)), ((bal / 35) * 2), ((bal / 35) + (bal / 70)), "white");
	insertZone(ZONE, "무인도", 7, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, "none");
	insertZone(ZONE, "오사카", 8, 21, 2, (bal / 30), (bal / 15), (bal / 30), (bal / 60), (bal / 30), ((bal / 30) + ((bal / 30) * 2)), ((bal / 30) * 2), ((bal / 30) + (bal / 60)),"sky");
	insertZone(ZONE, "시드니", 9, 37, 2, (bal / 30), (bal / 15), (bal / 30), (bal / 60), (bal / 30), ((bal / 30) + ((bal / 30) * 2)), ((bal / 30) * 2), ((bal / 30) + (bal / 60)), "sky");
	insertZone(ZONE, "홍콩", 10, 54, 2, (bal / 30), (bal / 15), (bal / 30), (bal / 60), (bal / 30), ((bal / 30) + ((bal / 30) * 2)), ((bal / 30) * 2), ((bal / 30) + (bal / 60)), "sky");
	insertZone(ZONE, "황금열쇠", 11, 68, 2, 0, 0, 0, 0, 0, 0, 0, 0, "none");
	insertZone(ZONE, "시카고", 12, 85, 2, (bal / 25), (bal / 25 ) * 2, (bal / 25), (bal / 50), (bal / 25), ((bal / 25) + ((bal / 25) * 2)), ((bal / 25) * 2), ((bal / 25) + (bal / 50)),"blue");
	insertZone(ZONE, "부산", 13, 102, 2, (bal / 25), (bal / 25 ) * 2, (bal / 25), (bal / 50), (bal / 25), ((bal / 25) + ((bal / 25) * 2)), ((bal / 25) * 2), ((bal / 25) + (bal / 50)), "blue");
	insertZone(ZONE, "우주여행", 14, 116, 2, 0, 0, 0, 0, 0, 0, 0, 0, "none");
	insertZone(ZONE, "모스크바", 15, 116, 8, (bal / 20), (bal / 10), (bal / 20), (bal / 40), (bal / 20), ((bal / 20) + ((bal / 20) * 2)), ((bal / 20) * 2), ((bal / 20) + (bal / 40)),"violet");
	insertZone(ZONE, "토론토", 16, 117, 14, (bal / 20), (bal / 10), (bal / 20), (bal / 40), (bal / 20), ((bal / 20) + ((bal / 20) * 2)), ((bal / 20) * 2), ((bal / 20) + (bal / 40)), "violet");
	insertZone(ZONE, "황금열쇠", 17, 116, 20, 0, 0, 0, 0, 0, 0, 0, 0, "none");
	insertZone(ZONE, "리스본", 18, 117, 26, (bal / 15), (bal / 15) * 2, (bal / 15), (bal / 30), (bal / 15), ((bal / 15) + ((bal / 15) * 2)), ((bal / 15) * 2), ((bal / 15) + (bal / 30)),"purple");
	insertZone(ZONE, "마드리드", 19, 116, 32, (bal / 15), (bal / 15) * 2, (bal / 15), (bal / 30), (bal / 15), ((bal / 15) + ((bal / 15) * 2)), ((bal / 15) * 2), ((bal / 15) + (bal / 30)),"purple");
	insertZone(ZONE, "로마", 20, 118, 38, (bal / 15), (bal / 15) * 2, (bal / 15), (bal / 30), (bal / 15), ((bal / 15) + ((bal / 15) * 2)), ((bal / 15) * 2), ((bal / 15) + (bal / 30)), "purple");
	insertZone(ZONE, "홀짝게임", 21, 116, 44, 0, 0, 0, 0, 0, 0, 0, 0, "none");
	insertZone(ZONE, "베를린", 22, 101, 44, (bal / 10), (bal / 5), (bal / 10), (bal / 20), (bal / 10), ((bal / 10) + ((bal / 10) * 2)), ((bal / 10) * 2), ((bal / 10) + (bal / 20)),"lred");
	insertZone(ZONE, "파리", 23, 86, 44, (bal / 10), (bal / 5), (bal / 10), (bal / 20), (bal / 10), ((bal / 10) + ((bal / 10) * 2)), ((bal / 10) * 2), ((bal / 10) + (bal / 20)),"lred");
	insertZone(ZONE, "런던", 24, 70, 44, (bal / 10), (bal / 5), (bal / 10), (bal / 20), (bal / 10), ((bal / 10) + ((bal / 10) * 2)), ((bal / 10) * 2), ((bal / 10) + (bal / 20)),"lred");
	insertZone(ZONE, "황금열쇠", 25, 52, 44, 0, 0, 0, 0, 0, 0, 0, 0, "none");
	insertZone(ZONE, "뉴욕", 26, 38, 44, (bal / 5), (bal / 5) * 2, (bal / 5), (bal / 10), (bal / 5), ((bal / 5) + ((bal / 5) * 2)), ((bal / 5) * 2), ((bal / 5) + (bal / 10)),"red");
	insertZone(ZONE, "서울", 27, 22, 44, (bal / 5), (bal / 5) * 2, (bal / 5), (bal / 10), (bal / 5), ((bal / 5) + ((bal / 5) * 2)), ((bal / 5) * 2), ((bal / 5) + (bal / 10)),"red");
}

void free_zone(zone_head* Z){
	zone_list* tmp = Z->head;
	Z->head->B_link->F_link = NULL;
	Z->head->B_link = NULL;

	while (Z->head->F_link != NULL){
		tmp = Z->head;
		Z->head = Z->head->F_link;
		free(tmp);
		tmp = NULL;
	}
	free(Z->head);
	Z->head = NULL;
}


