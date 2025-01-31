#include "menu.h"
#include "ScreenClear.h"



void ScreenClear(void) {
	printf("... 계속하려면 아무 키나 눌러주세요.\n");
	getchar(); 
	printf("\n... 데이터 저장중 ");
	for (int i = 0; i < 3; i++) {
		printf("%c", '.');
		Sleep(800); // 0.8초씩 3번 점을 출력하여 화면이 바로 지워지는것을 방지함 
	}

	system("cls");

}
