// 2023-2 ������α׷��� ����: �޲ٹ� ����
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);

// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("�÷��̾� ��: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}

void intro(void) {
	printf(".--------------------------------------------------------------.\n");
	printf("|                                                              |\n");
	printf("|       _     _          ____  ____         __  __ _           |\n");
	printf("|      | |   | |_   _   / ___|/ ___|_   _  |  \\/  (_)          |\n");
	printf("|   _  | |_  | | | | | | |  _| |  _| | | | | |\\/| | |          |\n");
	printf("|  | |_| | |_| | |_| | | |_| | |_| | |_| | | |  | | |          |\n");
	printf("|   \\___/ \\___/ \\__,_|  \\____|\\____|\\__,_| |_|  |_|_|          |\n");
	printf("|    ____    _    __  __ _____   ____ _____  _    ____ _____   |\n");
	printf("|   / ___|  / \\  |  \\/  | ____| / ___|_   _|/ \\  |  _ \\_   _|  |\n");
	printf("|  | |  _  / _ \\ | |\\/| |  _|   \\___ \\ | | / _ \\ | |_) || |    |\n");
	printf("|  | |_| |/ ___ \\| |  | | |___   ___) || |/ ___ \\|  _ < | |    |\n");
	printf("|   \\____/_/   \\_\\_|  |_|_____| |____/ |_/_/   \\_\\_| \\_\\|_|    |\n");
	printf("|                                                              |\n");
	printf("'--------------------------------------------------------------'\n");
	Sleep(5000);
}

int main(void) {
	jjuggumi_init();
	intro();
	sample();
	//mugunghwa();
	//nightgame();
	//juldarigi();
	//jebi();
	return 0;
}
