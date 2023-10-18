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

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // Í∞??åÎ†à?¥Ïñ¥ ?ÑÏπò, ?¥Îèô Ï£ºÍ∏∞

void sample_init(void) {
    map_init(15, 40);
    int x, y;
    for (int i = 0; i < n_player; i++) {
        // Í∞ôÏ? ?êÎ¶¨Í∞Ä ?òÏò§Î©??§Ïãú ?ùÏÑ±
        do {
            x = randint(1, N_ROW - 2);
            y = randint(1, N_COL - 2);
        } while (!placable(x, y));
        px[i] = x;
        py[i] = y;
        period[i] = randint(100, 500);

        back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
    }

    tick = 0;
}

void move_manual(key_t key) {
    // Í∞?Î∞©Ìñ•?ºÎ°ú ?ÄÏßÅÏùº ??x, yÍ∞?delta
    static int dx[4] = { -1, 1, 0, 0 };
    static int dy[4] = { 0, 0, -1, 1 };

    int dir;  // ?ÄÏßÅÏùº Î∞©Ìñ•(0~3)
    switch (key) {
    case K_UP: dir = DIR_UP; break;
    case K_DOWN: dir = DIR_DOWN; break;
    case K_LEFT: dir = DIR_LEFT; break;
    case K_RIGHT: dir = DIR_RIGHT; break;
    default: return;
    }

    // ?ÄÏßÅÏó¨???ìÏùº ?êÎ¶¨
    int nx, ny;
    nx = px[0] + dx[dir];
    ny = py[0] + dy[dir];
    if (!placable(nx, ny)) {
        return;
    }

    move_tail(0, nx, ny);
}

// 0 <= dir < 4Í∞Ä ?ÑÎãàÎ©??úÎç§
void move_random(int player, int dir) {
    int p = player;  // ?¥Î¶Ñ??Í∏∏Ïñ¥??..
    int nx, ny;  // ?ÄÏßÅÏó¨???§Ïùå???ìÏùº ?êÎ¶¨

    // ?ÄÏßÅÏùº Í≥µÍ∞Ñ???ÜÎäî Í≤ΩÏö∞???ÜÎã§Í≥?Í∞Ä??Î¨¥Ìïú Î£®ÌîÑ??Îπ†Ïßê)    

    do {
        nx = px[p] + randint(-1, 1);
        ny = py[p] + randint(-1, 1);
    } while (!placable(nx, ny));

    move_tail(p, nx, ny);
}

// back_buf[][]??Í∏∞Î°ù
void move_tail(int player, int nx, int ny) {
    int p = player;  // ?¥Î¶Ñ??Í∏∏Ïñ¥??..
    back_buf[nx][ny] = back_buf[px[p]][py[p]];
    back_buf[px[p]][py[p]] = ' ';
    px[p] = nx;
    py[p] = ny;
}

void sample(void) {
    sample_init();

    system("cls");
    display();
    while (1) {
        // player 0Îß??êÏúºÎ°??ÄÏßÅÏûÑ(4Î∞©Ìñ•)
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

        // tick Í∞íÏù¥ 500??Î∞∞Ïàò???åÎßå READY Î©îÏãúÏßÄ Ï∂úÎ†•
        if (tick == 500) {
            dialog("READY");
            Sleep(1000);
        }

        display();
        Sleep(10);
        tick += 10;
    }
}