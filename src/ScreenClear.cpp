#include "menu.h"
#include "ScreenClear.h"



void ScreenClear(void) {
	printf("... ����Ϸ��� �ƹ� Ű�� �����ּ���.\n");
	getchar(); 
	printf("\n... ������ ������ ");
	for (int i = 0; i < 3; i++) {
		printf("%c", '.');
		Sleep(800); // 0.8�ʾ� 3�� ���� ����Ͽ� ȭ���� �ٷ� �������°��� ������ 
	}

	system("cls");

}
