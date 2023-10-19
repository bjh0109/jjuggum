#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>


#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

/// 맵 안에서 카메라가 표시될 시작과 끝 위치
#define Camera_start_y 5
#define Camera_end_y 8
#define Camera_start_x 1

/// 무궁화 꽃이 피었습니 를 외칠 때 카메라 아이콘
#define Camera_not_working_icon '#'
/// 무궁화 꽃이 피었습니다를 외칠 때 카메라 아이콘
#define Camera_working_icon '@'

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

	for (int y = Camera_start_y; y < Camera_end_y + 1; y++) {
		back_buf[y][Camera_start_x] = Camera_not_working_icon;
	}

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
	dialog("READY");
	Sleep(1000);

	while (1) {
		key_t key = get_key();

		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual_1(key);
		}
		//print_mugung();
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
					move_random_1(i, -1);
			}
		}
		

		display();
		Sleep(10);
		tick += 10;
		gotoxy(N_ROW + 1, 0);
		printf("%d", tick);

	}
}


void print_mugung(void) {
	gotoxy(N_ROW + 1, 0);
	printf("a "); Sleep(350);
	printf("b "); Sleep(400);
	printf("c "); Sleep(500);
	printf("d "); Sleep(550);
	printf("e "); Sleep(600);
	printf("f "); Sleep(450);
	printf("g "); Sleep(250);
	printf("h "); Sleep(200);
	printf("i "); Sleep(100);
	printf("j"); Sleep(3000);
	gotoxy(N_ROW + 1, 0);
	for (int i = 1; i < 30; i++) {
		printf(" ");
	}
	Sleep(1000);

}


/// <summary>
/// "무궁화 꽃이 피었습니"
///    이후 "다"를 외친다면,
/// 다를 외친 후 3초동안 # -> @로 카메라가 변환되는 함수입니다.
/// </summary>
void turn_of_camera() {
	
}


/// <summary>
/// "무궁화 꽃이 피었습니다"를 외친 후 카메라가 돌아갔을 때
///		플레이어가 움직였는지, 움직였다면 어느 플레이어가 움직였는지를 파악하는 코드입니다.
/// </summary>
void check_player_moving_when_camera_turned() {

}