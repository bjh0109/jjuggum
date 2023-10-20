#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3


bool pass_player[PLAYER_MAX];


void sample_init_1(void);
void move_manual_1(key_t key);
void move_random_1(int i, int dir);
void move_tail_2(int i, int nx, int ny);
void young();

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기


int b = 0;

void sample_init_1(void) {
	map_init(14, 30);
	int x, y;

	for (int i = 0; i < n_player; i++) {
		// 같은 자리가 나오면 다시 생성
		do {
			//플레리어들을 오른쪽 가장자리에 랜덤으로 정렬해줌
			x = randint(2, N_ROW - 3);
			y = randint(28, N_COL - 2);
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}

	//플레이어 전부다 통과하지 못한 상태
	for (int i = 0; i < n_player; i++) {
		pass_player[i] = false;
	}



	//과제 2에서 이것도 변수로 받게 바꿔야함(영희)
	/*if (a == 0) {
		back_buf[5][1] = '#';
		back_buf[6][1] = '#';
		back_buf[7][1] = '#';
		back_buf[8][1] = '#';
	}
	else if (a == 1) {
		back_buf[5][1] = '@';
		back_buf[6][1] = '@';
		back_buf[7][1] = '@';
		back_buf[8][1] = '@';

	}*/



	tick = 0;
}

void move_manual_1(key_t key) {
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// 움직여서 놓일 자리
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}

	move_tail_2(0, nx, ny);
}

// 0 <= dir < 4가 아니면 랜덤
void move_random_1(int player, int dir) {
	int p = player;  // 이름이 길어서...
	int nx, ny;  // 움직여서 다음에 놓일 자리


	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	
	int x[4] = { 0,-1,1,0 };
	int y[4] = { -1.0,0,0 };
	int r = 0;
	do {
		r = randint(0, 101);
		/*gotoxy(N_ROW + 3, 0);
		printf("%d", r);*/
		if (r <= 70) {
			nx = px[p] + x[0];
			ny = py[p] + y[0];
		}
		else if (r <= 80) {
			nx = px[p] + x[1];
			ny = py[p] + y[1];
		}
		else if (r <= 90) {
			nx = px[p] + x[2];
			ny = py[p] + y[2];
		}
		else {
			nx = px[p] + x[3];
			ny = py[p] + y[3];
		}
	} while (!placable(nx, ny));

	move_tail_2(p, nx, ny);

}

void move_tail_2(int player, int nx, int ny) {
	int p = player;  // 이름이 길어서...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}


void young() {
	int a;
	gotoxy(N_ROW, 0);
	printf("%d", tick);

	if (b == 0) {
		back_buf[5][1] = '#';
		back_buf[6][1] = '#';
		back_buf[7][1] = '#';
		back_buf[8][1] = '#';
	}


	if (tick % 1000 == 0) {
		gotoxy(N_ROW + 1, 0);
		printf("무");
	}

	if (tick % 1500 == 0) {
		gotoxy(N_ROW + 1, 2);
		printf("궁");
	}

	if (tick % 2000 == 0) {
		gotoxy(N_ROW + 1, 4);
		printf("화");
	}

	if (tick % 2500 == 0) {
		gotoxy(N_ROW + 1, 6);
		printf("꽃");
	}

	if (tick % 3000 == 0) {
		gotoxy(N_ROW + 1, 8);
		printf("이");
	}

	if (tick % 3200 == 0) {
		gotoxy(N_ROW + 1, 10);
		printf("피");
	}

	if (tick % 3400 == 0) {
		gotoxy(N_ROW + 1, 12);
		printf("었");
	}

	if (tick % 3600 == 0) {
		gotoxy(N_ROW + 1, 14);
		printf("습");
	}

	if (tick % 3800 == 0) {
		gotoxy(N_ROW + 1, 16);
		printf("니");
	}

	if (tick % 4000 == 0) {
		gotoxy(N_ROW + 1, 18);
		printf("다");
		b = 1;
	}

	if (b == 1) {
		back_buf[5][1] = '@';
		back_buf[6][1] = '@';
		back_buf[7][1] = '@';
		back_buf[8][1] = '@';

	}

	if (tick % 7000 == 0) {
		gotoxy(N_ROW + 1, 0);
		for (int i = 0; i < 20 + 2; i++) {
			printf(" ");
			b = 0;
		}
		tick = 0;


	}


}



void pass1() {
	for (int i = 0; i < n_player; i++) {
		if ((px[i] == 4 && py[i] == 1) || (px[i] == 5 && py[i] == 2) || (px[i] == 6 && py[i] == 2) ||
			(px[i] == 7 && py[i] == 2) || (px[i] == 8 && py[i] == 2) || (px[i] == 9 && py[i] == 1)) {
			back_buf[px[i]][py[i]] = ' ';
			pass_player[i] = true;
		}
	}
}


void mugunghwa(void) {

	sample_init_1();

	system("cls");
	display();
	Sleep(1000);
	while (1) {
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual_1(key);
		}

		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0 && pass_player[i] == false) {
				move_random_1(i, -1);
			}
			else
				continue;
		}

		int a[PLAYER_MAX];
		for (int i = 0; i < n_player; i++) {
			a[i] = -1; // 모든 요소를 -1로 초기화
		}

		for (int i = 0; i < n_player; i++) {
			if (pass_player[i] == true) {
				a[i] = i;
				gotoxy(N_ROW + 3, 0);
				printf("통과: ");
				for (int j = 0; j < n_player; j++) {
					if (a[j] != -1) {
						printf("%d번 ", a[j]);
					}
				}
			}
		}

		//// tick 값이 500의 배수일 때만 ready 메시지 출력
		//if (tick % 1000 == 0 && tick != 0) {
		//	dialog("player 1 dead");
		//	Sleep(1000);
		//}

		pass1();
		display();
		Sleep(10);
		tick += 10;
		young();
	}
}