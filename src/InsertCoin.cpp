#include "InsertCoin.h"
#include "menu.h"
#include "CheckRightValue.h"

int InsertCoin(int index, struct member * memberBook) {
	printf("... 충전할 금액? [ 현재 금액 : %d ]\n", memberBook[index].pay);
	while (1) {
		int again = 0;
		int coin = 0;
		int i = 0;
		int numCount = 0;
		char bufferCoin[10] = { 0 };
		strcpy(bufferCoin, RightStringSize(bufferCoin, 10));
		if (strstr(bufferCoin, " ") || strlen(bufferCoin) == 0) {
			printf("...  공백은 입력할 수 없습니다.\n");
		}
		else {
			for (int i = 0;  bufferCoin[i] != '\0'; i++) {
				if (bufferCoin[i] & 0x80 || isalpha(bufferCoin[i]) ) { // 한글은 입력 받을 수 없음
					again = 1;
					break;
				}
				else if (isdigit(bufferCoin[i])) {
					numCount++;
				}
			}
			if (again != 1) {
				if (strlen(bufferCoin) == numCount) {
					coin = atoi(bufferCoin);
					for (i = 0; i <= 10000000; i++) {
						if (i == coin) {
							printf("... 충전 완료! [ 현재 금액 : %d ]\n", memberBook[index].pay + coin);
							return coin;
						}
					}
				}
			}
		}
		printf("... 충전 금액은, 0에서 10000000까지의 정수만 입력 가능합니다. \n");
	}
}
