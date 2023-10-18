#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"

#define DIALOG_DURATION_SEC		4

void draw(void);
void print_status(void);

// (zero-base) row��, col���� Ŀ�� �̵�
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row��, col���� ch ���
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

void map_init(int n_row, int n_col) {
	// �� ���۸��� ������ ����
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
		back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '*' : ' ';
		}
	}
}

// back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
bool placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// ��ܿ� ����, �ϴܿ��� ���� ���¸� ���
void display(void) {
	draw();
	gotoxy(N_ROW + 4, 0);  // �߰��� ǥ���� ������ ������ �ʰ� ����â ������ �� ������ ���
	print_status();
}

void draw(void) {
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void print_status(void) {
	printf("no. of players left: %d\n", n_alive);
	for (int p = 0; p < n_player; p++) {
		printf("player %2d: %5s\n", p, player[p] ? "alive" : "DEAD");
	}
}

void dialog(char message[]) {
    // ���� ���� ���� ����
    char temp_buf[ROW_MAX][COL_MAX];
    int center_row = N_ROW / 2;
    int center_col = N_COL / 2;
    int msg_length = strlen(message);
    int box_width = max(msg_length, 18) + 4;
    int box_start_col = center_col - box_width / 2;
    int box_end_col = center_col + box_width / 2;

    for (int i = 0; i < ROW_MAX; i++) {
        for (int j = 0; j < COL_MAX; j++) {
            temp_buf[i][j] = back_buf[i][j];
        }
    }

    // ��ȭ ���ڸ� �� ���� ǥ��
    for (int i = DIALOG_DURATION_SEC; i >= 0; --i) {
        if (i != DIALOG_DURATION_SEC) {
            Sleep(1000);
        }

        for (int row = center_row - 1; row <= center_row + 3; ++row) {
            for (int col = box_start_col - 1; col <= box_end_col + 1; ++col) {
                back_buf[row][col] = ' ';
            }
        }
        for (int row = center_row - 1; row <= center_row + 3; ++row) {
            for (int col = box_start_col - 1; col <= box_end_col + 1; ++col) {
                if (row == center_row - 1 || row == center_row + 3 || col == box_start_col - 1 || col == box_end_col + 1)
                    back_buf[row][col] = '*';
            }
        }

        gotoxy(center_row + 1, box_start_col + 4);
        printf("%s", message);
        gotoxy(center_row + 1, box_start_col + 2);
        printf("%d ", i);

        draw();
    }

    gotoxy(center_row + 1, box_start_col + 2);
    for (int disappear = 0; disappear < msg_length + 2; disappear++) {
        printf(" ");
    }

    // ���� ���·� ����
    for (int i = 0; i < ROW_MAX; i++) {
        for (int j = 0; j < COL_MAX; j++) {
            back_buf[i][j] = temp_buf[i][j];
        }
    }

    display();
}

