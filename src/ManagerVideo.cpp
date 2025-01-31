#include "menu.h"
#include "ManagerVideo.h"
#include "CheckRightValue.h"
#include "CheckInList.h"
#include "GetDate.h"
#include "InsertCoin.h"
#include "ManagerSubFunction.h"
#include "SortStruct.h"

// ������ ���� ���� ���� �� ����
	struct video * SearchvideoBook_forManager(struct video * videoBook, int * videoCount, struct member * memberBook , int * memberCount ) {

		char searchKey[40] = { 0 };
		int index = 0; // �˻��ϴ� �׸��� �����ϴ� �ε���
		printf("... �˻� �� ���� ?\n");
		strcpy(searchKey, RightStringSize(searchKey, 40));
		videoBook = SortVideoBook(videoBook, * videoCount);
		for (int i = 0; i < *videoCount; i++) {
			if (strstr(videoBook[i].name, searchKey) || strstr(videoBook[i].id, searchKey) || strstr(videoBook[i].maker, searchKey) || strstr(videoBook[i].memberId, searchKey) ) {
				index++;
			}
		}

		if (index == 0) {
			printf("... �˻���� ��ġ�ϴ� ����� �����ϴ�. \n");
			printf("... �޴��� ���ư��ϴ�.\n");
			return videoBook;
		}

		printf("... �� %d ���� ��� �˻� \n", index);
		int* searckIndex = (int*)malloc(sizeof(int) * index);
		index = 0;
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
		printf("---------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < *videoCount; i++) {
			if (strstr(videoBook[i].name, searchKey) || strstr(videoBook[i].id, searchKey) || strstr(videoBook[i].maker, searchKey))  {
				searckIndex[index++] = i;
				printf("%3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n",index, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled, videoBook[i].memberId, videoBook[i].rentalDate, videoBook[i].rentalLimit);
			}
		}
		printf("---------------------------------------------------------------------------------------------------------\n");

		int key = 0;
		int listIndex = index - 1;
		while (key != 3) {
			videoBook = SortVideoBook(videoBook, *videoCount);
			printf("... ���� �۾�? \n");
			printf("01. ���� ����\n02. ���� ���� ����\n03. ���� �˻� �� ����/���� ����\n");
			key = RightMenuKey(3);

			if (key == 1) {
				if (index != 1) {
					printf("... ������ ���ϴ� ����� ��ȣ?\n");
					listIndex = RightMenuKey(index) - 1;
				}

				videoBook = DelVideo_forManager(memberBook, memberCount, videoBook, videoCount, searckIndex[listIndex]);
				free(searckIndex);
				searckIndex = NULL;
				return videoBook;
			}
			else if (key == 2) {
				if (index != 1) {
					printf("... ������ ���ϴ� ����� ��ȣ?\n");
					listIndex = RightMenuKey(index) - 1;
				}
				videoBook = ChangeVideo_forManager(memberBook, memberCount, videoBook, videoCount, searckIndex[listIndex]);
				free(searckIndex);
				searckIndex = NULL;
				return videoBook;
				
			}
			else if (key == 3) {
				printf("03. ���� �˻� �� ����/���� ����\n");
				free(searckIndex);
				searckIndex = NULL;
				printf("... �޴��� ���ư��ϴ�.\n");
				return videoBook;
			}
		}
	}

	// ȸ�� ���� ���� Ž�� �Լ� 
	struct video * SearchvideoBook_forMember(struct video* videoBook, int* videoCount, struct member* memberBook, int* memberCount, int userIndex ) {

		char searchKey[40] = { 0 };
		int count = 0;
		printf("... �˻� �� ���� ?\n");
		strcpy(searchKey, RightStringSize(searchKey, 40));

		for (int i = 0; i < *videoCount; i++) {
			if (strstr(videoBook[i].name, searchKey) || strstr(videoBook[i].id, searchKey) || strstr(videoBook[i].maker, searchKey)) {
				count++;
			}
		}
		if (count == 0) {
			printf("... �˻���� ��ġ�ϴ� ����� �����ϴ�. \n");
			printf("... �޴��� ���ư��ϴ�.\n");
			return videoBook;
		}
		int* searckIndex = (int*)malloc(sizeof(int) * count);
		printf("... �� %d ���� ��� �˻� \n", count);
		count = 0;
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("%3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s  \n","��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���");
		printf("---------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < * videoCount; i++) {
			if (strstr(videoBook[i].name, searchKey) || strstr(videoBook[i].id, searchKey) || strstr(videoBook[i].maker, searchKey)) {
				searckIndex[count++] = i;
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s  \n", count, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled );
			}
		}
		printf("---------------------------------------------------------------------------------------------------------\n");
		int key = 0;
		while (key != 2) {
			printf("... ���� �۾�? \n");
			printf("01. ���� �뿩\n02. ���� �˻� �� �뿩 ����\n");
			key = RightMenuKey(2);

			if (key == 1) {
				printf("== 01. ���� �뿩 == \n");
				int listIndex = 0;
				if (count != 1) {
					printf("... �뿩�� ���ϴ� ����� ��ȣ?\n");
					listIndex = RightMenuKey(count) - 1;
				}
				videoBook = RentVideo_forMember(memberBook, memberCount, videoBook, videoCount, searckIndex[listIndex], userIndex);
				free(searckIndex);
				searckIndex = NULL;
				return videoBook;

			}
			else
			{
				printf("== 02. ���� �˻� �� �뿩 ���� == \n");
				free(searckIndex);
				searckIndex = NULL;
				return videoBook;

			}
		}
	}
