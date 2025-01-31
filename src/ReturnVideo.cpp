#include "ReturnVideo.h"
#include "menu.h"
#include "CheckRightValue.h"
#include "GetDate.h"
#include "InsertCoin.h"
#include "ScreenClear.h"

struct video * ReturnVideo_forMember(struct member* memberBook, int* memberCount, struct video* videoBook, int videoCount, char * loginId, int userIndex) {

	int key = 0;
	while (key != 3) {
		printf("==== 04. ���� �ݳ� ==== \n");
		printf("... �뿩�� ���� ����� ����մϴ�.\n");
		int count = 0;
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩��ID", "�ݳ�������");
		printf("---------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < videoCount; i++) {
			if (strcmp(videoBook[i].memberId, loginId) == 0) {
				count++;
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10d \n", count, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].memberId, videoBook[i].rentalLimit);
			}
		}
		printf("---------------------------------------------------------------------------------------------------------\n");

		if (count == 0) {
			printf("... �뿩�� ������ �����ϴ�.\n");
			printf("... �޴��� ���ư��ϴ�.\n");
			return videoBook;
		}

		printf("... �� %d ���� �׸� ���\n", count);
		printf("... ���� �۾�?\n");
		printf("01. ���� �뿩 ����\n02. ���� �ݳ�\n03. ���� �ݳ� ����\n");
		int key2 = RightMenuKey(3);
		int listIndex = 0;
		if (key2 == 1) {
			printf("== 01. ���� �뿩 ���� == \n");
			int* returnIndex = (int*)malloc(sizeof(int) * count);
			int index = 0;
			for (int i = 0; i < videoCount; i++) {
				if (strcmp(videoBook[i].memberId, loginId) == 0) {
					returnIndex[index++] = i;
				}
			}

			if (count != 1) {

				printf("... �뿩�� ������ �׸��� ��ȣ�� �����ϼ���.\n");
				listIndex = returnIndex[ RightMenuKey(count) - 1 ];

				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩��ID", "�ݳ�������");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10d \n", 1, videoBook[listIndex].name, videoBook[listIndex].maker, videoBook[listIndex].id, videoBook[listIndex].upDate, videoBook[listIndex].price, videoBook[listIndex].age, videoBook[listIndex].memberId, videoBook[listIndex].rentalLimit);
				printf("---------------------------------------------------------------------------------------------------------\n");
			}
			else {
				listIndex = returnIndex[0];
			}


			if (videoBook[listIndex].rentalLimit - VideoDateMaker() < 0) {
				int overDay = 0;
				printf("... ��ü�� �ϼ� [ %d ]�� ���� ��ü�ᰡ �ֽ��ϴ�.\n", overDay = VideoOverDayMaker(videoBook[listIndex].rentalLimit));
				int change = overDay * videoBook[listIndex].price;
				printf("... [ ���� �����ݾ� :%d ��]\n", memberBook[userIndex].pay);
				printf("------- ������ -------\n");
				printf("... �Ϸ� �뿩�� [%d]��\n", videoBook[listIndex].price);
				printf("... �� [ %d ] �� ��ü \n", overDay);
				printf("... ���� ���� �ݾ� [%d]��\n", change);
				printf("----------------------\n");
				while (memberBook[userIndex].pay - change < 0) {
					printf("... ���� �ݾ��� �����մϴ�. ȸ�� �ݾ� ���� �������� �̵��մϴ�.\n");
					memberBook[userIndex].pay += InsertCoin(userIndex, memberBook);
				}
				memberBook[userIndex].pay -= change;
				printf("... ���� �Ϸ�! [ ���� �ܾ� :%d ��]\n", memberBook[userIndex].pay);
				videoBook[listIndex].rentalLimit = VideoRentalLimitMaker(0);
			}

			printf("... ������ �뿩 �ϼ� ? ( �뿩�� 1�� ~ 14�� ���� �����մϴ�. ) [ ���� �ݳ� ������ : %d ]\n", videoBook[listIndex].rentalLimit);
			int rentalDay = RightMenuKey(14);

			int change = rentalDay * videoBook[listIndex].price;
			printf("... [ ���� �����ݾ� :%d ��]\n", memberBook[userIndex].pay);
			printf("------- ������ -------\n");
			printf("... �Ϸ� �뿩�� [%d]��\n", videoBook[listIndex].price);
			printf("... �� [ %d ] �� �뿩 ���� \n", rentalDay);
			printf("... ���� ���� �ݾ� [%d]��\n", change);
			printf("----------------------\n");

			while (memberBook[userIndex].pay - change < 0) {
				printf("... ȸ���� ���� �ݾ��� �����մϴ�. ȸ�� �ݾ� ���� �������� �̵��մϴ�.\n");
				memberBook[userIndex].pay += InsertCoin(userIndex, memberBook);
			}

			memberBook[userIndex].pay -= change;
			printf("... ���� �Ϸ�! [ ȸ���� �ܾ� :%d ��]\n", memberBook[userIndex].pay);

			videoBook[listIndex].rentalLimit = VideoOverRentDayMaker(videoBook[listIndex].rentalLimit, rentalDay);

			printf("... ���� �Ϸ� !\n");

			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩��ID", "�ݳ�������");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10d \n", 1, videoBook[listIndex].name, videoBook[listIndex].maker, videoBook[listIndex].id, videoBook[listIndex].upDate, videoBook[listIndex].price, videoBook[listIndex].age, videoBook[listIndex].memberId, videoBook[listIndex].rentalLimit);
			printf("---------------------------------------------------------------------------------------------------------\n");
			
			free(returnIndex);
			returnIndex = NULL;
			ScreenClear();


		}
		else if (key2 == 2) {
			printf("== 02. ���� �ݳ� == \n");
			int * returnIndex = (int*)malloc(sizeof(int) * count);
			int index = 0;
			for (int i = 0; i < videoCount; i++) {
				if (strcmp(videoBook[i].memberId, loginId) == 0) {
					returnIndex[index++] = i;
				}
			}

			if (count != 1) {

				printf("... �ݳ��� �׸��� ��ȣ�� �����ϼ���.\n");
				listIndex  = RightMenuKey(count) - 1;

				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩��ID", "�ݳ�������");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10d \n", 1, videoBook[returnIndex[listIndex]].name, videoBook[returnIndex[listIndex]].maker, videoBook[returnIndex[listIndex]].id, videoBook[returnIndex[listIndex]].upDate, videoBook[returnIndex[listIndex]].price, videoBook[returnIndex[listIndex]].age, videoBook[returnIndex[listIndex]].memberId, videoBook[returnIndex[listIndex]].rentalLimit);
				printf("---------------------------------------------------------------------------------------------------------\n");
			}

			printf("... �ݳ��� �����մϴ�.\n");
			if ( (videoBook[returnIndex[listIndex]].rentalLimit - VideoDateMaker() ) < 0 ) {
				int overDay = VideoOverDayMaker(videoBook[returnIndex[listIndex]].rentalLimit) ;
				int overPrice = videoBook[returnIndex[listIndex]].price * overDay;
				printf("... �ݳ� ������ �������ϴ�.\n");
				printf("... ��ü�ᰡ �ΰ��˴ϴ�.\n");
				printf("... [ ���� �����ݾ� :%d ��]\n", memberBook[userIndex].pay);
				printf("------- ������ -------\n");
				printf("... �Ϸ� �뿩�� [%d]��\n", videoBook[returnIndex[listIndex]].price);
				printf("... �� [ %d ] �� �ʰ� �뿩\n", overDay);
				printf("... ���� ���� �ݾ� [%d]��\n", overPrice);
				printf("----------------------\n");

				while (memberBook[userIndex].pay - overPrice < 0) {
					printf("... ���� �ݾ��� �����մϴ�. �ݾ� ���� �������� �̵��մϴ�.\n");
					memberBook[userIndex].pay += InsertCoin(userIndex, memberBook);

				}
				memberBook[userIndex].pay -= overPrice;
				printf("... [%d]�� ����\n", overPrice);
				printf("... ���� �ܾ� [%d]�� \n", memberBook[userIndex].pay);

			}
			
			videoBook[returnIndex[listIndex]].rentalLimit = 0;
			videoBook[returnIndex[listIndex]].rentalDate = 0;
			strcpy(videoBook[returnIndex[listIndex]].isRentaled, "O");
			strcpy(videoBook[returnIndex[listIndex]].memberId, "-");
			printf("... �ݳ� �Ϸ� !\n");


			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩��ID", "�ݳ�������");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10d \n", 1, videoBook[returnIndex[listIndex]].name, videoBook[returnIndex[listIndex]].maker, videoBook[returnIndex[listIndex]].id, videoBook[returnIndex[listIndex]].upDate, videoBook[returnIndex[listIndex]].price, videoBook[returnIndex[listIndex]].age, videoBook[returnIndex[listIndex]].memberId, videoBook[returnIndex[listIndex]].rentalLimit);
			printf("---------------------------------------------------------------------------------------------------------\n");
			
			free(returnIndex);
			returnIndex = NULL;
			ScreenClear();
		}
		else {
			printf("... �޴��� ���ư��ϴ�.\n");
			return videoBook;
		
		}
	}
}