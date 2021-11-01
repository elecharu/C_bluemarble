FMOD_SYSTEM* g_System;
FMOD_SOUND* g_Sound[10];
FMOD_CHANNEL* channel[2];  // 인트로, BGM channel[0]

void fmod_Init()
{
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL);
	FMOD_System_CreateSound(g_System, "인게임.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[0]); // BGM
	FMOD_System_CreateSound(g_System, "주사위.mp3", FMOD_DEFAULT, 0, &g_Sound[1]); // 주사위
	FMOD_System_CreateSound(g_System, "무인도.mp3", FMOD_DEFAULT, 0, &g_Sound[2]); // 무인도
	FMOD_System_CreateSound(g_System, "박수소리.wav", FMOD_DEFAULT, 0, &g_Sound[3]); // 사회복지기금 획득
	FMOD_System_CreateSound(g_System, "반환점.mp3", FMOD_DEFAULT, 0, &g_Sound[4]); // 반환점
	FMOD_System_CreateSound(g_System, "우주여행.mp3", FMOD_DEFAULT, 0, &g_Sound[5]); // 우주선
	FMOD_System_CreateSound(g_System, "한숨소리(사회복지기금).mp3", FMOD_DEFAULT, 0, &g_Sound[6]); // 사회복지기금 제출
	FMOD_System_CreateSound(g_System, "카드소리.wav", FMOD_DEFAULT, 0, &g_Sound[7]); // 카드소리
	FMOD_System_CreateSound(g_System, "시작화면.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[8]); // 인트로
	FMOD_System_CreateSound(g_System, "게임오버.mp3", FMOD_DEFAULT, 0, &g_Sound[9]); // 게임오버
}

void fmod_Release()
{
	for (int i = 0; i < 10; i++)
		FMOD_Sound_Release(g_Sound[i]);
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}