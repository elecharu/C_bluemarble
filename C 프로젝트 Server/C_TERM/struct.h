//#pragma once
//////////// 지역 정보 구조체 //////////////

typedef struct zone_list {
	struct zone_list* B_link;  //뒤의 땅을 나타냄 //llink
	struct zone_list* F_link; //앞의 땅을 나타냄 //rlink
	int zone_num;
	int zone_X;
	int zone_Y;
	int owner;
	int zone_cost;
	int hotel_cost;
	int building_cost;
	int villa_cost;
	int hotel;
	int building;
	int villa;
	int zone_toll;
	int hotel_toll;
	int building_toll;
	int villa_toll;
	char* zone_color;
	char* zone_name;
}zone_list;
typedef struct zone_head{
	zone_list* head;
}zone_head;



///////////////////// 유저 정보 구조체 //////////////////////
typedef struct player {
	struct zone_list* location;
	int pre_X;
	int pre_Y;
	int money;
	int island_index;		//무인도 턴 인덱스
	int spaceship;			//우주여행 여부
	int escape;				//무인도 탈출권
	int passcard; 			//우대권
	int OE; // 홀 수 짝수 ODD, EVEN
	int gameover;
	
}player;
/////////////////////// 황금열쇠 정보 구조체 /////////////////////
typedef struct golden_key{
	struct golden_key* F_link;
	int key_num;
	char* key_name;
	char* key_content;
}golden_key;

typedef struct golden_key_head {
	golden_key* front;
	golden_key* head;
}golden_key_head;