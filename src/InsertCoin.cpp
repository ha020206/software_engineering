#include "InsertCoin.h"
#include "menu.h"
#include "CheckRightValue.h"

int InsertCoin(int index, struct member * memberBook) {
	printf("... ������ �ݾ�? [ ���� �ݾ� : %d ]\n", memberBook[index].pay);
	while (1) {
		int again = 0;
		int coin = 0;
		int i = 0;
		int numCount = 0;
		char bufferCoin[10] = { 0 };
		strcpy(bufferCoin, RightStringSize(bufferCoin, 10));
		if (strstr(bufferCoin, " ") || strlen(bufferCoin) == 0) {
			printf("...  ������ �Է��� �� �����ϴ�.\n");
		}
		else {
			for (int i = 0;  bufferCoin[i] != '\0'; i++) {
				if (bufferCoin[i] & 0x80 || isalpha(bufferCoin[i]) ) { // �ѱ��� �Է� ���� �� ����
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
							printf("... ���� �Ϸ�! [ ���� �ݾ� : %d ]\n", memberBook[index].pay + coin);
							return coin;
						}
					}
				}
			}
		}
		printf("... ���� �ݾ���, 0���� 10000000������ ������ �Է� �����մϴ�. \n");
	}
}
