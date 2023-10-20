#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <time.h>


/*
* ********* ********* ********* *
* 상수, define, enum etc.. 선언 *
* ********* ********* ********* *
*/

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3


#define MuGungWha_next_keyword_present_seconds 3
/// 肄李쎌 臾몄댁 異�ν sleep ⑥ (硫몄ㅻ sleep 媛)
#define Console_print_frame_rate_unit 10


typedef enum Camera_position_info_from_console {
	Camera_start_x = 1,
	Camera_start_y = 5,
	Camera_end_y = 8
}CameraPosition;


typedef enum Camera_icon_from_console {
	Working_camera_icon = '@',
	Not_working_camera_icon = '#'
}CameraIcon;


typedef enum Camera_checking_state_when_game_paused {
	Camera_is_not_checking = 0,
	Camera_is_checking 
}CameraCheckingState;




/*
* ********* ********* ********* *
*          ⑥紐           *
* ********* ********* ********* *
*/
void sample_init_1(void);
void move_manual_1(key_t key);
void move_random_1(int i, int dir);
void move_tail_1(int i, int nx, int ny);
void print_mugung(void);

void update_canera_positoin_from_back_buf();
void turn_of_camera();
void update_players_moving_position();
void update_console_info();
char check_specific_player_in_back_buf(Point from);


/*
* ********* ********* ********* *
*          ��           *
* ********* ********* ********* *
*/
int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];



CameraCheckingState cameraCheckingState = Camera_is_not_checking;

void sample_init_1(void) {
	map_init(14, 30);
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

	update_canera_positoin_from_back_buf();

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

	move_tail_2(0, nx, ny);
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
}


void young() {
	int a;
	gotoxy(N_ROW, 0);
	printf("%d", tick);
	
	if (tick % 1000 == 0) {
		gotoxy(N_ROW+1, 0);
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
	}

	if (tick % 7000 == 0) {
		gotoxy(N_ROW + 1, 0);
		for (int i = 0; i < 20 + 2; i++) {
			printf(" ");
		}
		tick = 0;

	}


}


	if ((nx == 4 && ny == 1) || (nx == 5 && ny == 2) || (nx == 6 && ny == 2) ||
		(nx == 7 && ny == 2) || (nx == 8 && ny == 2) || (nx == 9 && ny == 1)) {
		gotoxy(N_ROW + 2, 0);
		printf("player%d clear", player);
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
		if (cameraCheckingState == Camera_is_checking) {
			/// 臾닿 苑 쇱듬 -> ""瑜 몄  cameraChecingState 瑜  媛 寃쎌곕 留ㅼ 
			/// TODO: - 3珥 移대 由  吏대 player泥댄ы湲 
		}
		else {
			/// TODO: - "臾닿 苑 쇱듬"   �댁대  대.
			update_players_moving_position();
		}
		update_console_info();
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


void update_console_info() {
	display();
	Sleep(Console_print_frame_rate_unit);
	tick += Console_print_frame_rate_unit;
	gotoxy(N_ROW + 1, 0);
	printf("%d", tick);

}


void update_players_moving_position() {
	for (int i = 1; i < n_player; i++) {
		if (tick % period[i] == 0) {
			move_random_1(i, -1);
		}
	}
}


void turn_of_camera() {
	Point directions[4] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

	cameraCheckingState = Camera_is_checking;
	time_t startTime = time(NULL);
	time_t endTime = startTime + MuGungWha_next_keyword_present_seconds;

	
	char moved_players_when_camera_working_state[100] = { ' ' };
	int moved_players_index = 0;

	update_canera_positoin_from_back_buf();
	update_console_info();

	while ((time(NULL) < endTime)) {
		Sleep(Console_print_frame_rate_unit);
		/// 硫댁 蹂댁ъ 寃 留  back_buf �蹂대� temp_map쇰 copy
		char before_players_moving_info_buf[ROW_MAX][COL_MAX];
		memcpy(before_players_moving_info_buf, back_buf, sizeof(back_buf));

		/// �댁대 뱀 瑜濡 吏щ..
		update_players_moving_position();
		
		for (int i = 0; i < ROW_MAX; i++) {
			for (int j = 0; j < COL_MAX; j++) {
				Point point = { i, j };
				bool isPlayerMoved = false;
				char player = check_specific_player_in_back_buf(point);

				if (player != '-1' && (before_players_moving_info_buf[i][j] != back_buf[i][j])) {
					
					for (int directionIndex = 0; directionIndex < 4; directionIndex++) {
						int dx = i + directions[directionIndex].x;
						int dy = j + directions[directionIndex].y;
						if (dx != 0 && dy != 0 && dx < ROW_MAX && dy < COL_MAX) {
							if (before_players_moving_info_buf[dx][dy] == player) {
								isPlayerMoved = true;
								break;
							}
						}
					}
				}

				if (isPlayerMoved && player != '-1') {
					/// 吏 �댁 �.
					moved_players_when_camera_working_state[moved_players_index++] = player;
				}

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
		memcpy(back_buf, before_players_moving_info_buf, sizeof(back_buf));
	}
	/// TODO: - moved_players_when_camera_working_state �λ 뱀 �댁대ㅼ 
	///				back_buf濡遺 �嫄고怨 ㅼ댁쇰洹몃 源蹂댁ъ＜ 肄 깊댁쇳⑸.
	///				대源吏? 0..<moved_players_index 源吏
	 
	
	
	cameraCheckingState = Camera_is_not_checking;
}

char check_specific_player_in_back_buf(Point from) {
	char player = '-1';
	for (int playerIndex = 0; playerIndex < n_player; playerIndex++) {
		if (back_buf[from.x][from.y] == '0' + playerIndex) {
			player = '0' + playerIndex;
			return player;
		}
	}
	return player;
}



void update_canera_positoin_from_back_buf() {
	CameraIcon icon;

	switch (cameraCheckingState) {
	case Camera_is_checking:
		icon = Working_camera_icon;
		break;
	case Camera_is_not_checking:
		icon = Not_working_camera_icon;
		break;
	}

	for (int y = Camera_start_y; y < Camera_end_y + 1; y++) {
		back_buf[y][Camera_start_x] = icon;

	}
}