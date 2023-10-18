#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_UP      0
#define DIR_DOWN    1
#define DIR_LEFT    2
#define DIR_RIGHT   3

void sample_init(void);
void move_manual(key_t key);
void move_random(int i, int dir);
void move_tail(int i, int nx, int ny);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�

void sample_init(void) {
    map_init(14, 40);
    int x, y;
    for (int i = 0; i < n_player; i++) {
        // ���� �ڸ��� ������ �ٽ� ����
        do {
            x = randint(2, N_ROW - 3);
            y = randint(38, N_COL - 2);
        } while (!placable(x, y));
        px[i] = x;
        py[i] = y;
        period[i] = randint(100, 500);

        back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
    }

    //���� 2���� �̰͵� ������ �ް� �ٲ����(����)
    back_buf[5][1] = '#';
    back_buf[6][1] = '#';
    back_buf[7][1] = '#';
    back_buf[8][1] = '#';



    tick = 0;
}


void move_manual(key_t key) {
    // �� �������� ������ �� x, y�� delta
    static int dx[4] = { -1, 1, 0, 0 };
    static int dy[4] = { 0, 0, -1, 1 };

    int dir;  // ������ ����(0~3)
    switch (key) {
    case K_UP: dir = DIR_UP; break;
    case K_DOWN: dir = DIR_DOWN; break;
    case K_LEFT: dir = DIR_LEFT; break;
    case K_RIGHT: dir = DIR_RIGHT; break;
    default: return;
    }

    // �������� ���� �ڸ�
    int nx, ny;
    nx = px[0] + dx[dir];
    ny = py[0] + dy[dir];
    if (!placable(nx, ny)) {
        return;
    }

    move_tail(0, nx, ny);
}

// 0 <= dir < 4�� �ƴϸ� ����
void move_random(int player, int dir) {
    int p = player;  // �̸��� ��...
    int nx, ny;  // �������� ������ ���� �ڸ�


    // ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	
    int a = 0, b = 0, c = 0, d = 0;
    int x[4] = { 0,-1,1,0 };
    int y[4] = { -1.0,0,0 };
    int i;
    do {
        i = randint(0, 101);
        if (0 < i <= 70 && a == 0) {
            nx = px[p] + x[0];
            ny = py[p] + y[0];
            a += 1;
        }
        else if (70 < i <= 80 && b == 0) {
            nx = px[p] + x[1];
            ny = py[p] + y[1];
            b += 1;
        }
        else if (80 < i <= 90 && c == 0) {
            nx = px[p] + x[2];
            ny = py[p] + y[2];
            c += 1;
        }
        else if (90 < i <= 100 && d == 0) {
            nx = px[p] + x[3];
            ny = py[p] + y[3];
            d += 1;
        }
    } while (!placable(nx, ny));
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    move_tail(p, nx, ny);

}

// back_buf[][]�� ���
void move_tail(int player, int nx, int ny) {
    int p = player;  // �̸��� ��...
    back_buf[nx][ny] = back_buf[px[p]][py[p]];
    back_buf[px[p]][py[p]] = ' ';
    px[p] = nx;
    py[p] = ny;
}

void sample(void) {

    sample_init();

    system("cls");
    display();
    Sleep(1000);
    while (1) {
        // player 0�� ������ ������(4����)
        key_t key = get_key();
        if (key == K_QUIT) {
            break;
        }
        else if (key != K_UNDEFINED) {
            move_manual(key);
        }

        for (int i = 1; i < n_player; i++) {
            if (tick % period[i] == 0) {
                move_random(i, -1);
            }
        }

        // tick ���� 500�� ����� ���� ready �޽��� ���
        if (tick == 500) {
            dialog("READY");
            Sleep(1000);
        }

        display();
        Sleep(10);
        tick += 10;
    }
}