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
/// 콘솔창에 문자열을 출력하는 sleep 단위 (메인스레드 sleep 시간)
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
*          함수명 선언          *
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
*          전역변수 선언          *
* ********* ********* ********* *
*/
int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];


CameraCheckingState cameraCheckingState = Camera_is_not_checking;

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
		if (cameraCheckingState == Camera_is_checking) {
			/// 무궁화 꽃이 피었습니 -> "다"를 외친 후 cameraChecingState 를 위와 같은 경우로 만들었을 때
			/// TODO: - 3초동안 카메라 돌린 후 움직이는 player체크하기 
		}
		else {
			/// TODO: - "무궁화 꽃이 피었습니" 일 때 플레이어들 랜덤 이동.
			update_players_moving_position();
		}
		update_console_info();
	}
}


void print_mugung(void) {
	gotoxy(N_ROW + 1, 0);
	printf("무 "); Sleep(350);
	printf("궁 "); Sleep(400);
	printf("화 "); Sleep(500);
	printf("꽃 "); Sleep(550);
	printf("이 "); Sleep(600);
	printf("피 "); Sleep(450);
	printf("었 "); Sleep(250);
	printf("습 "); Sleep(200);
	printf("니 "); Sleep(100);
	printf("다"); Sleep(3000);
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
		/// 화면에 보여지는 게임 맵 안 back_buf 정보를 temp_map으로 copy
		char before_players_moving_info_buf[ROW_MAX][COL_MAX];
		memcpy(before_players_moving_info_buf, back_buf, sizeof(back_buf));

		/// 플레이어들 특정 확률로 움직여라.
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
					/// 움직인 플레이어 저장.
					moved_players_when_camera_working_state[moved_players_index++] = player;
				}
			}
		}
		memcpy(back_buf, before_players_moving_info_buf, sizeof(back_buf));
	}
	/// TODO: - moved_players_when_camera_working_state에 저장된 특정 플레이어들을 
	///				back_buf로부터 제거하고 다이얼로그로 잠깐보여주는 코드 작성해야합니다.
	///				어디까지? 0..<moved_players_index 까지
	 
	
	
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