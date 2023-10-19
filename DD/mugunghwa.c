#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>


#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

void sample_init_1(void);
void move_manual_1(key_t key);
void move_random_1(int i, int dir);
void move_tail_1(int i, int nx, int ny);
void print_mugung(void);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];


void sample_init_1(void) {
	map_init(14, 40);
	int x, y;
	for (int i = 0; i < n_player; i++) {

		do {
			x = randint(2, N_ROW - 3);
			y = randint(38, N_COL - 2);
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}


	back_buf[5][1] = '#';
	back_buf[6][1] = '#';
	back_buf[7][1] = '#';
	back_buf[8][1] = '#';



	tick = 0;
}


void move_manual_1(key_t key) {

	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}


	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}

	move_tail_1(0, nx, ny);
}


void move_random_1(int player, int dir) {
	int p = player;
	int nx, ny;

	int r = randint(1, 100);
	gotoxy(N_ROW + 3, 0);
	printf("%d", r);
	if (r <= 70) { // Move left (70% probability)
		nx = px[p];
		ny = py[p] - 1;
	}
	else if (r <= 80) { // Move up (10% probability)
		nx = px[p] - 1;
		ny = py[p];
	}
	else if (r <= 90) { // Move down (10% probability)
		nx = px[p] + 1;
		ny = py[p];
	}
	else { // Stay in place (10% probability)
		nx = px[p];
		ny = py[p];
	}

	// Check if the new position is placable
	if (placable(nx, ny)) {
		move_tail_1(p, nx, ny);
	}
}


// back_buf[][]
void move_tail_1(int player, int nx, int ny) {
	int p = player;
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;

	if ((nx == 4 && ny == 1) || (nx == 5 && ny == 2) || (nx == 6 && ny == 2) ||
		(nx == 7 && ny == 2) || (nx == 8 && ny == 2) || (nx == 9 && ny == 1)) {
		gotoxy(N_ROW + 2, 0);
		printf("player%d clear", player);
	}



}


void mugunghwa(void) {
	sample_init_1();

	system("cls");
	display();
	Sleep(1000);
	//dialog("READY");
	Sleep(1000);

	while (1) {
		key_t key = get_key();

		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual_1(key);
		}
		
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
					move_random_1(i, -1);
			}
		}
		if (tick >= 5401) {
			tick = 0;
		}
		print_mugung(tick);

		display();
		Sleep(10);
		tick += 10;
		gotoxy(N_ROW + 2, 0);
		printf("%d", tick);
	}
}


void print_mugung(int msec) {
	gotoxy(N_ROW + 1, 0);
	if (msec == 500) {
		printf("¹« ");
	}
	if (msec == 800) {
		printf("¹« ±Ã ");
	}
	if (msec == 1100) {
		printf("¹« ±Ã È­ ");
	}
	if (msec == 1300) {
		printf("¹« ±Ã È­ ²É ");
	}
	if (msec == 1600) {
		printf("¹« ±Ã È­ ²É ÀÌ ");
	}
	if (msec == 1750) {
		printf("¹« ±Ã È­ ²É ÀÌ ÇÇ ");
	}
	if (msec == 1900) {
		printf("¹« ±Ã È­ ²É ÀÌ ÇÇ ¾ú ");
	}
	if (msec == 2100) {
		printf("¹« ±Ã È­ ²É ÀÌ ÇÇ ¾ú ½À ");
	}
	if (msec == 2200) {
		printf("¹« ±Ã È­ ²É ÀÌ ÇÇ ¾ú ½À ´Ï ");
	}
	if (msec == 2400) {
		printf("¹« ±Ã È­ ²É ÀÌ ÇÇ ¾ú ½À ´Ï ´Ù");
	}
	if (msec == 5400) {
		gotoxy(N_ROW + 1, 0);
		for (int i = 1; i < 30; i++) {
			printf(" ");
		}
	}

}