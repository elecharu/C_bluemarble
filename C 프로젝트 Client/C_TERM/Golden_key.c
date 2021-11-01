//#pragma once
#include "struct.h"
#include "def.h"
#include <stdio.h>
#include <windows.h>
///////////////////////////////// 황금 열쇠 ///////////////////////////////////////////////

golden_key* GetGoldenKey(void){
	return(golden_key*)malloc(sizeof(golden_key));
}

golden_key_head* createGoldenList(void){
	golden_key_head* A;
	A = (golden_key_head*)malloc(sizeof(golden_key_head));
	A->front = NULL;
	A->head = NULL;
	return A;
}

void insertKey(golden_key_head* G, int num, char* name, char* content){
	golden_key* insert = GetGoldenKey();
	golden_key* p = G->front;

	insert->F_link = NULL;
	insert->key_content = content;
	insert->key_name = name;
	insert->key_num = num;

	if (G->front == NULL){
		G->front = insert;
		G->head = insert;
		insert->F_link = insert;
	}
	else{
		while (p->F_link != G->front){
			p = p->F_link;
		}
		p->F_link = insert;
		insert->F_link = G->front;
	}
}


//////////////// 황금열쇠 초기화 //////////////////

void golden_key_init(golden_key_head* G_KEY,int bal){
	insertKey(G_KEY, 0, "병원비 지불", "병원에서 건강진단을 받았음. 병원비를 은행에 내시오.");
	insertKey(G_KEY, 1, "복권 당첨", "축하합니다. 복권에 당첨되었음.");
	insertKey(G_KEY, 2, "무인도탈출용(특수무전기)", "무인도에 갇혔을 경우 사용할 수 있음.");
	insertKey(G_KEY, 3, "무인도로 가시오.", "폭풍을 만났음. 무인도로 곧장가시오.");
	insertKey(G_KEY, 4, "주사위 홀짝권", "주사위의 홀/짝을 정할 수 있다.");
	insertKey(G_KEY, 5, "과속운전벌금", "과속운전을 했으므로 벌금을 내시오");
	insertKey(G_KEY, 6, "해외유학", "학교 등록금을 내시오");
	insertKey(G_KEY, 7, "연금혜택", "은행에서 노후연금을 받으시오");
	insertKey(G_KEY, 8, "이사가시오", "뒤로 세칸 옮기시오");
	insertKey(G_KEY, 9, "이사가시오", "뒤로 두칸 옮기시오");
	insertKey(G_KEY, 10, "고속도로", "출발지까지 곧바로 가시오");
	insertKey(G_KEY, 11, "자동차 경주 우승", "자동차 경주에서 챔피언이 되었음.");
	insertKey(G_KEY, 12, "우대권", "이 우대권을 가지고 있을 경우 상대방의 장소를 통행료없이 머무를 수 있음");
	insertKey(G_KEY, 13, "관광여행", "부산으로 가시오");
	insertKey(G_KEY, 14, "방범비", "방범비를 각 건물별로 다음과 같이 은행에 내시오(호텔:5만원,빌딩:3만원,별장:1만원)");
	insertKey(G_KEY, 15, "장학금혜택", "은행에서 장학금을 받으시오");
	insertKey(G_KEY, 16, "세계일주초대권", "축하합니다, 현재위치에서 한바퀴를 돌아오시오.(월급 2배)");
	insertKey(G_KEY, 17, "건물수리비지불", "건물수립를 각 건물 별로 다음과 같이 은행에 지불하시오. 단위:만원(호텔:15,빌딩:10,별장:3)");
	insertKey(G_KEY, 18, "노벨평화상수상", "당신은 세계평화를 위해 공헌하였으므로 은행으로부터 상금을 받습니다.");
	insertKey(G_KEY, 19, "반액대매출", "당신의 재산 중에서 땅 값이 제일 비싼 곳을 반액으로 은행에 파시오(건물까지)");
	insertKey(G_KEY, 20, "관광여행", "88년도 올림픽 개최지인 서울로 가시오");
	insertKey(G_KEY, 21, "정기정합소득세", "정기종합소득세를 각 건물별로 다음과 같이 은행에 내시오. 단위:만원(호텔:15,빌딩:10,별장:3)");
	insertKey(G_KEY, 22, "우주여행초청장", "우주항공국에서 우주여행초청장이 왔음(무료)");
	insertKey(G_KEY, 23, "공격권", "해당 플레이어의 가장 비싼 땅을 무료로 판매하시오");
}

void take_golden_key(golden_key_head* G_KEY, int num){
	while (G_KEY->front->key_num != num)
		G_KEY->front = G_KEY->front->F_link; //rlink
}

void free_key(golden_key_head* G){
	golden_key* tmp = G->head;

	while (tmp->key_name != "사회복지기금배당")
		tmp = tmp->F_link;
	tmp->F_link = NULL;

	while (G->head != NULL){
		tmp = G->head;
		G->head = G->head->F_link;
		free(tmp);
		tmp = NULL;
	}
	free(G->head);
	G->head = NULL;
}


