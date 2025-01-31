#include "menu.h"
#include "PrintVideo.h"
#include "CheckRightValue.h"
#include "GetDate.h"
#include "ManagerSubFunction.h"
#include "SortStruct.h"
#include "ScreenClear.h"
#include "SortStruct.h"


struct video * PirntVideoBook_forManager(struct video* videoBook, int* videoCount, struct member* memberBook, int* memberCount) {
	int key = 0;
	while (key != 5) {
		printf("==== 02-03. ���� ��� ��� �� ����/���� ==== \n");
		videoBook = SortVideoBook(videoBook, * videoCount);


		printf("01. ��ü ���� ���\n02. �뿩 ������ ���� ���\n03. �뿩�� ���� ���\n04. ��ü�� ���� ���\n05. ���� ��� ����\n");
		key = RightMenuKey(5);
		if (key == 1) {
			printf("==== 01. ��ü ���� ��� ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *videoCount; i++) {
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", i + 1, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled, videoBook[i].memberId, videoBook[i].rentalDate, videoBook[i].rentalLimit);
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (*videoCount == 0) {
				printf("... ������ �����ϴ�. \n");
				ScreenClear();
				return videoBook;
			}
			else {
				printf("... �� %d �׸� ���\n", *videoCount);
				printf("... ���� �۾�?\n");
				printf("... 01. ���� ����\n... 02. ���� ����\n... 03. ���� ��� ����\n");
				int key2 = 0;
				key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("01. ���� ����\n");
					int videoIndex = 0;
					if (*videoCount != 1) {
						printf("... ������ ������ ��ȣ?\n");
						videoIndex = RightMenuKey(*videoCount) - 1;
					}
					videoBook = DelVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					ScreenClear();
				}
				else if (key2 == 2) {
					printf("02. ���� ����\n");
					int videoIndex = 0;
					if (*videoCount != 1) {
						printf("... ������ ������ ��ȣ?\n");
						videoIndex = RightMenuKey(*videoCount) - 1;
					}
					videoBook = ChangeVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					ScreenClear();
				}
				else {
					printf("03. ���� ��� ����\n");
					return videoBook;
				}
			}
		}

		else if (key == 2) {
			int count = 0;
			printf("==== 02. �뿩 ������ ���� ��� ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *videoCount; i++) {
				if (strcmp(videoBook[i].isRentaled, "O") == 0) {
					count++;
					printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", count, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled, videoBook[i].memberId, videoBook[i].rentalDate, videoBook[i].rentalLimit);
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (count == 0) {
				printf("... �뿩 ������ ������ �����ϴ�. \n");
				ScreenClear();
				return videoBook;

			}
			else {
				printf("... �� %d �׸� ���\n", count);
				printf("... ���� �۾�?\n");
				printf("... 01. ���� ����\n... 02. ���� ����\n... 03. ���� ��� ����\n");
				int key2 = 0;
				key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("01. ���� ����\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if (strcmp(videoBook[i].isRentaled, "O") == 0) {
							printIndex[index++] = i;
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... ������ ������ ��ȣ?\n");
						videoIndex = printIndex[RightMenuKey(*videoCount) - 1];
					}
					else {
						videoIndex = printIndex[0];
					}
					videoBook = DelVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else if (key2 == 2) {
					printf("02. ���� ����\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if (strcmp(videoBook[i].isRentaled, "O") == 0) {
							printIndex[index++] = i;
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... ������ ������ ��ȣ?\n");
						videoIndex = printIndex[RightMenuKey(*videoCount) - 1];
					}
					else {
						videoIndex = printIndex[0];
					}

					videoBook = ChangeVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else {
					printf("03. ���� ��� ����\n");
					return videoBook;
				}
			}
		}
		else if (key == 3) {
			int count = 0;
			printf("==== 03. �뿩�� ���� ��� ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *videoCount; i++) {
				if (strcmp(videoBook[i].isRentaled, "X") == 0) {
					count++;
					printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", count, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled, videoBook[i].memberId, videoBook[i].rentalDate, videoBook[i].rentalLimit);

				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (count == 0) {
				printf("... �뿩�� ������ �����ϴ�. \n");
				ScreenClear();
				return videoBook;
			}
			else {
				printf("... �� %d �׸� ���\n", count);
				printf("... ���� �۾�?\n");
				printf("... 01. ���� ����\n... 02. ���� ����\n... 03. ���� ��� ����\n");
				int key2 = 0;
				key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("01. ���� ����\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if (strcmp(videoBook[i].isRentaled, "X") == 0) {
							printIndex[index] = i;
							index++;
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... ������ ������ ��ȣ?\n");
						videoIndex = printIndex[RightMenuKey( count ) - 1];
					}
					else {
						videoIndex = printIndex[0];
					}

					videoBook = DelVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else if (key2 == 2) {
					printf("02. ���� ����\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if (strcmp(videoBook[i].isRentaled, "X") == 0) {
							printIndex[index++] = i;
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... ������ ������ ��ȣ?\n");
						videoIndex = printIndex[RightMenuKey(*videoCount) - 1];
					}
					else {
						videoIndex = printIndex[0];
					}
					videoBook = ChangeVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else {
					printf("03. ���� ��� ����\n");
					return videoBook;
				}
			}
		}
		else if (key == 4) {
			int count = 0;
			int today = VideoDateMaker();
			printf("==== 04. ��ü�� ���� ��� ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���", "�뿩��(ID)", "�뿩��", "�ݳ�������");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *videoCount; i++) {
				if (strcmp(videoBook[i].isRentaled, "X") == 0) {
					if (videoBook[i].rentalLimit - today < 0) {
						count++;
						printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s %-10s %-10d %-10d \n", count, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled, videoBook[i].memberId, videoBook[i].rentalDate, videoBook[i].rentalLimit);
					}
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (count == 0) {
				printf("... ��ü�� ������ �����ϴ�. \n");
				ScreenClear();
				return videoBook;
			}
			else {
				printf("... �� %d �׸� ���\n", count);
				printf("... ���� �۾�?\n");
				printf("... 01. ���� ����\n... 02. ���� ����\n... 03. ���� ��� ����\n");
				int key2 = 0;
				key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("01. ���� ����\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if (videoBook[i].rentalLimit != 0) {
							if ((strcmp(videoBook[i].isRentaled, "X") == 0) && videoBook[i].rentalLimit - today < 0) {
								printIndex[index] = i;
								index++;
							}
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... ������ ������ ��ȣ?\n");
						videoIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						videoIndex = printIndex[ 0 ];
					}
					videoBook = DelVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else if (key2 == 2) {
					printf("02. ���� ����\n");
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *videoCount; i++) {
						if ((strcmp(videoBook[i].isRentaled, "X") == 0) && videoBook[i].rentalLimit - today < 0) {
							if (videoBook[i].rentalLimit != 0) {
								printIndex[index] = i;
								index++;
							}
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... ������ ������ ��ȣ?\n");
						videoIndex = printIndex[ RightMenuKey(count) - 1 ];
					}
					else {
						videoIndex = printIndex[0];
					}

					videoBook = ChangeVideo_forManager(memberBook, memberCount, videoBook, videoCount, videoIndex);

					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else {
					printf("03. ���� ��� ����\n");
					return videoBook;
				}
			}
		}
		else {
			printf("==== 05. ���� ��� ���� ====\n");
			return videoBook;
		}

	}
}
	



struct video * PirntVideoBook_forMember(struct video * videoBook, int videoCount, struct member * memberBook, int memberCount, int userIndex ) {

	int key = 0;
	while (key != 4) {

		printf("==== 03. ���� ��� �� �뿩 ==== \n");

		printf("01. ��ü ���� ���\n02. �뿩 ������ ���� ���\n03. �ֽ� ���� ���\n04. ���� ��� ����\n");
		key = RightMenuKey(4);
		if (key == 1) {
			printf("==== 01. ��ü ���� ��� ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < videoCount; i++) {
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s \n", i + 1, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled);
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (videoCount == 0) {
				printf("...  ������ �����ϴ�. \n");
				printf("...  �޴��� ���ư��ϴ�. \n");
				return videoBook;
			}
			else {
				printf("... �� %d �׸� ���\n", videoCount);
				printf("... ���� �۾�?\n");
				printf("... 01. ���� �뿩\n... 02. ���� ��� ����\n");
				int key2 = 0;
				key2 = RightMenuKey(2);
				if (key2 == 1) {
					printf("01. ���� �뿩\n");
					int videoIndex = 0;
					if (videoCount != 1) {
						printf("... �뿩�� ������ ��ȣ?\n");
						videoIndex = RightMenuKey(videoCount) - 1;
					}
					videoBook = RentVideo_forMember(memberBook, &memberCount, videoBook, &videoCount, videoIndex, userIndex);
					ScreenClear();
				}
				else {
					printf("02. ���� ��� ����\n");
					return videoBook;
				}
			}
		}
		else if (key == 2) {
			int count = 0;
			printf("==== 02. �뿩 ������ ���� ��� ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < videoCount; i++) {
				if (strcmp(videoBook[i].isRentaled, "O") == 0) {
					printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s \n", count + 1, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled);
					count++;
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (count == 0) {
				printf("... �뿩 ������ ������ �����ϴ�. \n");
				printf("...  �޴��� ���ư��ϴ�. \n");
				return videoBook;
			}
			else {
				printf("... �� %d �׸� ���\n", count);
				printf("... ���� �۾�?\n");
				printf("... 01. ���� �뿩\n... 02. ���� ��� ����\n");
				int key2 = 0;
				key2 = RightMenuKey(2);
				if (key2 == 1) {
					printf("02. ���� �뿩\n");
					int index = 0;

					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < videoCount; i++) {
						if (strcmp(videoBook[i].isRentaled, "O") == 0) {
							printIndex[index++] = i;
						}
					}
					int videoIndex = 0;
					if (count != 1) {
						printf("... �뿩�� ������ ��ȣ?\n");
						videoIndex =  printIndex[RightMenuKey(videoCount) - 1];
					}
					else {
						videoIndex = printIndex[0];
					}
					videoBook = RentVideo_forMember(memberBook, &memberCount, videoBook, &videoCount, videoIndex, userIndex);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
				}
				else {
					printf("02. ���� ��� ����\n");
					return videoBook;
				}
			}
		}
		else if (key == 3) {
			int count = 0;
			printf("==== 03. �ֽ� ���� ��� ====\n");
			videoBook = SortVideoBook_byDate(videoBook, videoCount);
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-20s %-10s %-20s %-10s %-10s %-10s %-10s \n", "��ȣ", "�����̸�", "����", "����������ȣ", "��ϳ�¥", "��������", "���ѿ���", "�뿩���ɿ���");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < videoCount; i++) {
				printf("%-3d %-20s %-10s %-20s %-10d %-10d %-10d %-10s \n", i + 1, videoBook[i].name, videoBook[i].maker, videoBook[i].id, videoBook[i].upDate, videoBook[i].price, videoBook[i].age, videoBook[i].isRentaled);
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (videoCount == 0) {
				printf("...  ������ �����ϴ�. \n");
				printf("...  �޴��� ���ư��ϴ�. \n");
				videoBook = SortVideoBook(videoBook, videoCount);
				return videoBook;
			}
			else {
				printf("... �� %d �׸� ���\n", videoCount);
				printf("... ���� �۾�?\n");
				printf("... 01. ���� �뿩\n... 02. ���� ��� ����\n");
				int key2 = 0;
				key2 = RightMenuKey(2);
				if (key2 == 1) {
					printf("01. ���� �뿩\n");
					int videoIndex = 0;
					if (videoCount != 1) {
						printf("... �뿩�� ������ ��ȣ?\n");
						videoIndex = RightMenuKey(videoCount) - 1;
					}
					videoBook = RentVideo_forMember(memberBook, &memberCount, videoBook, &videoCount, videoIndex, userIndex);
					ScreenClear();
				}
				else {
					printf("02. ���� ��� ����\n");
					videoBook = SortVideoBook(videoBook, videoCount);
					return videoBook;
				}
			}
		}
		else {
			printf("04. ���� ��� ����\n");
			return videoBook;
		}

	}
}
