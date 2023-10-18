#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>

#define PLAYER_MAX		10

bool player[PLAYER_MAX];  // 기본값 true, 탈락하면 false
int n_player, n_alive;
int tick;  // 시계

typedef enum Color_type {
	black = 0,  	//0
	dark_blue,	//1
	dark_green,	//2
	dark_sky_blue,//3
	dark_red,  	//4
	dark_purple,	//5
	dark_yellow,	//6
	gray,		//7
	dark_gray,	//8
	blue,		//9
	green,		//10
	sky_blue,	//11
	red,		//12
	purple,		//13
	yellow,		//14
	white		//15
} COLOR;

void text_color(int color);
void print_color_text(char const* const text, int color);
void intro_color(char const* const text, int color);
void intro(void);

// 미니게임
void intro(void);
void sample(void);
void mugunghwa(void);
//void nightgame(void);
//void juldarigi(void);
//void jebi(void);

int randint(int low, int high);

#endif
