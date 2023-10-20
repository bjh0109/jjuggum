// 2023-2 고급프로그래밍 과제: 쭈꾸미 게임
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);


// low 이상 high 이하 난수를 발생시키는 함수

int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("플레이어 수: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}


void text_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void print_color_text(char const* const text, int color) {
	text_color(color);
	printf(text);
	text_color(white);
}

void intro_color(char const* const text, int color) {
	printf("|");
	print_color_text(text, color);
	printf("|\n");
}

void intro(void) {
	printf(".--------------------------------------------------------------.\n");
	printf("|                                                              |\n");
	Sleep(35);
	intro_color("       _     _          ____  ____         __  __ _           ", red);
	Sleep(45);
	intro_color("      | |   | |_   _   / ___|/ ___|_   _  |  \\/  (_)          ", red);
	Sleep(55);
	intro_color("   _  | |_  | | | | | | |  _| |  _| | | | | |\\/| | |          ", red);
	Sleep(75);
	intro_color("  | |_| | |_| | |_| | | |_| | |_| | |_| | | |  | | |          ", red);
	Sleep(85);
	intro_color("   \\___/ \\___/ \\__,_|  \\____|\\____|\\__,_| |_|  |_|_|          ", red);
	Sleep(95);
	intro_color("    ____    _    __  __ _____   ____ _____  _    ____ _____   ", yellow);
	Sleep(105);
	intro_color("   / ___|  / \\  |  \\/  | ____| / ___|_   _|/ \\  |  _ \\_   _|  ", yellow);
	Sleep(115);
	intro_color("  | |  _  / _ \\ | |\\/| |  _|   \\___ \\ | | / _ \\ | |_) || |    ", yellow);
	Sleep(125);
	intro_color("  | |_| |/ ___ \\| |  | | |___   ___) || |/ ___ \\|  _ < | |    ", yellow);
	Sleep(135);
	intro_color("   \\____/_/   \\_\\_|  |_|_____| |____/ |_/_/   \\_\\_| \\_\\|_|    ", yellow);
	printf("|                                                              |\n");
	printf("'--------------------------------------------------------------'\n");
	Sleep(1500);
}


//void intro(void)


int main(void) {
	
	jjuggumi_init();

	intro();
	//sample();
	mugunghwa();
	//nightgame();
	//juldarigi();
	//jebi();
	return 0;
}