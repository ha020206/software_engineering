#include "menu.h"
#include "GetDate.h"
#include "FileReadAndWrite.h"
#include "CheckInList.h"
#include "CheckRightValue.h"
#include "JoinMember.h"
#include "JoinVideo.h"
#include "LogIn.h"
#include "ManagerMember.h"
#include "ManagerVideo.h"
#include "PrintMember.h"
#include "PrintVideo.h"
#include "ScreenClear.h"
#include "InsertCoin.h"
#include "SortStruct.h"
#include "ReturnVideo.h"
// 202322371 �Ͻ¿� ����Ʈ������� 2������
// �۾� ȯ�� : VisualStudio 2022
// ! ù ȸ������ ����� �����ڷ� �����˴ϴ�. ��й�ȣ, ���̵� ���� �ʵ��� ���Ǹ� ��Ź�帳�ϴ�. 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

	printf("... ���� �뿩 ���α׷��� �����մϴ�. \n");
	for (int i = 0; i < 3; i++) {
		printf("%c", '.');
		Sleep(800); // 0.2�ʾ� 3�� ���� ����Ͽ� ȭ���� �ٷ� �������°��� ������ 
	}
	printf("\n");
	// ������ �� ���� ���� ���� ����
	int memberCount = 0;
	int videoCount = 0;

	// ������ �� ���� �д� �Լ�
	ReadFile( &memberCount, &videoCount); 
	
	// ���� �޸� ����
	struct member * memberBook = (struct member *) malloc(sizeof(struct member) * memberCount);
	struct video * videoBook = (struct video*)malloc(sizeof(struct video) * videoCount);

	// ������ ������ �д� �Լ� 
	WriteBook(memberBook, memberCount, videoBook, videoCount);
	
	memberBook = ReAge(memberBook, memberCount); // ���� �缳�� (�⵵ �ٲ��,, )

	printf("\n... ��� �Ϸ��� �ƹ� Ű�� �����ּ���. \n");
	getchar();
	system("cls");
	
	
	int key = 0;
	do  {
		SortMemberBook(memberBook, memberCount); // ȸ�� ����� �̸������� ����
		SortVideoBook(videoBook , videoCount); // ���� ����� �̸������� ����

		printf(" ==== ���� �뿩 ���α׷� ==== \n");
		printf("01. �α���\n02. ȸ������\n03. ���α׷� ����\n");
		char loginId[16] = { 0 }; // �α��� �� �α��� �� ���̵� ��� ���� 
		int specialKey = 0; // ������ ȸ���� �ڽ��� ������ �� , �ڵ� �α׾ƿ� �ϰ� �ϴ� �����Ű ���� 
		key = RightMenuKey(3); 
		if (key == 1) {
			struct member user = { 0 };
			int userIndex = -1;
			int successLogin = 0; // �α����� �������� �� 1�� ���� 
			memberBook = LogIn(memberBook, &memberCount, videoBook, &videoCount, &userIndex, & successLogin, loginId); // �α��� �Լ�
			if (successLogin == 1) { // �α��ο� ���������� Ű�� 1

				int key2 = 0; // ���� �޴�
				int key3 = 0; //  ���� �޴�
				if (strcmp(memberBook[userIndex].manager, "������") == 0) {
					do {
						userIndex = GetIndex(memberBook, memberCount, loginId); // �������� ��� sort �Լ� ������ �ε��� ��ȣ�� �ٲ� �� ����, ���̵� �̿��� �ε��� ��ȣ�� �ٽ� ���� 
						printf(" [%s][%s] �� \n\n", memberBook[userIndex].manager, memberBook[userIndex].name );
						printf("==== ������ ��� ====\n");
						printf("01. ȸ�� ����\n02. ���� ����\n03. ������ ��� ����\n");
						key2 = RightMenuKey(3);
						key3 = 0;
						if (key2 == 1) {
							do {
								printf("== 01. ȸ�� ���� ==\n");
								printf("01. ȸ�� �߰�\n02. ȸ�� �˻� �� ����/����\n03. ȸ�� ��� ��� �� ����/����\n04. ȸ�� ���� ����\n");
								key3 = RightMenuKey(4);
								if (key3 == 1) {
									printf("==== 01-01. ȸ�� �߰� ==== \n");
									int beforeCount = memberCount;
									memberBook = (struct member*)realloc(memberBook, sizeof(struct member) * (( memberCount) + 1));
									memberBook[beforeCount] = JoinMember(memberBook, & memberCount); // ȸ�����԰� ���� 
									ScreenClear();

								}
								else if (key3 == 2) {

									printf("==== 01-02. ȸ�� �˻� �� ����/���� ==== \n");
									memberBook = SortMemberBook(memberBook, memberCount); // ���� 
									memberBook = SearchMemberBook_forManager(memberBook, & memberCount,  videoBook, videoCount, & specialKey , loginId);
									ScreenClear();
									if ( specialKey == -1) { // �����ڰ� �ڱ��ڽ��� �����ϰų� �����ڿ��� �Ϲ� ȸ������ �����ϴ� ��� -> �α׾ƿ� 
										key2 = 3;
										key3 = 4;
										break;
									}
									
								}
								else if (key3 == 3) {

									// printf("==== 01-03. ȸ�� ��� ��� �� ����/����==== \n");
									memberBook = PirntMemberBook_forManager(memberBook, & memberCount, videoBook, & videoCount, & specialKey, loginId);
									ScreenClear();
									if (specialKey == -1) {
										key2 = 3;
										key3 = 4;
										break;
									}
									
								}
								else {
									printf("==== 01-04. ȸ�� ���� ���� ==== \n");
									ScreenClear();
									break; 
								}
							}while (key3 != 4);
						}
						else if (key2 == 2) {
							do {
								printf("==== 02. ���� ���� ====\n");
								printf("01. ���� �߰�\n02. ���� �˻� �� ����/����\n03. ���� ��� ��� �� ����/����\n04. ���� ���� ����\n");
								key3 = RightMenuKey(4);
								if (key3 == 1) {

									printf("==== 02-01. ���� �߰� ==== \n");
									int beforeCount = videoCount;
									videoBook = (struct video*)realloc(videoBook, sizeof(struct video) * ((videoCount) + 1));
									videoBook[beforeCount] = JoinVideo(videoBook, & videoCount);
									ScreenClear();
								}
								else if (key3 == 2) {
									printf("==== 02-02. ���� �˻� �� ����/���� ==== \n");
									videoBook = SearchvideoBook_forManager(videoBook, & videoCount, memberBook, & memberCount);
									ScreenClear();
								}
								else if (key3 == 3) {

									// printf("==== 02-03. ���� ��� ��� �� ����/���� ==== \n");
									
									videoBook = PirntVideoBook_forManager(videoBook, & videoCount, memberBook, & memberCount);
									ScreenClear();
								}
								else {
									printf("==== 02-04. ���� ���� ���� ==== \n");
									ScreenClear();
									break;
								}
							} while (key3 != 4);
						}
						else if(key2 == 3){
							printf("==== 03. ������ ��� ���� ====\n");
							ScreenClear();
							break; 
						}

					} while (key2 != 3);
				} 
				else {
					do {
						userIndex = GetIndex(memberBook, memberCount, loginId);
						printf(" [%s][%s] �� , ���� ���� �ݾ� : %-d \n\n", memberBook[userIndex].manager, memberBook[userIndex].name, memberBook[userIndex].pay);
						printf("==== ȸ�� ��� ==== \n");
						printf("01. �������� ����\n02. ���� �뿩�� �ݳ�\n03. �ݾ� ����\n04. �α׾ƿ�\n");
						key2 = RightMenuKey(4);
						if (key2 == 1) {
							do {
								printf("==== 01. ���� ���� ���� ==== \n");
								printf("... ���� ������ ����մϴ�.\n");
								printf("---------------------------------------------------------------------------------------------------------\n");
								printf(" %-10s %-15s %-15s %-5s %-15s %-15s %-20s %-5s \n", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "����ݾ�", "ȸ�� ����");
								printf("---------------------------------------------------------------------------------------------------------\n");
								printf(" %-10s %-15s %-15s %-5d %-15s %-15s %-20d %-5s \n", memberBook[userIndex].name, memberBook[userIndex].num, memberBook[userIndex].ident, memberBook[userIndex].age, memberBook[userIndex].id, memberBook[userIndex].passWord, memberBook[userIndex].pay, memberBook[userIndex].manager);
								printf("---------------------------------------------------------------------------------------------------------\n");

								printf("... ���� �۾�?\n");
								printf("01. ȸ�� Ż��\n02. ȸ�� ���� ����\n03. ȸ�� ���� ���� ����\n");
								key3 = RightMenuKey(3);

								if (key3 == 1) {
									printf("==== 01 - 01. ȸ�� Ż�� ==== \n");
									int i = 0;
									for (i = 0; i < videoCount; i++) {
										if (strcmp(memberBook[userIndex].id, videoBook[i].memberId) == 0) {
											printf(" ... �ݳ����� ���� ������ �ִ� ��� Ż�� �Ұ����մϴ�.\n");
											printf(" ... �޴��� ���ư��ϴ�.\n");
											ScreenClear();
											break;
										}
									}
									if (i == videoCount) {
										memberBook = DelMemberBook(memberBook, userIndex, &memberCount);
										key3 = 3;
										key2 = 3;
										printf(" ... �ʱ� �޴��� ���ư��ϴ�.\n");
										ScreenClear();
										break;
									}

								}
								else if (key3 == 2) {
									// printf("==== 01 - 02. ȸ�� ���� ���� ==== \n");
									memberBook = ChangeMemberBook_forMember(memberBook, userIndex, &memberCount);
									ScreenClear();
								}
								else if (key3 == 3) {
									printf("==== 01 - 03. ȸ�� ���� ���� ���� ==== \n");
									ScreenClear();
									break;
								}
							} while (key3 != 3);
						}
						else if (key2 == 2) {
							do {
								printf("==== 02. ���� �뿩�� �ݳ� ==== \n");
								printf("01. ���� �ѷ�����\n02. ���� �˻� �� �뿩\n03. ���� ��� �� �뿩\n04. ���� �ݳ�\n05. ���� �뿩�� �ݳ� ����\n");
								key3 = RightMenuKey(5);
								if (key3 == 1) {
									int uniVideoCount = 0;
									printf("==== 01. ���� �ѷ����� ==== \n"); // ���� ��� �߿��� �ߺ��� ������ ���� ���� ������ ��� 
									printf("... �츮 ���� ���� ���� �ѷ�����\n");
									printf("---------------------------------------------------------------------------------------------------------\n");
									printf("%-3s %-20s %-10s \n", "��ȣ", "�����̸�", "����");
									printf("---------------------------------------------------------------------------------------------------------\n");
									for (int i = 0; i < videoCount; i++) {
										if (IsVideoNameMakerInList(videoBook, i, videoBook[i].name, videoBook[i].maker) == 0) {
											printf("%-3d %-20s %-10s \n", ++ uniVideoCount, videoBook[i].name, videoBook[i].maker);
										}
									}
									printf("---------------------------------------------------------------------------------------------------------\n");
									if (uniVideoCount == 0) {
										printf("... ���Կ� ������ ������ �����ϴ�. \n");
									}
									else {
										printf("... �� %d ���� ���� ������\n", uniVideoCount);
									}
									ScreenClear();
								}
								else if (key3 == 2) {
									printf("==== 02. ���� �˻� �� �뿩 ==== \n");
									videoBook = SearchvideoBook_forMember(videoBook, &videoCount, memberBook, &memberCount, userIndex);
									ScreenClear();
								}
								else if (key3 == 3) {
									// printf("==== 03. ���� ��� �� �뿩 ==== \n");
									videoBook = PirntVideoBook_forMember(videoBook, videoCount, memberBook, memberCount, userIndex);
									ScreenClear();
								}
								else if (key3 == 4) {
									// printf("==== 04. ���� �ݳ� ==== \n");
									videoBook = ReturnVideo_forMember(memberBook, &memberCount, videoBook, videoCount, loginId, userIndex);
									ScreenClear();

								}
								else if (key3 == 5) {
									printf("==== 05. ���� �뿩�� �ݳ� ���� ==== \n");
									ScreenClear();
									break;
								}
							} while (key3 != 4);

						}
						else if (key2 == 3) {
							printf("==== 03. �ݾ� ���� ==== \n");
							memberBook[userIndex].pay += InsertCoin(userIndex, memberBook);
						
							ScreenClear();

						}
						else if (key2 == 4) {
							printf("==== 04. �α׾ƿ� ==== \n");
							ScreenClear();
							break;
						}
					} while (key2 != 4);
				}
			}
		}
		else if (key == 2) {
			int beforeCount = memberCount;
			memberBook = (struct member *)realloc(memberBook, sizeof( struct member ) * ( memberCount + 1) );
			memberBook[beforeCount] = JoinMember(memberBook, & memberCount);
			ScreenClear();
		}
		else if (key == 3) {
			printf("\n... ���� �뿩 ���α׷��� �����մϴ�. \n");
			WriteFile( memberBook, memberCount, videoBook , videoCount);
			printf("\n... ��� �Ϸ��� �ƹ� Ű�� �����ּ���. \n");
			getchar();

			free(memberBook);
			free(videoBook);
			return 0;
		}
	}while (key != 3);
}