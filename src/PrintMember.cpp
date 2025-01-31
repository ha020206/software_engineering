#include "menu.h"
#include "PrintMember.h"
#include "CheckRightValue.h"
#include "CheckInList.h"
#include "ManagerSubFunction.h"
#include "GetDate.h"
#include "SortStruct.h"
#include "ScreenClear.h"


struct member* PirntMemberBook_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int* videoCount, int* sepcialKey, char* loginId) {
	int key = 0;
	while (key != 6) {
		printf("==== 01-03. ȸ�� ��� ��� �� ����/����==== \n");
		memberBook = SortMemberBook(memberBook, * memberCount);
		printf("01. ��ü ȸ�� ���\n02. �뿩 ȸ�� ���\n03. ��ü ȸ�� ���\n04. �Ϲ� ȸ�� ���\n05. ������ ȸ�� ���\n06. ��� ����\n");
		int key = RightMenuKey(6);
		if (key == 1) {
			printf("==== 01. ��ü ȸ�� ��� ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����" , "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *memberCount; i++) {
				printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %d\n", i + 1, memberBook[i].name, memberBook[i].num, memberBook[i].ident, memberBook[i].age, memberBook[i].id , memberBook[i].passWord,  memberBook[i].manager, memberBook[i].pay);
			}
			printf("---------------------------------------------------------------------------------------------------------\n");

			if (*memberCount == 0) {
				printf("... ȸ���� �����ϴ�. \n");
				printf("... �޴��� ���ư��ϴ� \n");
				return memberBook;
			}
			else {
				printf("... �� %d ���� ��� �˻� \n", *memberCount);
				printf("... ���� �۾�?\n");
				printf("... 01. ȸ�� ����\n... 02. ȸ�� ���� ����\n... 03. ȸ�� ��� ����\n");
				int key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("== 01. ȸ�� ���� ==\n");
					int memberIndex = 0;  
					if (*memberCount != 1) {
						printf("... ������ ȸ���� ��ȣ?\n");
						memberIndex = RightMenuKey(*memberCount) - 1;
					}
					memberBook = DelMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					if (* sepcialKey == -1) {
						return memberBook;
					}
					ScreenClear();
				}
				else if (key2 == 2) {
					printf("== 02. ȸ�� ���� ���� ==\n");
					int memberIndex = 0;
					if (*memberCount != 1) {
						printf("... ������ ȸ���� ��ȣ?\n");
						memberIndex = RightMenuKey(*memberCount) - 1;
					}
					memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					if (* sepcialKey == -1) {
						return memberBook;
					}
					ScreenClear();
				}
				else {
					printf("== 03. ȸ�� ��� ���� ==\n");
					printf("... �޴��� ���ư��ϴ� \n");
					return memberBook;
				}
			}
		}
		else if (key == 2) {
			int count = 0;
			printf("==== 02. �뿩 ȸ�� ��� ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *memberCount; i++) {
				int find = 0;
				for (int j = 0; j < *videoCount; j++) {
					if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
						find++;
						if (find == 1) {
							printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %d\n", ++count, memberBook[i].name, memberBook[i].num, memberBook[i].ident, memberBook[i].age, memberBook[i].id, memberBook[i].passWord, memberBook[i].manager, memberBook[i].pay);
						}
						printf("%14s [%s][%s] �ݳ� ������ : [%d]\n", " ", videoBook[j].name, videoBook[j].id, videoBook[j].rentalLimit);

					}
				}
			}

			printf("---------------------------------------------------------------------------------------------------------\n");

			if (count == 0) {
				printf("... �뿩�� ȸ���� �����ϴ�. \n");
				printf("... ����� �����մϴ�. \n");
				return memberBook;
			}
			else {
				printf("... �� %d ���� ��� �˻� \n", count);
				printf("... ���� �۾�?\n");
				printf("... 01. ȸ�� ����\n... 02. ȸ�� ���� ����\n... 03. ȸ�� ��� ����\n");
				int key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("== 01. ȸ�� ���� ==\n");
					int memberIndex = 0;
					int index = 0;
					int find = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						int find = 0;
						for (int j = 0; j < *videoCount; j++) {
							if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
								find++;
								if (find == 1) {
									printIndex[index] = i;
									index++;
								}

							}
						}
					}
					if (count != 1) {
						printf("... ������ ȸ���� ��ȣ?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = DelMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (* sepcialKey == -1) {
						return memberBook;
					}
					
				}
				else if (key2 == 2) {
					printf("== 02. ȸ�� ���� ���� ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						int find = 0;
						for (int j = 0; j < *videoCount; j++) {
							if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
								find++;
								if (find == 1) {
									printIndex[index] = i;
									index++;
								}
							}
						}
					}
					if (count != 1) {
						printf("... ������ ȸ���� ��ȣ?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (* sepcialKey == -1) {
						return memberBook;
					}
				}
				else {
					printf("== 03. ȸ�� ��� ���� ==\n");
					printf("... �޴��� ���ư��ϴ� \n");
					return memberBook;
				}

			}
		}
		else if (key == 3) {
			int count = 0;
			printf("==== 03. ��ü ȸ�� ��� ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *memberCount; i++) {
				int find = 0;
				for (int j = 0; j < *videoCount; j++) {
					if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
						if ( strcmp(videoBook[j].isRentaled, "X") == 0 && videoBook[j].rentalLimit - VideoDateMaker() < 0) {
							find++;
							if (find == 1) {
								printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %d\n", ++count, memberBook[i].name, memberBook[i].num, memberBook[i].ident, memberBook[i].age, memberBook[i].id, memberBook[i].passWord, memberBook[i].manager, memberBook[i].pay);
							}
							printf("%14s [%s][%s] ��ü�ϼ� : [%d]\n", " ", videoBook[j].name, videoBook[j].id, VideoOverDayMaker( videoBook[j].rentalLimit ) );

						}
					}
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");

			if (count == 0) {
				printf("... ��ü�� ȸ���� �����ϴ�. \n");
				printf("... ����� �����մϴ�. \n");
				return memberBook;
			}
			else {
				printf("... �� %d ���� ��� �˻� \n", count);
				printf("... ���� �۾�?\n");
				printf("... 01. ȸ�� ����\n... 02. ȸ�� ���� ����\n... 03. ȸ�� ��� ����\n");
				int key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("== 01. ȸ�� ���� ==\n");
					int memberIndex = 0;
					int index = 0;
					int find = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);

					for (int i = 0; i < *memberCount; i++) {
						int find = 0;
						for (int j = 0; j < *videoCount; j++) {
							if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
								if (strcmp(videoBook[j].isRentaled, "X") == 0 && videoBook[j].rentalLimit - VideoDateMaker() < 0) {
									find++;
									if (find == 1) {
										printIndex[index ++ ] = i;
									}

								}
							}
						}
					}
					if (count != 1) {
						printf("... ������ ȸ���� ��ȣ?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					
					memberBook = DelMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}

				else if (key2 == 2) {
					printf("== 02. ȸ�� ���� ���� ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						int find = 0;
						for (int j = 0; j < *videoCount; j++) {
							if (strcmp(videoBook[j].memberId, memberBook[i].id) == 0) {
								if (strcmp(videoBook[j].isRentaled, "X") == 0 && videoBook[j].rentalLimit - VideoDateMaker() < 0) {
									find++;
									if (find == 1) {
										printIndex[index ++] = i;
									}

								}
							}
						}
					}
					if (count != 1) {
						printf("... ������ ȸ���� ��ȣ?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}
				else {
					printf("== 03. ȸ�� ��� ���� ==\n");
					printf("... �޴��� ���ư��ϴ� \n");
					return memberBook;
				}


			}

		}
		else if (key == 4) {
			int count = 0;
			printf("==== 04. �Ϲ� ȸ�� ��� ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *memberCount; i++) {
				if (strcmp(memberBook[i].manager, "�Ϲ�ȸ��") == 0) {
					printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %d\n", ++count, memberBook[i].name, memberBook[i].num, memberBook[i].ident, memberBook[i].age, memberBook[i].id, memberBook[i].passWord, memberBook[i].manager, memberBook[i].pay);
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");

			if (count == 0) {
				printf("... ȸ���� �����ϴ�. \n");
				printf("... ����� �����մϴ�. \n");
				return memberBook;
			}
			else {
				printf("... �� %d ���� ��� �˻� \n", count);
				printf("... ���� �۾�?\n");
				printf("... 01. ȸ�� ����\n... 02. ȸ�� ���� ����\n... 03. ȸ�� ��� ����\n");
				int key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("== 01. ȸ�� ���� ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						if (strcmp(memberBook[i].manager, "�Ϲ�ȸ��") == 0) {
							printIndex[index++] = i;
						}
					}

					if (count != 1) {
						printf("... ������ ȸ���� ��ȣ?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
				
					memberBook = DelMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}
				else if (key2 == 2) {
					printf("== 02. ȸ�� ���� ���� ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						if (strcmp(memberBook[i].manager, "�Ϲ�ȸ��") == 0) {
							printIndex[index++] = i;
						}
					}
					if (count != 1) {
						printf("... ������ ȸ���� ��ȣ?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}
				else {
					printf("== 03. ȸ�� ��� ���� ==\n");
					printf("... �޴��� ���ư��ϴ� \n");
					return memberBook;
				}

			}
		}
		else if (key == 5) {
			int count = 0;
			printf("==== 05. ������ ȸ�� ��� ====\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("%-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n", "��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
			printf("---------------------------------------------------------------------------------------------------------\n");
			for (int i = 0; i < *memberCount; i++) {
				if (strcmp(memberBook[i].manager, "������") == 0) {
					printf("%-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %d\n", ++count, memberBook[i].name, memberBook[i].num, memberBook[i].ident, memberBook[i].age, memberBook[i].id, memberBook[i].passWord, memberBook[i].manager, memberBook[i].pay);
				}
			}
			printf("---------------------------------------------------------------------------------------------------------\n");
			if (count == 0) {
				printf("... ȸ���� �����ϴ�. \n");
				printf("... ����� �����մϴ�. \n");
				return memberBook;
			}
			else {
				printf("... �� %d ���� ��� �˻� \n", count);
				printf("... ���� �۾�?\n");
				printf("... 01. ȸ�� ����\n... 02. ȸ�� ���� ����\n... 03. ȸ�� ��� ����\n");
				int key2 = RightMenuKey(3);
				if (key2 == 1) {
					printf("== 01. ȸ�� ���� ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						if (strcmp(memberBook[i].manager, "������") == 0) {
							printIndex[index++] = i;
						}
					}

					if (count != 1) {
						printf("... ������ ȸ���� ��ȣ?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = DelMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}
				else if (key2 == 2) {
					printf("== 01. ȸ�� ���� ���� ==\n");
					int memberIndex = 0;
					int index = 0;
					int* printIndex = (int*)malloc(sizeof(int) * count);
					for (int i = 0; i < *memberCount; i++) {
						if (strcmp(memberBook[i].manager, "������") == 0) {
							printIndex[index++] = i;
						}
					}
					if (count != 1) {
						printf("... ������ ȸ���� ��ȣ?\n");
						memberIndex = printIndex[RightMenuKey(count) - 1];
					}
					else {
						memberIndex = printIndex[0];
					}
					
					memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, *videoCount, memberIndex, sepcialKey, loginId);
					free(printIndex);
					printIndex = NULL;
					ScreenClear();
					if (*sepcialKey == -1) {
						return memberBook;
					}
				}
				else {
					printf("== 03. ȸ�� ��� ���� ==\n");
					printf("... �޴��� ���ư��ϴ� \n");
					return memberBook;
				}

			}
		}
		else {
			printf("== 06. ȸ�� ��� ���� ==\n");
			printf("... �޴��� ���ư��ϴ� \n");
			return memberBook;
		}


	}
}
