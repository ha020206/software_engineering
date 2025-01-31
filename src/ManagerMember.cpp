#include "menu.h"
#include "ManagerMember.h"
#include "CheckRightValue.h"
#include "ScreenClear.h"
#include "CheckInList.h"
#include "ManagerSubFunction.h"
#include "SortStruct.h"
#include "GetDate.h"
// ȸ�� ���� ���� �ҽ�
//

// ������ ���� ȸ�� �˻� �� ���� ���� 
struct member* SearchMemberBook_forManager(struct member* memberBook, int* memberCount, struct video* videoBook, int videoCount, int * sepcialKey, char * loginId) {
	
	// �˻��� �Է� 
	char searchKey[40] = { 0 };
	int count = 0; // �˻���� ��ġ�ϴ� ����� ���� count 
	printf("... �˻� �� ���� ?\n");
	strcpy( searchKey, RightStringSize(searchKey , 40) );

	// �˻���� ��ġ�ϴ� �׸� ���� ī��Ʈ (�̸�, ���̵�, �ֹι�ȣ, ��ȭ��ȣ, ��й�ȣ�� ����)
	for (int i = 0; i < * memberCount; i++) {
		if (strstr(memberBook[i].name, searchKey) || strstr(memberBook[i].id, searchKey) || strstr(memberBook[i].ident, searchKey) || strstr(memberBook[i].num, searchKey) || strstr(memberBook[i].passWord, searchKey)) {
			count++;
		}
	}
	// ��ġ�ϴ� �׸��� ���� ���,, �޴��� ���ư� 
	if(count == 0){
		printf("... �˻���� ��ġ�ϴ� ����� �����ϴ�. \n");
		printf("... ȸ�� ���� �޴��� ���ư��ϴ�.\n");
		return memberBook;
	}
	// ��ġ�ϴ� �׸��� ���� ���, ����Ʈ 
	printf("... �� %d ���� ��� �˻� \n", count);
	int* searckIndex = (int*)malloc(sizeof(int) * count); // �����޸� ���� 
	count = 0; // �ٽ� ���Ŵϱ� �ʱ�ȭ 
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf(" %-3s %-10s %-15s %-15s %-4s %-10s %-10s %-10s %-10s\n","��ȣ", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����",  "���̵�", "��й�ȣ", "ȸ�� ����", "���� �ݾ�");
	printf("---------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < *memberCount; i++) {
		if (strstr(memberBook[i].name, searchKey) || strstr(memberBook[i].id, searchKey) || strstr(memberBook[i].ident, searchKey) || strstr(memberBook[i].num, searchKey) || strstr(memberBook[i].passWord, searchKey)) {
			searckIndex[count++] = i; // ����� ���� ��ȣ�� ���� 
			printf(" %-3d %-10s %-15s %-15s %-4d %-10s %-10s %-10s %-10d\n", count, memberBook[i].name , memberBook[i].num, memberBook[i].ident, memberBook[i].age , memberBook[i].id, memberBook[i].passWord, memberBook[i].manager, memberBook[i].pay);
		}
	}
	printf("---------------------------------------------------------------------------------------------------------\n");
	int key = 0; // �޴� �Է¹��� Ű
	int listIndex = 0; // ��Ϲ�ȣ�� memberBook ���� ���� �ε�����ȣ�� ���� ���� 
	while (key != 3) {
		memberBook = SortMemberBook(memberBook, * memberCount); // ������ ������ �ٲ�Ƿ� Sort
		printf("... ���� �۾�? \n");
		printf("01. ȸ�� ���� ����\n02. ȸ�� ���� ����\n03. ȸ�� �˻� �� ����/���� ����\n");
		key = RightMenuKey(3);
		if (key == 1) { // ȸ�� ���� �޴�
			if (count != 1) { //  �׸� ������ 1�� �ƴϸ�, ���� �� 
				printf("... ������ ���ϴ� ����� ��ȣ?\n");
			    listIndex = RightMenuKey(count) -1 ; // ������ ��ȣ -1 == �迭 �ε�����ȣ
			}

			memberBook = DelMember_forManager(memberBook, memberCount, videoBook, videoCount, searckIndex[listIndex]  , sepcialKey, loginId);
			free(searckIndex);
			searckIndex = NULL;
			return memberBook;

		}
		else if (key == 2) {
			if (count != 1) { // ȸ�� ���� �޴� 
				printf("... ������ ���ϴ� ����� ��ȣ?\n");
				listIndex = RightMenuKey(count) - 1;
			}
			memberBook = ChangeMember_forManager(memberBook, memberCount, videoBook, videoCount, searckIndex[listIndex], sepcialKey, loginId);
			free(searckIndex);
			searckIndex = NULL;
			return memberBook;

		}
		else if (key == 3) {
			printf("... ȸ�� ���� �޴��� ���ư��ϴ�.\n");
			free(searckIndex);
			searckIndex = NULL;
			return memberBook;
		}
	}
}
// ��� ���� �Լ� 
struct member* DelMemberBook(struct member * memberBook, int index, int * memberCount) { 

	for (int i = index; i < (* memberCount); i++) {
		memberBook[i] = memberBook[i + 1];
	}
	* memberCount = (* memberCount) - 1;
	printf("... ȸ�� ���� �Ϸ� !\n");
	return memberBook;
}




// ȸ�� ���� ���� ���� 
struct member* ChangeMemberBook_forMember(struct member* memberBook, int index, int* memberCount) {
	int key = 0;
	struct member buffer = { 0 };
	while (key != 5) {
		int again = 0;
		int key2 = 0;
		printf("... ���� �� �׸�?\n");
		printf("01. �̸�\n02. ��ȭ��ȣ \n03. �ֹε�Ϲ�ȣ\n04. ��й�ȣ\n");
		key = RightMenuKey(4);
		if (key == 1) {
			printf("... ���� �� �̸�? [ ���� �̸� : %s ]\n", memberBook[index].name);
			RightMemberName(memberBook[index].name);
			printf("\n... ������ ȸ�� ������ ����մϴ�. \n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf(" %-10s %-15s %-15s %-5s %-15s %-15s %-15s %-5s \n", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "���� �ݾ�", "ȸ�� ����");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf(" %-10s %-15s %-15s %-5d %-15s %-15s %-15d %-5s \n", memberBook[index].name, memberBook[index].num, memberBook[index].ident, memberBook[index].age, memberBook[index].id, memberBook[index].passWord, memberBook[index].pay, memberBook[index].manager);
			printf("---------------------------------------------------------------------------------------------------------\n");
			return memberBook;
		}
		else if (key == 2) {
			again = 0;
			do {
				key2 = 0;
				again = 0;
				printf("\n... ���� �� ��ȭ��ȣ? [ ���� ��ȭ��ȣ : %s ]\n", memberBook[index].num);
				strcpy(buffer.num, RightMemberNum(buffer.num));
				again = IsMemberNumInList(memberBook, *memberCount, buffer.num);
				if (again == 1) {
					printf("... �̹� ���Ե� ��ȭ��ȣ�� �����մϴ�. \n");
					printf("... 01. �ٸ� ��ȭ��ȣ �Է� \n... 02. ��ȭ��ȣ �Է� ���\n");
					key2 = RightMenuKey(2);
					if (key2 == 2) {
						printf("... �޴��� ���ư��ϴ�. \n");
						again = 0;
						return memberBook;
					}
				}
			} while (again == 1);
			if (key2 == 0) {
				strcpy(memberBook[index].num, buffer.num);
				printf("\n... ���� �Ϸ�! \n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-10s %-15s %-15s %-5s %-15s %-15s %-15s %-5s \n", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "���� �ݾ�", "ȸ�� ����");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-10s %-15s %-15s %-5d %-15s %-15s %-15d %-5s \n", memberBook[index].name, memberBook[index].num, memberBook[index].ident, memberBook[index].age, memberBook[index].id, memberBook[index].passWord, memberBook[index].pay, memberBook[index].manager);
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("... �޴��� ���ư��ϴ�. \n");
				return memberBook;
			}
		}
		else if (key == 3) {
			do {
				key2 = 0;
				again = 0;
				printf("... ���� �� �ֹε�Ϲ�ȣ? [ ���� �ֹε�Ϲ�ȣ : %s ]\n", memberBook[index].ident);
				strcpy(buffer.ident, RightMemberIdent(buffer.ident)); // 
				again = IsMemberIdentInList(memberBook, *memberCount, buffer.ident);
				if (again == 1) {
					printf("... �̹� ���Ե� �ֹε�Ϲ�ȣ�� �����մϴ�. \n");
					printf("... 01. �ٸ� �ֹε�Ϲ�ȣ �Է� \n... 02. �ֹε�Ϲ�ȣ �Է� ���\n");
					key2 = RightMenuKey(2);
					if (key2 == 2) {
						printf("... �޴��� ���ư��ϴ�. \n");
						again = 0;
						return memberBook;	
					}
				}
			} while (again == 1);
			if (key2 == 0) {
				strcpy(memberBook[index].ident, buffer.ident);
				memberBook[index].age = CountAge(memberBook[index].ident);

				printf("\n... ���� �Ϸ�! \n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-10s %-15s %-15s %-5s %-15s %-15s %-15s %-5s \n", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "���� �ݾ�", "ȸ�� ����");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf(" %-10s %-15s %-15s %-5d %-15s %-15s %-15d %-5s \n", memberBook[index].name, memberBook[index].num, memberBook[index].ident, memberBook[index].age, memberBook[index].id, memberBook[index].passWord, memberBook[index].pay, memberBook[index].manager);
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("... �޴��� ���ư��ϴ�. \n");
				return memberBook;
			}
		}
		else if (key == 4) {
			printf("... ���� �� ��й�ȣ? [ ���� ��й�ȣ : %s ]\n", memberBook[index].passWord);
			strcpy(memberBook[index].passWord, RightMemberPassWord(memberBook[index].passWord));
			printf("\n... ���� �Ϸ�! \n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf(" %-10s %-15s %-15s %-5s %-15s %-15s %-15s %-5s \n", "�̸�", "��ȭ��ȣ", "�ֹε�Ϲ�ȣ", "����", "���̵�", "��й�ȣ", "���� �ݾ�", "ȸ�� ����");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf(" %-10s %-15s %-15s %-5d %-15s %-15s %-15d %-5s \n", memberBook[index].name, memberBook[index].num, memberBook[index].ident, memberBook[index].age, memberBook[index].id, memberBook[index].passWord, memberBook[index].pay, memberBook[index].manager);
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("... �޴��� ���ư��ϴ�. \n");
			return memberBook;
		}
	}
}

