#pragma once
#include "struct.h"
#include "def.h"
#include <stdio.h>
#include <windows.h>

//////////////////////////////  지역 ////////////////////////////////////////

zone_list* GetZone(void)
{
	return (zone_list*)malloc(sizeof(zone_list));
}

zone_head* createZoneList(void)
{
	zone_head* A;
	A = (zone_head*)malloc(sizeof(zone_head));
	A->head = NULL;
	return A;
}

void insertZone(zone_head* Z, char* name, int num, int Y, int X, int Z_cost, int H_cost, int B_cost, int V_cost, int Z_toll, int H_toll, int B_toll, int V_toll)
{
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

	if (Z->head == NULL)
	{
		Z->head = insert;
		insert->llink = NULL;
		insert->rlink = Z->head;
	}
	else
	{
		while (p->rlink != Z->head)
		{
			p = p->rlink;
		}
		p->rlink = insert;
		insert->llink = p;
		insert->rlink = Z->head;
		Z->head->llink = insert;
	}
}

void Zone_init(zone_head* ZONE)
{
	insertZone(ZONE, "출발", 0, 52, 142, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "타이베이", 1, 52, 128, 5, 25, 15, 5, 1, 25, 9, 3);
	insertZone(ZONE, "황금열쇠", 2, 52, 114, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "홍콩", 3, 52, 100, 5, 25, 15, 5, 1, 25, 9, 3);
	insertZone(ZONE, "마닐라", 4, 52, 86, 5, 25, 15, 5, 1, 25, 9, 3);
	insertZone(ZONE, "제주도", 5, 52, 72, 20, 0, 0, 0, 30, 0, 0, 0);
	insertZone(ZONE, "싱가포르", 6, 52, 58, 10, 25, 15, 5, 1, 55, 27, 9);
	insertZone(ZONE, "황금열쇠", 7, 52, 44, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "카이로", 8, 52, 30, 10, 25, 15, 5, 1, 55, 27, 9);
	insertZone(ZONE, "이스탄불", 9, 52, 16, 12, 25, 15, 5, 1, 60, 30, 10);
	insertZone(ZONE, "무인도", 10, 52, 2, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "아테네", 11, 47, 2, 14, 50, 30, 10, 2, 75, 45, 15);
	insertZone(ZONE, "황금열쇠", 12, 42, 2, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "코펜하겐", 13, 37, 2, 16, 50, 30, 10, 2, 90, 50, 18);
	insertZone(ZONE, "스톡홀름", 14, 32, 2, 16, 50, 30, 10, 2, 90, 50, 18);
	insertZone(ZONE, "콩코드여객기", 15, 27, 2, 20, 0, 0, 0, 30, 0, 0, 0);
	insertZone(ZONE, "취리히", 16, 22, 2, 18, 50, 30, 10, 2, 99, 55, 20);
	insertZone(ZONE, "황금열쇠", 17, 17, 2, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "베를린", 18, 12, 2, 18, 50, 30, 10, 2, 99, 55, 20);
	insertZone(ZONE, "몬트리올", 19, 7, 2, 20, 50, 30, 10, 2, 100, 60, 22);
	insertZone(ZONE, "사회복지기금", 20, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "부에노스아..", 21, 2, 16, 22, 75, 45, 15, 3, 105, 70, 25);
	insertZone(ZONE, "황금열쇠", 22, 2, 30, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "상파울로", 23, 2, 44, 24, 75, 45, 15, 3, 110, 75, 30);
	insertZone(ZONE, "시드니", 24, 2, 58, 24, 75, 45, 15, 3, 110, 75, 30);
	insertZone(ZONE, "부산", 25, 2, 72, 50, 0, 0, 0, 60, 0, 0, 0);
	insertZone(ZONE, "하와이", 26, 2, 86, 26, 75, 45, 15, 3, 115, 80, 33);
	insertZone(ZONE, "리스본", 27, 2, 100, 26, 75, 45, 15, 3, 115, 80, 33);
	insertZone(ZONE, "퀸엘리자베..", 28, 2, 114, 30, 0, 0, 0, 20, 0, 0, 0);
	insertZone(ZONE, "마드리드", 29, 2, 128, 28, 75, 45, 15, 3, 120, 85, 36);
	insertZone(ZONE, "우주여행", 30, 2, 142, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "도쿄", 31, 7, 142, 30, 100, 60, 20, 4, 127, 90, 39);
	insertZone(ZONE, "콜롬비아호", 32, 12, 142, 40, 0, 0, 0, 50, 0, 0, 0);
	insertZone(ZONE, "파리", 33, 17, 142, 32, 100, 60, 20, 4, 140, 100, 45);
	insertZone(ZONE, "로마", 34, 22, 142, 32, 100, 60, 20, 4, 140, 100, 45);
	insertZone(ZONE, "황금열쇠", 35, 27, 142, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "런던", 36, 32, 142, 35, 100, 60, 20, 4, 150, 110, 50);
	insertZone(ZONE, "뉴욕", 37, 37, 142, 35, 100, 60, 20, 4, 150, 110, 50);
	insertZone(ZONE, "사회복지기금접수처", 38, 42, 142, 0, 0, 0, 0, 0, 0, 0, 0);
	insertZone(ZONE, "서울", 39, 47, 142, 100, 0, 0, 0, 200, 0, 0, 0);
}

void free_zone(zone_head* Z)
{
	zone_list* tmp = Z->head;
	Z->head->llink->rlink = NULL;
	Z->head->llink = NULL;

	while (Z->head->rlink != NULL)
	{
		tmp = Z->head;
		Z->head = Z->head->rlink;
		free(tmp);
		tmp = NULL;
	}
	free(Z->head);
	Z->head = NULL;
}


